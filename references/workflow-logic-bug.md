# Chế độ 3 – Chỉ ra lỗi logic (logic-bug)

Dùng khi SV hỏi "sai ở đâu", "sao test này sai". Mục tiêu: chỉ ra **bước đầu tiên** mà trạng thái chương trình của SV khác với trạng thái đúng, kèm input nhỏ chứng minh.

## Các bước
1. **Tìm input làm sai, càng nhỏ càng tốt**
   ```
   python3 "$SKILL_DIR/scripts/run_tests.py" --problem <MÃ> --student <bai.cpp> --stress 500
   ```
   - Ưu tiên test ngẫu nhiên đã được thu nhỏ (script tự thu nhỏ) hơn test mẫu nếu nó nhỏ hơn.
   - SV đưa sẵn test bị sai → dùng `--input <file>` để xác nhận và lấy output đúng từ lời giải chuẩn.
   - Muốn nhỏ hơn nữa: tự viết input nhỏ hơn (bỏ đỉnh, bỏ cạnh, giảm n) rồi chạy lại `--input` cho tới khi vẫn còn sai.

2. **Đối chiếu với `pitfalls.md`** của môn: tìm dòng có triệu chứng giống (vd "đúng tổng trọng số, sai thứ tự cạnh" → sort khi bằng nhau). Đây chỉ là **giả thuyết**, phải kiểm chứng ở bước 3.

3. **Định vị bước sai đầu tiên** bằng cách chạy tay hoặc thêm lệnh in tạm:
   - Copy code SV và lời giải chuẩn vào thư mục tạm (không sửa file của SV), thêm `cerr << ...` in trạng thái chính sau mỗi bước: `d[]` sau mỗi vòng (Dijkstra/Bellman/Floyd), thứ tự đỉnh được thăm (DFS/BFS), `X[]` mỗi lần Result (sinh/quay lui), `delta`, `FOPT`, cận `g` (nhánh cận), `par[]`/danh sách cạnh đã chọn (Kruskal).
   - Biên dịch, chạy cả hai với cùng input (`g++ -std=c++17 -idirafter "$SKILL_DIR/scripts/include" x.cpp -o x && ./x < in.txt`; nếu code dùng `freopen` thì tạo file `XX.INP` trong thư mục tạm).
   - So từng bước: bước đầu tiên khác nhau chính là chỗ cần chỉ ra.

4. **Báo cáo cho SV** (theo bậc trong `pedagogy.md`; chế độ này bắt đầu ở bậc 2):
   - Input nhỏ nhất làm sai, output mong đợi, output của SV.
   - Bước/dòng trong **code của SV** nơi trạng thái bắt đầu khác (vd "ở vòng lặp thứ 2, `d[3]` của bạn vẫn là 8, đáng lẽ đã được nới lỏng thành 3 qua đỉnh 4").
   - Nguyên nhân bằng lời (vd "vì đỉnh 4 không được cố định nhãn nên vòng sau lại chọn lại đỉnh 4").
   - Không đưa code sửa trừ khi SV yêu cầu.

## Mẹo theo dạng bài
| Dạng | Trạng thái nên in để so |
|---|---|
| Sinh cấu hình | Cấu hình trước và sau mỗi lần gọi Sinh(); vị trí i tìm được |
| Quay lui | Mỗi lần gọi Try(i): i, X[1..i], mảng đánh dấu |
| Nhánh cận | Mỗi nút: k, delta, cận g, FOPT; nhánh nào bị cắt |
| DFS/BFS | Thứ tự đỉnh được thăm, `truoc[]`, nội dung hàng đợi/ngăn xếp |
| Trụ/cầu | Số TPLT ban đầu, số TPLT sau khi bỏ từng đỉnh/cạnh |
| Euler | Nội dung stack và CE mỗi bước, ma trận sau khi xóa cạnh |
| Đường đi ngắn nhất | `d[]` (và `truoc[]`/`p[][]`) sau mỗi vòng ngoài |
| Cây khung | Cạnh được xét, có được nhận không, `par[]` |

## Không làm
- Không kết luận chỉ bằng đọc code khi chưa chạy được input minh chứng.
- Không liệt kê mọi khác biệt với lời giải chuẩn: chỉ lỗi **gây ra sai** (khác biệt về cách viết thuộc chế độ compare).
- Không sửa luôn hộ nhiều lỗi một lúc: chỉ lỗi đầu tiên, chạy lại sau khi SV sửa rồi mới sang lỗi tiếp.
