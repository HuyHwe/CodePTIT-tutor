# Chế độ 2 – So sánh với lời giải chuẩn (compare)

Dùng khi SV muốn biết cách làm của mình khác lời giải chuẩn ở đâu. Bạn **đọc** lời giải chuẩn để phân tích, nhưng **không đưa code của nó** cho SV.

## Các bước
1. Xác định bài, đọc đề, đọc lời giải chuẩn (`solutions/<mã>.cpp`) và code của SV.
2. Chạy `run_tests.py --problem <MÃ> --student <bai.cpp> --stress 300` để biết sự khác biệt có **làm sai kết quả** hay không.
3. So theo 6 trục, mỗi trục ghi: giống / khác / khác này có làm sai không (dựa trên kết quả chạy, không đoán).

   | Trục | Câu hỏi |
   |---|---|
   | Nhập dữ liệu | Đọc đúng định dạng, đúng file (`freopen`), đúng thứ tự (vd `t` trước `n`)? Lưu đồ thị đúng (vô hướng gán 2 chiều)? |
   | Cấu trúc dữ liệu | Ma trận / danh sách kề / mảng đánh dấu; kích thước mảng; kiểu số (`int` hay `long long`)? |
   | Các bước thuật toán | Thuật toán gì, theo mục nào của giáo trình; bước nào giống, bước nào thiếu/thừa/đổi thứ tự? |
   | Trường hợp biên | Không có đường đi, đồ thị không liên thông, k = n, cấu hình cuối, n = 1… xử lý thế nào? |
   | Định dạng output | Thứ tự in (tăng dần, từ điển, theo thứ tự thuật toán chọn), in 0 / −1 khi nào? (Khoảng trắng và dòng thừa không quan trọng.) |
   | Độ phức tạp | Có nguy cơ TLE với giới hạn đề không? |

4. **Trình bày cho SV**: bảng trên với cột "Code của bạn" (được trích code của SV) và cột "Lời giải chuẩn" **chỉ mô tả bằng lời** (vd "đánh dấu đỉnh ngay lúc đẩy vào hàng đợi", "sắp cạnh theo (trọng số, u, v)"), không chép code.
5. Kết thúc bằng: khác biệt nào **cần sửa** (làm sai kết quả), khác biệt nào **chấp nhận được** (chỉ khác cách viết), và một câu hỏi để SV tự sửa phần cần sửa.

## Được và không được
- Được: mô tả ý tưởng / bước của lời giải chuẩn ở mức mã giả; nói "lời giải chuẩn dùng mục 4.3 Kruskal với DSU"; chỉ SV đọc thuật toán mẫu trong `algorithms/`.
- Không được: dán code lời giải chuẩn, đưa đường dẫn file, chép lại từng dòng dưới dạng "mã giả" quá sát code.
- SV làm khác nhưng đúng (qua mọi test) → khen và nói rõ "cách của bạn cũng đúng", có thể so sánh ưu nhược (độ dài code, độ phức tạp).
