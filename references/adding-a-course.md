# Thêm môn học mới (dành cho người bảo trì)

Mỗi môn là một thư mục `courses/<id>/`. Nguồn gốc (đề, lời giải, thuật toán mẫu) để ở ngoài skill. Script build sẽ copy vào.

## 1. Chuẩn bị nguồn
| Nguồn | Yêu cầu |
|---|---|
| File đề `.md` | Mỗi bài một mục `## <số>. (<MÃ>) <Tên bài>`, có phần `**Test Case:**` |
| Thư mục lời giải | Mỗi bài một file `.cpp`, **tên bắt đầu bằng mã bài** (vd `TRR3_1001 Ten bai.cpp`). Dòng comment đầu: `// <MÃ>. <mô tả>`, có thể ghi `muc X.Y` / `Ap dung X.Y` để tự gắn mục thuật toán. Cuối file có block test: `/* Test 1 \n input: ... \n expected output: ... */` (hoặc `Input:/Output:`) |
| Thư mục thuật toán mẫu | File `<mục>_<Ten>.cpp` (vd `3.1_Dijkstra.cpp`), cũng có block test ở cuối |
| (Tùy chọn) Tài liệu lý thuyết | Văn bản thuần (export từ Google Docs): chương `3. Tên chương`, mục `3.1. Tên mục`, các phần `Lời văn.` / `Mã giả.` / `Code.`, bảng dạng `a | b | c`, gạch đầu dòng `–` |

## 2. Tạo `courses/<id>/course.json`
```json
{
  "id": "trr3",
  "name": "Tên môn",
  "code_patterns": ["TRR3_\\d{4}"],
  "sources": {
    "problems_md": "TRR3 CodePTIT/De Bai.md",
    "solutions_dir": "TRR3 CodePTIT",
    "algorithms_dir": "TRR3 Thuat toan",
    "theory_md": "Bộ thuật toán TRR3.md"
  },
  "algorithm_overrides": {"TRR3_1001": ["1.2", "1.5"]},
  "default_algorithms": {"TRR3_10": ["0"]},
  "topics": {"TRR3_10": "Tên chủ đề của nhóm bài có mã bắt đầu bằng TRR3_10"},
  "generators": {"TRR3_1001": "matrix_ud"}
}
```
- `code_patterns`: regex nhận mã bài ở **đầu tên file** lời giải. Mã phải khác các môn đã có.
- `algorithm_overrides`: gắn tay mục thuật toán khi comment `muc X.Y` không đủ hoặc mơ hồ.
- `generators`: tên hàm trong `scripts/generators.py` (xem `GENERATORS`). Input mới chưa có hàm phù hợp thì viết thêm một hàm `f(rng, size) -> str` sinh input **hợp lệ theo đề**, nhỏ (n ≤ ~8).

## 3. Build
```
# (nếu có tài liệu lý thuyết) tách theo mục thành algorithms/*.md – xem thử bằng --out <thư mục nháp>
python3 scripts/maintainer/build_theory.py --course trr3 --source-root "<thư mục chứa nguồn>"
# tạo problems/, solutions/, algorithms/*.cpp, index.json và cập nhật registry.json
python3 scripts/maintainer/build_course.py --course trr3 --source-root "<thư mục chứa nguồn>"
```
`build_theory.py` tạo lại toàn bộ `algorithms/*.md` mỗi lần chạy: **đừng sửa tay các file này**, hãy sửa file nguồn. Ghi chú riêng cần giữ (vd lưu ý cho một bài CodePTIT) đặt trong `course.json` → `"theory_notes": {"<mục>": "markdown"}` (`"0"` = conventions). Script báo nếu code trong tài liệu khác file `.cpp` của cùng mục.

## 4. Kiểm tra
```
python3 scripts/run_tests.py --self-check-all          # mọi lời giải + thuật toán mẫu phải đúng trên test của nó
python3 scripts/find_problem.py --list trr3
python3 scripts/run_tests.py --problem TRR3_1001 --check-generator 50       # generator sinh input hợp lệ
```
Viết thêm `courses/trr3/pitfalls.md` (triệu chứng → nguyên nhân) và cập nhật `description` trong `SKILL.md` để agent nhận ra môn mới.

## Cập nhật lời giải / đề của môn đã có
Sửa file nguồn rồi chạy lại `build_theory.py` (nếu đổi tài liệu lý thuyết) và `build_course.py`, sau đó `--self-check-all`. `pitfalls.md` viết tay, không bị script đụng tới.
