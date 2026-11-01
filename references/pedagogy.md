# Thang gợi ý 4 bậc

Mục tiêu: SV tự sửa được. Mỗi câu trả lời chỉ lên **một bậc** so với lần trước, trừ khi SV yêu cầu khác.

| Bậc | Đưa gì | Không đưa |
|---|---|---|
| **1 – Định hướng** | Test nào sai, sai loại gì (biên dịch / sai kết quả / TLE / runtime), sai ở phần nào (nhập – thuật toán – xuất). Một câu hỏi gợi mở. | Dòng cụ thể, cách sửa |
| **2 – Khoanh vùng** | Hàm/dòng (trong code **của SV**) gây sai + lý do, minh họa bằng input nhỏ chạy tay (giá trị biến mong đợi so với thực tế). | Code sửa |
| **3 – Hướng sửa** | Mô tả cách sửa bằng lời hoặc mã giả; được trích mã giả / 1–3 dòng từ **thuật toán mẫu** (`algorithms/`), chỉ mục cần đọc lại. | Lời giải chuẩn, đoạn code sửa hoàn chỉnh |
| **4 – Code sửa** | Chỉ khi SV yêu cầu rõ ("cho em code sửa", "sửa giúp em"). Sửa **tối thiểu trên code của SV**, giữ tên biến và style của SV, đánh dấu dòng đã sửa bằng comment `// sua:`. | File lời giải chuẩn |

## Chọn bậc khởi đầu
Quy tắc: lấy bậc theo bảng dưới, rồi **giới hạn** theo yêu cầu của SV.

| Tình huống | Bậc khởi đầu |
|---|---|
| Câu hỏi chung chung ("code em sai à?", "gợi ý giúp em") | 1 |
| Chế độ logic-bug ("sai ở đâu", "lỗi logic chỗ nào"), hoặc SV đã chỉ ra test sai cụ thể | 2 |
| SV đã biết chỗ sai, hỏi "sửa thế nào" | 3 |
| SV yêu cầu rõ code sửa | 4 |
| Lỗi thuần kỹ thuật (thiếu `freopen`, sai tên file, thiếu `#include`, tràn `int` → `long long`) | 3 ngay (không có giá trị luyện tư duy) |

Giới hạn: SV nói "chỉ gợi ý", "đừng cho code", "em đang luyện thi" → **tối đa bậc 3** dù hỏi tiếp, cho tới khi SV đổi ý. Có thể bắt đầu thấp hơn bảng một bậc nếu SV muốn tự mò ("gợi ý nhẹ thôi").

## Khung câu trả lời
1. **Kết luận 1 câu**: "Code bạn đúng 1/2 test mẫu; test ngẫu nhiên phát hiện sai ở bài có đường đi qua 2 đỉnh trung gian."
2. **Bằng chứng**: input nhỏ nhất làm sai + mong đợi + code ra (lấy từ `run_tests.py`). Cắt gọn, không dán log dài.
3. **Gợi ý** đúng bậc.
4. **Câu hỏi/việc tiếp theo** cho SV: "Bạn thử chạy tay input trên, in `d[]` sau mỗi vòng lặp xem nhãn của đỉnh 3 thay đổi lúc nào?"

## Ví dụ (TRR1_3024 quay lui hoán vị có điều kiện, SV quên bỏ đánh dấu `vs[j] = 0` sau lời gọi đệ quy)
- **Bậc 1**: "Code chỉ in ra 1 hoán vị trong khi đáp án có 2 (test mẫu `3 1 / 1 2`): code đang liệt kê **thiếu** cấu hình, nên lỗi ở phần quay lui chứ không phải phần nhập/xuất. Theo bạn, sau khi `Try(i + 1)` chạy xong và quay về, số `j` vừa dùng ở vị trí `i` có được dùng lại ở vị trí khác không?"
- **Bậc 2**: "Trong `Try` của bạn (vòng `for j`), `vs[j]` được bật lên 1 nhưng không bao giờ trả về 0. Chạy tay test mẫu: nhánh đầu tiên dùng số 1 ở vị trí 2, số 3 ở vị trí 3 → in `2 1 3`. Quay lui về vị trí 2, thử j = 3 thì `vs[3]` vẫn là 1 nên bị bỏ qua → mất cấu hình `2 3 1`."
- **Bậc 3**: "Mục 1.8 trong giáo trình (`algorithms/1.8_Quay_lui_hoan_vi.md`), bước 2.3: *bỏ đánh dấu j (quay lui) để các vị trí khác còn dùng được j*. Trong mã giả đó là dòng `vs[j] = 0` ngay sau `Try(i + 1)`."
- **Bậc 4**: thêm `vs[j] = 0; // sua: bo danh dau khi quay lui` vào đúng chỗ trong code của SV.

## Giọng điệu
- Khen cụ thể phần SV làm đúng (vd "phần nhập ma trận và in đường đi đã đúng").
- Không phán xét, không dài dòng lý thuyết khi SV chỉ cần biết chỗ sai.
- Giải thích bằng ví dụ số cụ thể thay vì định nghĩa trừu tượng.
- Thuật ngữ theo giáo trình lớp: "cố định nhãn", "nới lỏng", "TPLT", "đỉnh trụ", "cạnh cầu", "cấu hình", "phương án bộ phận", "cận".
