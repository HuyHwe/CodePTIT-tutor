#!/usr/bin/env python3
"""Compile and run a student's C++ solution against the tests of a CodePTIT problem.

Examples:
  python run_tests.py --problem TRR5001 --student bai.cpp
  python run_tests.py --problem TRR5001 --student bai.cpp --stress 300
  python run_tests.py --problem TRR5001 --student bai.cpp --input my_input.txt
  python run_tests.py --problem TRR5001 --self-check      # reference vs. its own tests
  python run_tests.py --self-check-all                    # every problem in every course

Exit code: 0 = all passed, 1 = some test failed, 2 = usage / compile error.
Never modifies the student's files: everything runs in a temp directory.
"""
import argparse
import hashlib
import json
import os
import random
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import (COURSES_DIR, SKILL_ROOT, all_problems, find_problem_by_code,  # noqa: E402
                    normalize_output, outputs_match, read_text, tests_from_cpp)

SHIM_INCLUDE = Path(__file__).resolve().parent / "include"
CACHE_DIR = Path(tempfile.gettempdir()) / "codeptit-tutor-cache"
EXE = ".exe" if os.name == "nt" else ""
MAX_OUTPUT = 1 << 20  # 1 MB


# ------------------------------------------------------------------ compiling

def find_compiler():
    for cc in (os.environ.get("CXX"), "g++", "clang++", "c++"):
        if cc and shutil.which(cc):
            return cc
    return None


def compile_cpp(src_path):
    """Return (exe_path, None) or (None, error_text). Builds are cached by content hash."""
    cc = find_compiler()
    if not cc:
        return None, "Không tìm thấy trình biên dịch C++ (g++ / clang++). Hãy cài g++ (MinGW trên Windows, Xcode CLT trên macOS)."
    src = Path(src_path).read_bytes()
    key = hashlib.sha1(src + cc.encode()).hexdigest()[:16]
    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    exe = CACHE_DIR / f"{key}{EXE}"
    if exe.exists():
        return exe, None
    tmp_src = CACHE_DIR / f"{key}.cpp"
    tmp_src.write_bytes(src)
    cmd = [cc, "-std=c++17", "-O2", "-idirafter", str(SHIM_INCLUDE), str(tmp_src), "-o", str(exe)]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=120,
                           encoding="utf-8", errors="replace")
    except subprocess.TimeoutExpired:
        return None, "Biên dịch quá 120 giây."
    if r.returncode != 0:
        err = r.stderr.replace(str(tmp_src), Path(src_path).name)
        return None, err.strip()[-4000:]
    return exe, None


# ------------------------------------------------------------------ I/O style

def _strip_comments(src):
    src = re.sub(r"/\*.*?\*/", "", src, flags=re.S)
    return re.sub(r"//[^\n]*", "", src)


def detect_io(src_path):
    """Return {"in": [file names], "out": [file names]} read/written via freopen/ifstream."""
    code = _strip_comments(read_text(src_path))
    ins = re.findall(r'freopen\s*\(\s*"([^"]+)"\s*,\s*"r', code)
    outs = re.findall(r'freopen\s*\(\s*"([^"]+)"\s*,\s*"w', code)
    ins += re.findall(r'ifstream\s+\w+\s*\(\s*"([^"]+)"', code)
    outs += re.findall(r'ofstream\s+\w+\s*\(\s*"([^"]+)"', code)
    return {"in": sorted(set(ins)), "out": sorted(set(outs))}


# ------------------------------------------------------------------ running

def run_exe(exe, input_text, io, timeout):
    """Run in a fresh temp dir. Input goes to stdin AND to every input file the code opens."""
    with tempfile.TemporaryDirectory(prefix="codeptit-run-") as wd:
        for name in io["in"]:
            Path(wd, name).write_text(input_text, encoding="utf-8")
        try:
            r = subprocess.run([str(exe)], input=input_text.encode(), cwd=wd,
                               capture_output=True, timeout=timeout)
        except subprocess.TimeoutExpired:
            return {"status": "TLE", "output": ""}
        out = r.stdout
        for name in io["out"]:
            p = Path(wd, name)
            if p.exists():
                out = p.read_bytes()
                break
        res = {"status": "OK", "output": out[:MAX_OUTPUT].decode("utf-8", errors="replace"),
               "stderr": r.stderr[:2000].decode("utf-8", errors="replace")}
        if r.returncode != 0:
            res["status"] = "RE"
            res["returncode"] = r.returncode
        return res


def first_diff_line(got, expected):
    """First line that differs, ignoring spacing and blank lines (like the CodePTIT judge)."""
    g = [l.split() for l in normalize_output(got).split("\n") if l.strip()]
    e = [l.split() for l in normalize_output(expected).split("\n") if l.strip()]
    for i in range(max(len(g), len(e))):
        gl = " ".join(g[i]) if i < len(g) else "<không có dòng này>"
        el = " ".join(e[i]) if i < len(e) else "<không có dòng này>"
        if gl != el:
            return {"line": i + 1, "got": gl, "expected": el}
    return None


def judge(res, expected):
    if res["status"] != "OK":
        return res["status"]
    return "PASS" if outputs_match(res["output"], expected) else "WA"


# ------------------------------------------------------------------ problem lookup

def resolve_problem(code):
    hits = find_problem_by_code(code)
    if not hits:
        sys.exit(f"Không tìm thấy bài '{code}'. Thử: python find_problem.py \"{code}\"")
    if len(hits) > 1:
        names = ", ".join(f"{c}/{p['code']}" for c, p in hits)
        sys.exit(f"Mã '{code}' trùng ở nhiều môn: {names}. Ghi rõ dạng <môn>/<mã>.")
    course, entry = hits[0]
    entry = dict(entry)
    entry["course"] = course
    entry["solution_path"] = COURSES_DIR / course / entry["solution"]
    return entry


def resolve_arg(code):
    if "/" in code and not Path(code).exists():
        course, c = code.split("/", 1)
        for cid, p in all_problems():
            if cid == course and p["code"].upper() == c.upper():
                e = dict(p, course=cid, solution_path=COURSES_DIR / cid / p["solution"])
                return e
    return resolve_problem(code)


# ------------------------------------------------------------------ main flows

def run_suite(student, reference, tests, timeout, stress=0, generator=None, seed=None,
              custom_input=None):
    report = {"compile": {}, "tests": [], "stress": None, "io": {}}
    s_exe, err = compile_cpp(student)
    if err:
        report["compile"] = {"ok": False, "who": "student", "error": err}
        return report
    report["compile"] = {"ok": True}
    s_io = detect_io(student)
    report["io"]["student"] = s_io
    r_exe = r_io = None
    if reference:
        r_exe, rerr = compile_cpp(reference)
        if rerr:
            report["compile"] = {"ok": False, "who": "reference", "error": rerr}
            return report
        r_io = detect_io(reference)
        report["io"]["reference"] = r_io

    if custom_input is not None:
        tests = [{"name": "Input tự nhập", "input": custom_input, "output": None}]

    for t in tests:
        res = run_exe(s_exe, t["input"], s_io, timeout)
        expected = t["output"]
        if expected is None and r_exe:
            rr = run_exe(r_exe, t["input"], r_io, timeout)
            expected = rr["output"]
        verdict = judge(res, expected) if expected is not None else res["status"]
        item = {"name": t["name"], "verdict": verdict, "input": t["input"],
                "expected": normalize_output(expected or ""), "got": normalize_output(res["output"])}
        if verdict == "WA":
            item["first_diff"] = first_diff_line(res["output"], expected)
        if res.get("stderr"):
            item["stderr"] = res["stderr"]
        if "returncode" in res:
            item["returncode"] = res["returncode"]
        report["tests"].append(item)

    if stress and r_exe and generator:
        report["stress"] = stress_test(s_exe, s_io, r_exe, r_io, generator, stress, timeout, seed)
    elif stress:
        report["stress"] = {"skipped": "Bài này chưa có bộ sinh test ngẫu nhiên (generator)."}
    return report


def stress_test(s_exe, s_io, r_exe, r_io, generator, count, timeout, seed):
    import generators  # local module
    gen = generators.get(generator)
    if gen is None:
        return {"skipped": f"Không có generator '{generator}'."}
    rng = random.Random(seed if seed is not None else 12345)

    def attempt(size):
        inp = gen(rng, size)
        rr = run_exe(r_exe, inp, r_io, timeout)
        if rr["status"] != "OK":
            return None  # generator produced something the reference rejects; skip it
        sr = run_exe(s_exe, inp, s_io, timeout)
        v = judge(sr, rr["output"])
        if v == "PASS":
            return None
        return {"failed": True, "verdict": v, "input": inp,
                "expected": normalize_output(rr["output"]), "got": normalize_output(sr["output"]),
                "first_diff": first_diff_line(sr["output"], rr["output"]) if v == "WA" else None}

    # Grow sizes slowly so the first failure found is small.
    for i in range(count):
        bad = attempt(1 + i * 6 // max(count, 1))
        if bad:
            bad["ran"] = i + 1
            # Shrink: keep sampling the smallest size and keep the shortest failing input,
            # so the student gets a counterexample small enough to trace by hand.
            original = len(bad["input"])
            for _ in range(150):
                smaller = attempt(1)
                if smaller and len(smaller["input"]) < len(bad["input"]):
                    smaller["ran"] = bad["ran"]
                    bad = smaller
            bad["shrunk_from"] = original if len(bad["input"]) < original else None
            return bad
    return {"ran": count, "failed": False}


def io_warning(report, entry):
    s, r = report["io"].get("student"), report["io"].get("reference")
    if not s or not r:
        return None
    if r["in"] and not s["in"]:
        return (f"Đề yêu cầu đọc file {', '.join(r['in'])} / ghi {', '.join(r['out'])}, nhưng code đang dùng "
                "bàn phím (stdin). Script vẫn chạy được, nhưng nộp lên CodePTIT có thể bị sai — cần freopen.")
    if s["in"] and r["in"] and s["in"] != r["in"]:
        return f"Tên file vào khác đề: code dùng {s['in']}, đề yêu cầu {r['in']}."
    if s["out"] and r["out"] and s["out"] != r["out"]:
        return f"Tên file ra khác đề: code dùng {s['out']}, đề yêu cầu {r['out']}."
    return None


def short(text, n=1500):
    return text if len(text) <= n else text[:n] + f"\n... (cắt bớt, còn {len(text) - n} ký tự)"


def print_report(report, title, warn=None):
    print(f"=== {title} ===")
    c = report["compile"]
    if not c.get("ok"):
        who = "code sinh viên" if c.get("who") == "student" else "lời giải chuẩn"
        print(f"LỖI BIÊN DỊCH ({who}):\n{c.get('error')}")
        return
    if warn:
        print(f"CẢNH BÁO I/O: {warn}")
    labels = {"PASS": "ĐÚNG", "WA": "SAI KẾT QUẢ", "TLE": "QUÁ THỜI GIAN", "RE": "LỖI KHI CHẠY (runtime error)", "OK": "đã chạy"}
    for t in report["tests"]:
        print(f"\n[{t['name']}] {labels.get(t['verdict'], t['verdict'])}")
        if t["verdict"] not in ("PASS",):
            print("--- input ---\n" + short(t["input"].rstrip()))
            if t["expected"]:
                print("--- mong đợi ---\n" + short(t["expected"]))
            print("--- code cho ra ---\n" + short(t["got"] or "<rỗng>"))
            if t.get("first_diff"):
                d = t["first_diff"]
                print(f"--- khác đầu tiên ở dòng {d['line']}: mong đợi `{d['expected']}` nhưng ra `{d['got']}`")
            if t.get("returncode") is not None:
                print(f"--- mã thoát: {t['returncode']} (thường do truy cập mảng ngoài phạm vi / chia 0 / đệ quy quá sâu)")
            if t.get("stderr"):
                print("--- stderr ---\n" + short(t["stderr"], 500))
    s = report.get("stress")
    if s:
        print("\n=== Test ngẫu nhiên (so với lời giải chuẩn) ===")
        if s.get("skipped"):
            print(s["skipped"])
        elif not s["failed"]:
            print(f"Đã chạy {s['ran']} test ngẫu nhiên: tất cả khớp.")
        else:
            print(f"Phát hiện test làm sai sau {s['ran']} lần thử ({labels.get(s['verdict'], s['verdict'])}).")
            print("Đã thu nhỏ: input dưới đây ngắn nhất trong ~150 lần thử thêm"
                  + (f" (ban đầu {s['shrunk_from']} ký tự)." if s.get("shrunk_from") else "; không tìm được input nhỏ hơn."))
            print("--- input ---\n" + short(s["input"].rstrip()))
            print("--- mong đợi ---\n" + short(s["expected"]))
            print("--- code cho ra ---\n" + short(s["got"] or "<rỗng>"))
            if s.get("first_diff"):
                d = s["first_diff"]
                print(f"--- khác đầu tiên ở dòng {d['line']}: mong đợi `{d['expected']}` nhưng ra `{d['got']}`")
    passed = sum(t["verdict"] == "PASS" for t in report["tests"])
    print(f"\nTổng: {passed}/{len(report['tests'])} test có sẵn đúng hoàn toàn.")


def all_ok(report):
    if not report["compile"].get("ok"):
        return False
    if any(t["verdict"] not in ("PASS", "OK") for t in report["tests"]):
        return False
    s = report.get("stress")
    return not (s and s.get("failed"))


def self_check_all(timeout):
    total = bad = 0
    for course, p in all_problems():
        total += 1
        sol = COURSES_DIR / course / p["solution"]
        rep = run_suite(str(sol), None, tests_from_cpp(sol), timeout)
        ok = all_ok(rep)
        bad += not ok
        verdicts = ",".join(t["verdict"] for t in rep["tests"]) or "NO TESTS"
        if not rep["compile"].get("ok"):
            verdicts = "COMPILE ERROR"
        print(f"{'OK ' if ok else 'BAD'} {course}/{p['code']}: {verdicts}")
    algo_total = algo_bad = 0
    for course in sorted(d.name for d in COURSES_DIR.iterdir() if d.is_dir()):
        for cpp in sorted((COURSES_DIR / course / "algorithms").glob("*.cpp")):
            tests = tests_from_cpp(cpp)
            if not tests:
                continue
            algo_total += 1
            rep = run_suite(str(cpp), None, tests, timeout)
            ok = all_ok(rep)
            algo_bad += not ok
            if not ok:
                print(f"BAD {course}/algorithms/{cpp.name}: " + ",".join(t["verdict"] for t in rep["tests"]))
    print(f"\nLời giải: {total - bad}/{total} đúng. Thuật toán mẫu: {algo_total - algo_bad}/{algo_total} đúng.")
    return 0 if bad == 0 and algo_bad == 0 else 1


def check_generator(entry, count, timeout):
    """Maintainer check: the reference must run cleanly and print something on generated inputs."""
    import generators
    gen = generators.get(entry.get("generator") or "")
    if gen is None:
        print(f"{entry['code']}: chưa có generator hợp lệ ({entry.get('generator')})")
        return 1
    exe, err = compile_cpp(entry["solution_path"])
    if err:
        print(err)
        return 2
    io, rng, bad = detect_io(entry["solution_path"]), random.Random(1), 0
    for i in range(count):
        inp = gen(rng, 1 + i * 6 // count)
        r = run_exe(exe, inp, io, timeout)
        if r["status"] != "OK" or not r["output"].strip():
            bad += 1
            if bad <= 3:
                print(f"--- input làm lời giải chuẩn {r['status']}/rỗng ---\n{inp}")
    print(f"{entry['code']} ({entry['generator']}): {count - bad}/{count} input hợp lệ")
    return 0 if bad == 0 else 1


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--problem", help="mã bài, vd TRR5001, TRR1_2002, LT004 hoặc trr2/TRR5001")
    ap.add_argument("--student", help="đường dẫn file .cpp của sinh viên")
    ap.add_argument("--reference", help="(tùy chọn) file lời giải để so, thay cho lời giải trong skill")
    ap.add_argument("--input", help="file input tự nhập: chạy code SV và lời giải chuẩn rồi so")
    ap.add_argument("--stress", type=int, default=0, help="số test ngẫu nhiên so với lời giải chuẩn")
    ap.add_argument("--seed", type=int)
    ap.add_argument("--timeout", type=float, default=2.0)
    ap.add_argument("--json", action="store_true", help="in kết quả dạng JSON")
    ap.add_argument("--self-check", action="store_true", help="chạy lời giải chuẩn với test của nó")
    ap.add_argument("--self-check-all", action="store_true")
    ap.add_argument("--check-generator", type=int, metavar="N",
                    help="(bảo trì) sinh N input, kiểm tra lời giải chuẩn chạy ổn trên tất cả")
    a = ap.parse_args()

    if a.self_check_all:
        sys.exit(self_check_all(a.timeout))
    if not a.problem and not a.reference:
        ap.error("cần --problem hoặc --reference")

    entry = resolve_arg(a.problem) if a.problem else None
    if a.check_generator:
        sys.exit(check_generator(entry, a.check_generator, a.timeout))
    reference = a.reference or (str(entry["solution_path"]) if entry else None)
    student = reference if a.self_check else a.student
    if not student:
        ap.error("cần --student (hoặc --self-check)")
    if not Path(student).exists():
        sys.exit(f"Không thấy file {student}")

    tests = tests_from_cpp(reference) if reference else []
    custom = read_text(a.input) if a.input else None
    generator = entry.get("generator") if entry else None
    rep = run_suite(student, reference, tests, a.timeout, a.stress, generator, a.seed, custom)
    warn = io_warning(rep, entry) if not a.self_check else None
    if a.json:
        rep["io_warning"] = warn
        print(json.dumps(rep, ensure_ascii=False, indent=2))
    else:
        title = f"{entry['course']}/{entry['code']} – {entry['title']}" if entry else Path(student).name
        print_report(rep, title, warn)
    if not rep["compile"].get("ok"):
        sys.exit(2)
    sys.exit(0 if all_ok(rep) else 1)


if __name__ == "__main__":
    main()
