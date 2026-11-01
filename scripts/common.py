"""Helpers shared by the codeptit-tutor scripts (Python 3.8+, standard library only)."""
import json
import re
import sys
import unicodedata
from pathlib import Path

SKILL_ROOT = Path(__file__).resolve().parent.parent
COURSES_DIR = SKILL_ROOT / "courses"

# Windows consoles often default to a legacy code page; force UTF-8 so Vietnamese prints.
for _stream in (sys.stdout, sys.stderr):
    try:
        _stream.reconfigure(encoding="utf-8")
    except (AttributeError, ValueError):
        pass


def load_json(path):
    with open(path, encoding="utf-8") as f:
        return json.load(f)


def load_registry():
    return load_json(COURSES_DIR / "registry.json")


def load_index(course_id):
    return load_json(COURSES_DIR / course_id / "index.json")


def all_problems():
    """Yield (course_id, problem_entry) for every problem in every course."""
    for course in load_registry()["courses"]:
        idx = load_index(course["id"])
        for p in idx["problems"]:
            yield course["id"], p


def strip_accents(text):
    text = text.replace("đ", "d").replace("Đ", "D")
    text = unicodedata.normalize("NFD", text)
    return "".join(c for c in text if unicodedata.category(c) != "Mn")


def norm_code(text):
    """'trr1-2002', 'TRR1_2002', 'trr1 2002' -> 'TRR12002' for loose code matching."""
    return re.sub(r"[^A-Z0-9]", "", strip_accents(text).upper())


def read_text(path):
    data = Path(path).read_bytes()
    for enc in ("utf-8-sig", "cp1258", "latin-1"):
        try:
            return data.decode(enc)
        except UnicodeDecodeError:
            continue
    return data.decode("utf-8", errors="replace")


# ---------------------------------------------------------------- test parsing

_TEST_HDR = re.compile(r"^\s*test(\s*case)?\b.*$", re.I)
_INPUT_HDR = re.compile(r"^\s*(input|đầu vào|dau vao)\s*:\s*(.*)$", re.I)
_OUTPUT_HDR = re.compile(r"^\s*(expected\s+output|output|đầu ra|dau ra)\s*:\s*(.*)$", re.I)


def _trim_blank(lines):
    while lines and not lines[0].strip():
        lines.pop(0)
    while lines and not lines[-1].strip():
        lines.pop()
    return lines


def parse_test_block(text):
    """Parse 'Test 1 / input: / expected output:' style text into a list of tests.

    Returns [{"name", "input", "output"}]. Text outside input/output sections is ignored.
    """
    tests, cur, mode, name = [], None, None, None

    def flush():
        if cur and (cur["input"] or cur["output"]):
            cur["input"] = "\n".join(_trim_blank(cur["input"])) + "\n"
            cur["output"] = "\n".join(_trim_blank(cur["output"]))
            tests.append(cur)

    for raw in text.splitlines():
        line = raw.rstrip()
        if _TEST_HDR.match(line) and mode != "input":
            name = line.strip()
            continue
        m = _INPUT_HDR.match(line)
        if m:
            flush()
            cur = {"name": name or f"Test {len(tests) + 1}", "input": [], "output": []}
            name, mode = None, "input"
            if m.group(2).strip():
                cur["input"].append(m.group(2).strip())
            continue
        m = _OUTPUT_HDR.match(line)
        if m and cur is not None:
            mode = "output"
            if m.group(2).strip():
                cur["output"].append(m.group(2).strip())
            continue
        if cur is None or mode is None:
            continue
        if line.strip().startswith("```"):
            continue
        cur[mode].append(line)
    flush()
    return tests


def tests_from_cpp(path):
    """Extract tests from the last /* ... */ comment block that mentions input/output."""
    src = read_text(path)
    blocks = re.findall(r"/\*(.*?)\*/", src, re.S)
    for block in reversed(blocks):
        if re.search(r"input\s*:", block, re.I) and re.search(r"output\s*:", block, re.I):
            return parse_test_block(block)
    return []


def tests_from_problem_md(path):
    """Fallback: parse '**Test Case:**' sections of a problem statement markdown file."""
    text = read_text(path)
    text = re.sub(r"\*\*(Test Case[^*]*)\*\*", r"\1", text)
    text = text.replace("Expected Output:", "expected output:")
    # Drop explanation lines ("Giải thích: ...") so they don't leak into outputs.
    text = "\n".join(l for l in text.splitlines() if not l.strip().lower().startswith("giải thích"))
    return parse_test_block(text)


# ---------------------------------------------------------------- output compare

def normalize_output(text):
    lines = [l.rstrip() for l in text.replace("\r\n", "\n").replace("\r", "\n").split("\n")]
    return "\n".join(_trim_blank(lines))


def outputs_match(got, expected):
    """CodePTIT ignores extra spaces and blank/extra line breaks: compare token by token."""
    return got.split() == expected.split()


def find_problem_by_code(code):
    """Exact (loose) code lookup. Returns list of (course_id, entry)."""
    key = norm_code(code)
    return [(c, p) for c, p in all_problems() if norm_code(p["code"]) == key]
