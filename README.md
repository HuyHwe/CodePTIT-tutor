# codeptit-tutor – Trợ giảng TRR1 / TRR2 cho coding agent

Skill (chuẩn [Agent Skills](https://agentskills.io)) giúp sinh viên làm bài CodePTIT môn **Toán rời rạc 1** và **Toán rời rạc 2**:

- **Gợi ý sửa code** theo 4 bậc, không làm hộ.
- **So sánh** cách làm của bạn với lời giải chuẩn (mô tả bằng lời, không lộ code).
- **Chỉ ra lỗi logic**: chạy code của bạn với test mẫu và hàng trăm test ngẫu nhiên nhỏ, tìm input nhỏ nhất làm sai.

Hiện có 31 bài TRR1, 40 bài TRR2, 33 thuật toán mẫu kèm lý thuyết (lời văn + mã giả).

## Yêu cầu
- `python3` ≥ 3.8 (Windows: `python`)
- Trình biên dịch C++: `g++` (Windows: MinGW-w64) hoặc `clang++` (macOS: `xcode-select --install`). macOS không có sẵn `<bits/stdc++.h>`, skill đã kèm bản thay thế.

## Cài đặt
Copy cả thư mục `codeptit-tutor/` vào thư mục skills của agent:

| Agent | Vị trí |
|---|---|
| Claude Code (mọi project) | `~/.claude/skills/codeptit-tutor/` |
| Claude Code (một project) | `<project>/.claude/skills/codeptit-tutor/` |
| Codex CLI | `~/.codex/skills/codeptit-tutor/` |
| Agent khác hỗ trợ Agent Skills | Xem tài liệu của agent (thường là `.agents/skills/` hoặc tương tự) |

Kiểm tra máy chạy được:
```
python3 ~/.claude/skills/codeptit-tutor/scripts/run_tests.py --problem TRR5001 --self-check
```

## Cách dùng
Mở thư mục bài làm trong agent và hỏi tự nhiên, ví dụ:
- "Bài TRR5001 em làm file `dijkstra.cpp` sai test 1, gợi ý giúp em"
- "So code `quaylui.cpp` của em với lời giải chuẩn bài TRR1_3024"
- "Code `kruskal.cpp` đúng test mẫu mà nộp vẫn sai, lỗi logic ở đâu?"
- "Cho em code sửa luôn" (chỉ khi bạn thật sự muốn: skill sẽ sửa trên code của bạn)

Tự chạy script không cần agent:
```
python3 scripts/find_problem.py "dinh tru bfs"
python3 scripts/run_tests.py --problem TRR2024 --student bai.cpp --stress 300
```
Output được so như CodePTIT: bỏ qua khoảng trắng và dòng thừa.

## Cấu trúc
```
SKILL.md                 hướng dẫn cho agent (router)
references/              thang gợi ý + 3 quy trình (hint / compare / logic-bug) + cách thêm môn
courses/<môn>/           index.json, problems/, solutions/ (lời giải chuẩn), algorithms/ (lý thuyết + code mẫu), pitfalls.md
scripts/                 find_problem.py, run_tests.py, generators.py, include/ (bits/stdc++.h thay thế)
scripts/maintainer/      build_course.py, build_theory.py (cho người bảo trì)
```

## Bảo trì / thêm môn mới
Xem [references/adding-a-course.md](references/adding-a-course.md). Build lại từ nguồn:
```
for c in trr1 trr2; do python3 scripts/maintainer/build_theory.py --course $c --source-root "<thư mục gốc>"; done
python3 scripts/maintainer/build_course.py --all --source-root "<thư mục gốc>"
python3 scripts/run_tests.py --self-check-all
```

Nội dung lời giải và tài liệu: Đức Huy ([fanpage](https://www.facebook.com/thodayptit/)). Chỉ dùng cho mục đích học tập.
