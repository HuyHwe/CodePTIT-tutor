# Chế độ 1 – Gợi ý sửa code (hint)

Dùng khi SV bí, code chưa chạy, hoặc hỏi chung "giúp em bài này".

## Các bước
1. **Xác định bài** (`find_problem.py`), đọc đề `problems/<mã>.md` và mục thuật toán mẫu được gắn (`algorithms/<mục>_*.md`).
2. **Phân loại tình trạng code của SV**:

   | Tình trạng | Làm gì |
   |---|---|
   | Chưa có code / mới có ý tưởng | Hỏi SV định dùng thuật toán nào. Chỉ mục giáo trình phù hợp (vd "bài này là 1.7 Quay lui tổ hợp + điều kiện X[1] = t"). Gợi ý chia bài: nhập → thuật toán → xuất. **Không viết code thay SV.** |
   | Code dở dang | So cấu trúc với **mã giả** trong thuật toán mẫu, chỉ bước còn thiếu (vd "đã có chọn min, còn thiếu bước nới lỏng"). |
   | Lỗi biên dịch | Chạy `run_tests.py`, đọc lỗi, giải thích lỗi đầu tiên bằng lời dễ hiểu (lỗi C++ thường kéo theo nhiều lỗi giả phía sau). Đây là lỗi kỹ thuật: được chỉ thẳng cách sửa. |
   | Biên dịch được | Chạy `run_tests.py --stress 300` rồi xử lý theo bảng dưới. |

3. **Xử lý theo kết quả chạy**:

   | Kết quả | Hướng gợi ý |
   |---|---|
   | Tất cả ĐÚNG (cả test ngẫu nhiên) | Báo SV code đúng trên mọi test đã thử. Nhắc kiểm tra `CẢNH BÁO I/O` nếu có (đề yêu cầu `freopen`). Có thể gợi ý cải thiện (độ phức tạp, giới hạn n lớn) nếu SV muốn. |
   | Sai test mẫu | Bắt đầu bậc 1 với test mẫu (SV đã thấy test này trong đề). |
   | Đúng test mẫu, sai test ngẫu nhiên | Đưa input nhỏ mà script tìm được – đây là gợi ý giá trị nhất. Kiểm tra trước `pitfalls.md` (tràn số, thứ tự khi bằng nhau, trường hợp biên). |
   | QUÁ THỜI GIAN | Kiểm tra vòng lặp vô hạn (điều kiện dừng của Sinh(), quay lui thiếu điều kiện dừng, `while` không tăng biến) trước khi nghĩ tới độ phức tạp. |
   | LỖI KHI CHẠY | Thường là truy cập mảng ngoài phạm vi (đánh số từ 1 mà khai báo `a[n]`), đệ quy vô hạn, chia cho 0. Chỉ dòng nghi ngờ bằng chạy tay input nhỏ. |
   | CẢNH BÁO I/O | Lỗi kỹ thuật: nói thẳng cần `freopen("XX.INP", "r", stdin); freopen("XX.OUT", "w", stdout);` với đúng tên file đề yêu cầu. |

4. **Trả lời** theo khung trong `pedagogy.md`, bắt đầu ở bậc phù hợp.
5. Sau khi SV sửa: chạy lại `run_tests.py` trên file mới để xác nhận, rồi báo kết quả.

## Lưu ý
- Output được so như CodePTIT: bỏ qua khoảng trắng và dòng thừa. Không góp ý SV về dấu cách hay dòng trống.
- Nếu SV dùng cách làm khác giáo trình nhưng đúng (vd Dijkstra dùng `priority_queue`, Kruskal không dùng DSU): **chấp nhận**, chỉ góp ý nếu kết quả hoặc thứ tự output khác đề yêu cầu.
- Ghi chú `notes` của bài (vd test gốc trong đề sai) cần báo cho SV ngay từ đầu.
