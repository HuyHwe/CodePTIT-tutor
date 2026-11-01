#!/usr/bin/env python3
"""Build courses/<id>/ (problems, solutions, algorithms, index.json) from raw source folders.

For maintainers, not students. Usage:
  python build_course.py --course trr2 --source-root "/path/to/Vibe Code"
  python build_course.py --all --source-root "/path/to/Vibe Code"

Reads courses/<id>/course.json (see references/adding-a-course.md for the format).
Theory notes (algorithms/*.md) are produced separately by build_theory.py and only linked here.
"""
import argparse
import json
import re
import shutil
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
from common import COURSES_DIR, read_text, strip_accents, tests_from_cpp  # noqa: E402
from run_tests import detect_io  # noqa: E402

PROBLEM_HDR = re.compile(r"^##\s+\d+\.\s+\(([A-Za-z0-9_]+)\)\s*(.*?)\s*$")
SECTION_REF = re.compile(r"(?:muc|ap dung)\s+(\d+(?:\.\d+)*)", re.I)


LATEX = [(r"\deg^+", "deg⁺"), (r"\deg^-", "deg⁻"), (r"\deg", "deg"), (r"\le", "≤"), (r"\ge", "≥"),
         (r"\neq", "≠"), (r"\ne", "≠"), (r"\times", "×"), (r"\cap", "∩"), (r"\cup", "∪"), (r"\in", "∈"),
         (r"\rightarrow", "→"), (r"\to", "→"), (r"\ldots", "…"), (r"\dots", "…"), (r"\cdot", "·"),
         (r"\sum", "Σ"), (r"\infty", "∞"), (r"\{", "{"), (r"\}", "}")]


def delatex(text):
    """'$1 \\le u_i < v_i \\le n$' -> '1 ≤ u_i < v_i ≤ n'. Chat panels don't render LaTeX, and agents
    copy the notation they read, so statements are stored as plain Unicode text."""
    def conv(m):
        s = m.group(1)
        for k, v in LATEX:
            s = re.sub(re.escape(k) + r"(?![A-Za-z])", v, s)
        s = re.sub(r"([_^])\{([^{}]*)\}", r"\1\2", s)  # 2^{18} -> 2^18, c_{ij} -> c_ij
        return s
    return re.sub(r"\$([^$\n]+)\$", conv, text)


def split_problems(md_text):
    """Return {code: (title, markdown)} from a '## N. (CODE) Title' statements file."""
    out, code, title, buf = {}, None, None, []
    for line in delatex(md_text).splitlines():
        m = PROBLEM_HDR.match(line)
        if m:
            if code:
                out[code] = (title, buf)
            code, title, buf = m.group(1), m.group(2), []
            continue
        if code:
            buf.append(line)
    if code:
        out[code] = (title, buf)
    result = {}
    for c, (t, lines) in out.items():
        while lines and (not lines[-1].strip() or lines[-1].strip() == "---"):
            lines.pop()
        result[c] = (t, f"# {c} – {t}\n\n" + "\n".join(lines).strip() + "\n")
    return result


def header_comments(src):
    lines = []
    for line in src.splitlines():
        s = line.strip()
        if s.startswith("//"):
            lines.append(s.lstrip("/ ").strip())
        elif s:
            break
    return lines


def code_from_filename(name, patterns):
    for p in patterns:
        m = re.match(p, name)
        if m:
            return m.group(0)
    return None


def algorithm_id(stem):
    m = re.match(r"^(\d+(?:\.\d+)*)_(.+)$", stem)
    return (m.group(1), m.group(2).replace("_", " ")) if m else (None, None)


def resolve_sections(refs, algo_ids):
    out = []
    for r in refs:
        if r in algo_ids:
            out.append(r)
        else:  # '2.1' -> '2.1.1' / '2.1.2' only when unambiguous
            cands = [a for a in algo_ids if a.startswith(r + ".")]
            if len(cands) == 1:
                out.append(cands[0])
    return list(dict.fromkeys(out))


ABBREV = {"ds": "danh sach", "mt": "ma tran", "ts": "trong so", "tplt": "thanh phan lien thong",
          "dske": "danh sach ke", "dscanh": "danh sach canh", "mtlienthuoc": "ma tran lien thuoc",
          "matranke": "ma tran ke", "cohuong": "co huong", "vohuong": "vo huong"}


def split_camel(name):
    """'CoHuong MaTranKe sang DSCanhTS' -> 'Co Huong Ma Tran Ke sang DS Canh TS'."""
    return re.sub(r"(?<=[a-z])(?=[A-Z])|(?<=[A-Z])(?=[A-Z][a-z])", " ", name)


def keywords_for(code, title, file_name, topic, summary):
    words = strip_accents(" ".join([code, title, split_camel(file_name), topic] + summary)).lower()
    extra = [v for k, v in ABBREV.items() if re.search(rf"\b{k}\b", words)]
    return " ".join([words] + extra)


def clean_summary(header, code):
    """Drop the leading 'CODE - ' / 'CODE. ' prefix of the first comment line, keep the rest."""
    out = []
    for i, line in enumerate(header):
        if i == 0 and line.upper().startswith(code.upper()):
            line = line[len(code):].lstrip(" .-:")
        if line:
            out.append(line)
    return out


def topic_for(code, topics):
    best = ""
    for prefix in topics:
        if code.startswith(prefix) and len(prefix) > len(best):
            best = prefix
    return topics.get(best, "")


def build(course_id, source_root):
    cdir = COURSES_DIR / course_id
    cfg = json.loads((cdir / "course.json").read_text(encoding="utf-8"))
    src = cfg["sources"]
    root = Path(source_root)

    # ---- algorithms (reference implementations by textbook section)
    adir = cdir / "algorithms"
    adir.mkdir(parents=True, exist_ok=True)
    algos = {}
    for cpp in sorted((root / src["algorithms_dir"]).glob("*.cpp")):
        aid, name = algorithm_id(cpp.stem)
        if not aid:
            continue
        shutil.copy2(cpp, adir / cpp.name)
        algos[aid] = {"id": aid, "name": name, "cpp": f"algorithms/{cpp.name}"}
    # theory notes produced by build_theory.py (may include sections without .cpp)
    for md in sorted(adir.glob("*.md")):
        aid, name = algorithm_id(md.stem)
        if not aid:
            continue
        algos.setdefault(aid, {"id": aid, "name": name})["notes"] = f"algorithms/{md.name}"
    if (adir / "conventions.md").exists():
        algos["0"] = {"id": "0", "name": "Quy ước & khung nhập liệu chung", "notes": "algorithms/conventions.md"}

    # ---- problem statements
    statements = split_problems(read_text(root / src["problems_md"]))
    pdir = cdir / "problems"
    pdir.mkdir(exist_ok=True)
    for code, (_, md) in statements.items():
        (pdir / f"{code}.md").write_text(md, encoding="utf-8")

    # ---- solutions
    sdir = cdir / "solutions"
    sdir.mkdir(exist_ok=True)
    problems, missing = [], []
    overrides = cfg.get("algorithm_overrides", {})
    defaults = cfg.get("default_algorithms", {})
    generators = cfg.get("generators", {})
    for cpp in sorted((root / src["solutions_dir"]).glob("*.cpp")):
        code = code_from_filename(cpp.name, cfg["code_patterns"])
        if not code:
            print(f"  bỏ qua {cpp.name}: không nhận ra mã bài", file=sys.stderr)
            continue
        dst = sdir / f"{code}.cpp"
        shutil.copy2(cpp, dst)
        text = read_text(cpp)
        header = header_comments(text)
        refs = SECTION_REF.findall(" ".join(header) + " " + text)
        if code in overrides:
            sections = overrides[code]
        else:
            sections = resolve_sections(refs, list(algos))
            if not sections:
                for prefix, secs in defaults.items():
                    if code.startswith(prefix):
                        sections = secs
        tests = tests_from_cpp(cpp)
        notes = [re.sub(r"^test(\s*case)?\s*\d*\s*\((.*)\)\s*$", r"\2", t["name"], flags=re.I)
                 for t in tests if "(" in t["name"]]
        notes += cfg.get("extra_notes", {}).get(code, [])
        io = detect_io(cpp)
        title = statements.get(code, (None,))[0]
        if title is None:
            missing.append(code)
            title = cpp.stem[len(code):].strip(" _-").replace("_", " ")
        file_name = split_camel(cpp.stem[len(code):].strip(" _-").replace("_", " "))
        entry = {
            "code": code,
            "title": title,
            "name": file_name,
            "topic": topic_for(code, cfg.get("topics", {})),
            "summary": clean_summary(header, code),
            "problem": f"problems/{code}.md" if code in statements else None,
            "solution": f"solutions/{code}.cpp",
            "algorithms": [s for s in sections if s in algos],
            "io": ({"type": "file", "in": io["in"], "out": io["out"]} if io["in"] else {"type": "stdin"}),
            "num_tests": len(tests),
            "notes": notes,
        }
        if code in generators:
            entry["generator"] = generators[code]
        entry["keywords"] = keywords_for(code, title, file_name, entry["topic"], entry["summary"])
        problems.append(entry)

    index = {"course": course_id, "name": cfg["name"],
             "algorithms": sorted(algos.values(), key=lambda a: [int(x) for x in a["id"].split(".")]),
             "problems": problems}
    (cdir / "index.json").write_text(json.dumps(index, ensure_ascii=False, indent=1), encoding="utf-8")
    print(f"{course_id}: {len(problems)} bài, {len(algos)} mục thuật toán, {len(statements)} đề")
    if missing:
        print(f"  CẢNH BÁO: không có đề cho {missing}")
    no_alg = [p["code"] for p in problems if not p["algorithms"]]
    if no_alg:
        print(f"  (không gắn thuật toán mẫu: {', '.join(no_alg)})")
    return cfg


def write_registry():
    courses = []
    for d in sorted(COURSES_DIR.iterdir()):
        if (d / "course.json").exists() and (d / "index.json").exists():
            cfg = json.loads((d / "course.json").read_text(encoding="utf-8"))
            courses.append({"id": cfg["id"], "name": cfg["name"], "code_patterns": cfg["code_patterns"]})
    (COURSES_DIR / "registry.json").write_text(
        json.dumps({"courses": courses}, ensure_ascii=False, indent=1), encoding="utf-8")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--course")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--source-root", required=True)
    a = ap.parse_args()
    ids = [d.name for d in COURSES_DIR.iterdir() if (d / "course.json").exists()] if a.all else [a.course]
    for cid in sorted(ids):
        build(cid, a.source_root)
    write_registry()


if __name__ == "__main__":
    main()
