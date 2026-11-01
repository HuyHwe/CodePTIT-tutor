#!/usr/bin/env python3
"""Find a CodePTIT problem and print every file the tutor needs for it.

Examples:
  python find_problem.py TRR5001
  python find_problem.py "trr1 2002"
  python find_problem.py "liet ke to hop quay lui"
  python find_problem.py --file path/to/student.cpp   # guess from file name / comments / I/O
  python find_problem.py --list [trr1|trr2]
  python find_problem.py --algorithms trr2

Output: best matches with absolute paths to statement, reference solution,
algorithm templates and theory notes. Add --json for machine-readable output.
"""
import argparse
import difflib
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import COURSES_DIR, all_problems, load_index, load_registry, norm_code, read_text, strip_accents  # noqa: E402


def expand(course, p):
    cdir = COURSES_DIR / course
    algos = {a["id"]: a for a in load_index(course)["algorithms"]}
    out = {
        "course": course, "code": p["code"], "title": p["title"], "name": p["name"], "topic": p["topic"],
        "summary": p["summary"], "io": p["io"], "num_tests": p["num_tests"], "notes": p["notes"],
        "problem": str(cdir / p["problem"]) if p.get("problem") else None,
        "solution": str(cdir / p["solution"]),
        "pitfalls": str(cdir / "pitfalls.md") if (cdir / "pitfalls.md").exists() else None,
        "algorithms": [],
    }
    for aid in p["algorithms"]:
        a = algos.get(aid)
        if a:
            out["algorithms"].append({"id": aid, "name": a["name"],
                                      "cpp": str(cdir / a["cpp"]) if a.get("cpp") else None,
                                      "notes": str(cdir / a["notes"]) if a.get("notes") else None})
    if p.get("generator"):
        out["generator"] = p["generator"]
    return out


def _words(text):
    return re.findall(r"[a-z0-9]+", strip_accents(text).lower())


_IDF = None


def _idf():
    """Rare words (e.g. 'tru', 'kruskal') count more than common ones ('do', 'thi', 'bang')."""
    global _IDF
    if _IDF is None:
        import math
        docs = [set(_words(p["keywords"])) for _, p in all_problems()]
        n = len(docs)
        vocab = set().union(*docs) if docs else set()
        _IDF = {w: math.log((n + 1) / (1 + sum(w in d for d in docs))) + 0.1 for w in vocab}
    return _IDF


def score(query, p):
    words = [w for w in _words(query) if len(w) > 1]
    if not words:
        return 0.0
    idf = _idf()
    title_words = set(_words(p["title"] + " " + p["name"]))
    all_words = set(_words(p["keywords"]))
    total = sum(idf.get(w, 3.0) for w in words)
    got = sum(idf.get(w, 3.0) * (1.0 if w in title_words else 0.7 if w in all_words else 0) for w in words)
    ratio = difflib.SequenceMatcher(None, " ".join(words), " ".join(_words(p["title"] + " " + p["name"]))).ratio()
    return (got / total) * 0.85 + ratio * 0.15


def search(query, limit=5):
    key = norm_code(query)
    # 1) exact code ("TRR5001", "trr1-2002"); also accept the number alone ("5001")
    exact = [(c, p) for c, p in all_problems() if norm_code(p["code"]) == key]
    if not exact and key.isdigit():
        exact = [(c, p) for c, p in all_problems() if norm_code(p["code"]).endswith(key)]
    if exact:
        return [(1.0, c, p) for c, p in exact]
    # 2) code embedded in a longer string
    for c, p in all_problems():
        if norm_code(p["code"]) in key and len(norm_code(p["code"])) >= 5:
            return [(1.0, c, p)]
    # 3) fuzzy by title / file name / summary / topic
    scored = sorted(((score(query, p), c, p) for c, p in all_problems()), key=lambda x: -x[0])
    return [s for s in scored[:limit] if s[0] > 0.25]


def guess_from_file(path):
    """Guess the problem from a student's file: name, comments, identifiers and I/O file names."""
    src = read_text(path)
    comments = [c.strip() for c in re.findall(r"//\s*(.+)", src) + re.findall(r"/\*(.*?)\*/", src, re.S)]
    candidates = [Path(path).stem.replace("_", " ")] + [c for c in comments if len(c) < 200][:15]
    # 1) an explicit problem code anywhere in name/comments wins
    for cand in candidates:
        res = search(cand, 3)
        if res and res[0][0] >= 1.0:
            return res
    # 2) score each clue separately and keep each problem's best score
    generic = {"bai", "code", "main", "test", "sv", "em", "solution", "cpp", "lam", "file", "nhap", "result",
               "try", "sinh", "int", "void", "for", "while", "return", "cout", "cin", "bits", "stdc", "include"}
    idents = sorted(set(re.findall(r"\b([A-Za-z][A-Za-z0-9]{3,})\s*\(", src)))
    idents = [re.sub(r"(?<=[a-z])(?=[A-Z])", " ", i) for i in idents]
    clues = []
    for clue in candidates + idents:
        words = [w for w in _words(clue) if len(w) > 1 and w not in generic]
        if words:
            clues.append(" ".join(words))
    best = {}
    for clue in clues:
        for c, p in all_problems():
            s = score(clue, p)
            key = (c, p["code"])
            if s > best.get(key, (0,))[0]:
                best[key] = (s, c, p)
    io = re.findall(r'freopen\s*\(\s*"([A-Za-z]+)\.INP"', src, re.I)
    ranked = []
    for s, c, p in best.values():
        if io and io[0].upper() + ".INP" in p["io"].get("in", []):
            s += 0.1  # same input file as the statement (DT/TK/CT/CK/DN/BN)
        ranked.append((min(s, 0.99), c, p))
    ranked.sort(key=lambda x: -x[0])
    return [r for r in ranked[:5] if r[0] > 0.3]


def print_human(results):
    if not results:
        print("Không tìm thấy bài phù hợp. Hãy hỏi sinh viên mã bài (vd TRR5001, TRR1_2002, LT004).")
        return
    for s, c, p in results:
        e = expand(c, p)
        tag = "KHỚP MÃ" if s >= 1.0 else f"độ khớp {s:.2f}"
        print(f"== {c}/{e['code']} – {e['title']} ({e['name']}) [{tag}]")
        print(f"   Chủ đề: {e['topic']}")
        if e["summary"]:
            print("   Tóm tắt: " + " | ".join(e["summary"]))
        io = e["io"]
        print("   I/O: " + (f"đọc {', '.join(io['in'])}, ghi {', '.join(io['out'])}" if io["type"] == "file" else "stdin/stdout"))
        print(f"   Đề bài:      {e['problem']}")
        print(f"   Lời giải chuẩn (KHÔNG đưa nguyên cho SV): {e['solution']}")
        for a in e["algorithms"]:
            print(f"   Thuật toán mẫu {a['id']} {a['name']}: cpp={a['cpp']} notes={a['notes']}")
        if e["pitfalls"]:
            print(f"   Lỗi hay gặp: {e['pitfalls']}")
        for n in e["notes"]:
            print(f"   Ghi chú: {n}")
        print(f"   Số test có sẵn: {e['num_tests']}" + (f"; generator: {e['generator']}" if e.get("generator") else "; chưa có generator"))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("query", nargs="*")
    ap.add_argument("--file", help="đoán bài từ file code của sinh viên")
    ap.add_argument("--list", nargs="?", const="all", help="liệt kê bài của một môn (hoặc tất cả)")
    ap.add_argument("--algorithms", metavar="COURSE", help="liệt kê các mục thuật toán mẫu của một môn")
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args()

    if a.list:
        for c, p in all_problems():
            if a.list in ("all", c):
                print(f"{c}/{p['code']}\t{p['title']}\t{p['name']}\t[{','.join(p['algorithms'])}]")
        return
    if a.algorithms:
        for al in load_index(a.algorithms)["algorithms"]:
            print(f"{al['id']}\t{al['name']}\tcpp={al.get('cpp')}\tnotes={al.get('notes')}")
        return
    if a.file:
        results = guess_from_file(a.file)
    elif a.query:
        results = search(" ".join(a.query))
    else:
        ap.error("cần truy vấn, --file, --list hoặc --algorithms")
    if a.json:
        print(json.dumps([dict(expand(c, p), score=round(s, 3)) for s, c, p in results], ensure_ascii=False, indent=1))
    else:
        print_human(results)


if __name__ == "__main__":
    main()
