#!/usr/bin/env python3
"""Convert a plain-text theory document ("Bộ thuật toán ...") into one markdown file per section.

For maintainers. Usage:
  python build_theory.py --course trr2 --source-root "/path/to/Vibe Code"

Input format (plain text, as exported from Google Docs):
  "<n>. <Chapter title>"          chapter heading, optionally followed by intro text
  "<n>.<m>[.<k>]. <Section title>"  section heading
  "Lời văn." / "Mã giả." / "Code..."  parts of a section
  "a | b | c"                     table rows;  "– item" bullets;  "  1. item" nested lists
Output: courses/<id>/algorithms/<section>_<Name>.md, conventions.md (chapter 0), cheatsheet.md
("Bảng tra nhanh" chapter). The "Code." part links to the tested .cpp of the same section
when it exists; otherwise the code is kept inline. Extra notes that must survive a rebuild
live in course.json under "theory_notes": {"<section id>": "markdown text"} ("0" = conventions).
"""
import argparse
import json
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
from common import COURSES_DIR, read_text, strip_accents  # noqa: E402

SECTION = re.compile(r"^(\d+(?:\.\d+)+)\.\s+(\S.*?)\s*$")
CHAPTER = re.compile(r"^(\d+)\.\s+(\S.*?)\s*$")
PART = re.compile(r"^(Lời văn|Mã giả|Code)\b\.?\s*(.*)$")
LIST = re.compile(r"^(\s*)(\d+\.|[–-])\s+(.*)$")


def is_ascii(s):
    return all(ord(c) < 128 for c in s)


def is_header(line):
    return bool(SECTION.match(line) or PART.match(line))


# ------------------------------------------------------------------ tokenising

def strip_toc(lines):
    """Drop the 'Mục lục' block (title line + consecutive entries until a blank line)."""
    out, i = [], 0
    while i < len(lines):
        if lines[i].strip().lower() == "mục lục":
            i += 1
            while i < len(lines) and lines[i].strip():
                i += 1
            continue
        out.append(lines[i])
        i += 1
    return out


def split_document(lines):
    """Return (preamble, [chapter dict]) where chapter = {id, title, intro, sections:[(id,title,lines)]}."""
    pre, chapters, cur_ch, cur_sec = [], [], None, None
    expected = None  # next chapter number we accept as a heading
    for idx, line in enumerate(lines):
        prev_blank = idx == 0 or not lines[idx - 1].strip()
        m = SECTION.match(line)
        if m and not line.startswith(" "):
            cur_sec = (m.group(1), m.group(2), [])
            if cur_ch is None:
                cur_ch = {"id": m.group(1).split(".")[0], "title": "", "intro": [], "sections": []}
                chapters.append(cur_ch)
            cur_ch["sections"].append(cur_sec)
            continue
        c = CHAPTER.match(line)
        if c and prev_blank and not line.startswith(" "):
            num = int(c.group(1))
            if expected is None or num == expected:
                cur_ch = {"id": c.group(1), "title": c.group(2), "intro": [], "sections": []}
                chapters.append(cur_ch)
                cur_sec, expected = None, num + 1
                continue
        if cur_sec is not None:
            cur_sec[2].append(line)
        elif cur_ch is not None:
            cur_ch["intro"].append(line)
        else:
            pre.append(line)
    return pre, chapters


# ------------------------------------------------------------------ markdown rendering

def take_pseudo(lines, i):
    """Pseudo-code: until a blank line, unless the text after the blank is still indented."""
    block = []
    while i < len(lines):
        l = lines[i]
        if not l.strip():
            j = i
            while j < len(lines) and not lines[j].strip():
                j += 1
            if j < len(lines) and lines[j][:1].isspace() and not is_header(lines[j]):
                block += lines[i:j]
                i = j
                continue
            break
        if is_header(l):
            break
        block.append(l)
        i += 1
    return block, i


def looks_like_code(l):
    s = l.strip()
    return bool(s) and is_ascii(s) and (bool(re.search(r"[;{}]", s)) or s.startswith(("#include", "//", "using ")))


def is_code_line(l):
    """Indented, pure ASCII, or containing C++ punctuation / a // comment (comments may have diacritics)."""
    return l[:1].isspace() or is_ascii(l) or bool(re.search(r"[;{}]|//", l))


def take_code(lines, i):
    """C++ code run; stops at a prose line (column 0, Vietnamese, no code punctuation) or a heading."""
    block = []
    while i < len(lines):
        l = lines[i]
        if l.strip() and (not is_code_line(l) or SECTION.match(l) or PART.match(l)):
            break
        if not l.strip():
            j = i
            while j < len(lines) and not lines[j].strip():
                j += 1
            if j < len(lines) and looks_like_code(lines[j]) and not SECTION.match(lines[j]):
                block += lines[i:j]
                i = j
                continue
            break
        block.append(l)
        i += 1
    while block and not block[-1].strip():
        block.pop()
    return block, i


def table_md(rows):
    cells = [[c.strip() for c in r.split("|")] for r in rows]
    width = max(len(r) for r in cells)
    cells = [r + [""] * (width - len(r)) for r in cells]
    out = ["| " + " | ".join(cells[0]) + " |", "|" + "---|" * width]
    out += ["| " + " | ".join(r) + " |" for r in cells[1:]]
    return out


def render(lines, cpp_name=None, code_ref=None):
    """Render a block of plain text to markdown. Returns (markdown_lines, inline_code_blocks)."""
    out, codes, i = [], [], 0

    def blank():
        if out and out[-1] != "":
            out.append("")

    while i < len(lines):
        l = lines[i].rstrip()
        s = l.strip()
        if not s:
            blank()
            i += 1
            continue
        p = PART.match(s)
        if p:
            kind, rest = p.group(1), p.group(2).strip()
            blank()
            if kind == "Mã giả":
                out.append("**Mã giả.**")
                block, i = take_pseudo(lines, i + 1)
                out += ["```text"] + block + ["```"]
                continue
            if kind == "Lời văn":
                out.append("**Lời văn.**")
                i += 1
                continue
            # Code part ("Code.", "Code. (Mở Github)", "Code cho đồ thị vô hướng", ...)
            rest = rest.replace("(Mở Github)", "").strip()
            label = "**Code" + (" " + rest.rstrip(".") if rest and not rest.startswith("(") else "") + ".**"
            note = f" {rest}" if rest.startswith("(") else ""
            i += 1
            # prose right after "Code." (e.g. "Nhập: n, rồi ma trận ...") is kept as a note
            lead = []
            while i < len(lines) and not is_header(lines[i]) and \
                    (not lines[i].strip() or not is_code_line(lines[i])):
                if lines[i].strip():
                    lead.append(lines[i].strip())
                i += 1
            block, i = take_code(lines, i)
            codes.append(block)
            if cpp_name:
                out.append(f"{label}{note} Code chuẩn đã chạy thử: [{cpp_name}]({cpp_name}).")
                if lead:
                    out += [""] + lead
            else:
                out.append(f"{label}{note} (mục này không có file .cpp riêng)")
                if lead:
                    out += [""] + lead
                out += ["", "```cpp"] + block + ["```"]
            continue
        if " | " in s:
            rows = []
            while i < len(lines) and " | " in lines[i]:
                rows.append(lines[i].strip())
                i += 1
            blank()
            out += table_md(rows)
            blank()
            continue
        if looks_like_code(l) and not LIST.match(l) and take_code(lines, i)[1] > i:
            block, i = take_code(lines, i)
            blank()
            out += ["```cpp"] + block + ["```"]
            blank()
            continue
        m = LIST.match(l)
        if m:
            indent, marker, text = m.groups()
            level = len(indent) // 2
            marker = "-" if marker in "–-" else marker
            out.append("   " * level + f"{marker} {text}")
            i += 1
            continue
        # short standalone line -> sub-heading
        nxt = lines[i + 1] if i + 1 < len(lines) else ""
        if len(s) <= 70 and not s.endswith((".", ",", ";")) and (
                s.endswith(":") or not nxt.strip() or LIST.match(nxt) or " | " in nxt or looks_like_code(nxt)):
            blank()
            out.append(f"**{s}**")
            i += 1
            continue
        out.append(s)
        i += 1
    while out and out[-1] == "":
        out.pop()
    return out, codes


def slug(title):
    s = re.sub(r"\(.*?\)", "", strip_accents(title))
    s = re.sub(r"[^A-Za-z0-9]+", "_", s).strip("_")
    return "_".join(s.split("_")[:5])


def code_lines(text):
    """Normalised code lines for comparison (spacing and comment diacritics ignored)."""
    return [re.sub(r"\s+", " ", strip_accents(l)).strip() for l in text if l.strip()]


# ------------------------------------------------------------------ main

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--course", required=True)
    ap.add_argument("--source-root", required=True)
    ap.add_argument("--out", help="thư mục ghi (mặc định courses/<id>/algorithms)")
    a = ap.parse_args()

    cdir = COURSES_DIR / a.course
    cfg = json.loads((cdir / "course.json").read_text(encoding="utf-8"))
    root = Path(a.source_root)
    src = root / cfg["sources"]["theory_md"]
    algo_src = root / cfg["sources"]["algorithms_dir"]
    notes = cfg.get("theory_notes", {})
    cpps = {}
    for p in algo_src.glob("*.cpp"):
        m = re.match(r"^(\d+(?:\.\d+)*)_", p.stem)
        if m:
            cpps[m.group(1)] = p

    text = read_text(src).replace("\xa0", " ").replace("\u200b", "").replace("\t", "    ")
    pre, chapters = split_document(strip_toc(text.splitlines()))
    out_dir = Path(a.out) if a.out else cdir / "algorithms"
    out_dir.mkdir(parents=True, exist_ok=True)
    for old in out_dir.glob("*.md"):
        old.unlink()

    written, mismatches = [], []
    titles = {sid: t for ch in chapters for sid, t, _ in ch["sections"]}

    def write(name, text):
        (out_dir / name).write_text(text.rstrip() + "\n", encoding="utf-8")
        written.append(name)

    for ch in chapters:
        intro_md, _ = render(ch["intro"])
        if ch["id"] == "0":
            body = intro_md + ([""] + [notes["0"]] if "0" in notes else [])
            write("conventions.md", f"# {ch['title']}\n\n" + "\n".join(body))
            continue
        if "tra nhanh" in strip_accents(ch["title"]).lower():
            write("cheatsheet.md", f"# {ch['title']}\n\n" + "\n".join(intro_md))
            continue
        for k, (sid, title, body) in enumerate(ch["sections"]):
            cpp_id = sid if sid in cpps else (sid + ".1" if sid + ".1" in cpps else None)
            file_id = cpp_id or sid
            # "2.1.2. Đồ thị có hướng" -> prefix the parent's title so the file stands alone
            parent = sid.rsplit(".", 1)[0]
            if parent in titles and parent != sid and len(title) < 30:
                title = f"{titles[parent]} – {title}"
            if cpp_id and cpp_id != sid:
                first = next((l.strip() for l in body if l.strip()), "")
                if len(first) < 30 and not PART.match(first):
                    title = f"{title} – {first}"
                    body = body[body.index(next(l for l in body if l.strip())) + 1:]
            md, codes = render(body, cpps[cpp_id].name if cpp_id else None)
            head = f"# {file_id}. {title}\n\n"
            if k == 0 and any(l.strip() for l in intro_md):
                quoted, prev = [], None
                for l in intro_md:  # keep each intro line as its own paragraph inside the quote
                    is_row = l.startswith("|")
                    if l and prev and not (is_row and prev.startswith("|")):
                        quoted.append(">")
                    quoted.append(("> " + l) if l else ">")
                    prev = l or None
                head += "> Chương " + ch["id"] + f" – {ch['title']}\n>\n" + "\n".join(quoted) + "\n\n"
            extra = notes.get(sid) or notes.get(file_id)
            text = head + "\n".join(md) + (f"\n\n{extra}" if extra else "")
            name = (cpps[cpp_id].stem if cpp_id else f"{sid}_{slug(title)}") + ".md"
            write(name, text)
            if cpp_id:  # report doc code that is not in the tested .cpp
                ref = set(code_lines(read_text(cpps[cpp_id]).splitlines()))
                missing = [l for b in codes for l in code_lines(b) if l not in ref]
                if missing:
                    mismatches.append((name, missing))

    print(f"{a.course}: {len(written)} file -> {out_dir}")
    for n in written:
        print("  ", n)
    if mismatches:
        print("\nCode trong tài liệu KHÁC file .cpp (file .md đang trỏ tới .cpp):")
        for n, miss in mismatches:
            print(f"  {n}: {len(miss)} dòng, vd: {miss[0][:90]}")


if __name__ == "__main__":
    main()
