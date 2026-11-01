# Lỗi hay gặp – TRR1

Dùng khi chẩn đoán: khớp **triệu chứng** (output sai thế nào) với **nguyên nhân**, rồi kiểm chứng bằng cách chạy test, đừng đoán.

## Chung cho mọi bài (CodePTIT)
| Triệu chứng | Nguyên nhân hay gặp |
|---|---|
| Đúng test mẫu, sai test ẩn với số lớn | Tràn `int`: tích hai số ≤ 2^18 (BCNN, n·m), 2^n với n ≤ 50, C(n, k) với n ≤ 50 → dùng `long long`; dịch bit phải viết `1LL << n` chứ không phải `1 << n` |
| Thiếu/thừa **số** ở output (vd in dòng 2 khi k = 0) | Khoảng trắng và dòng thừa **không** ảnh hưởng (CodePTIT bỏ qua), nhưng in thừa một giá trị là sai. Xem đề: "k > 0 thì mới in dòng 2" |
| In thêm chữ ("Ket qua:", "Nhap n:") | Mọi `cout` hướng dẫn nhập đều bị chấm là sai |
| Mảng đánh số từ 1 nhưng khai báo vừa đúng `X[n]` | Truy cập `X[n]` ngoài mảng → khai báo dư (`X[n + 5]`) |

## Logic, tập hợp (TRR1_10xx)
- Phương trình: **quên trường hợp suy biến** a = 0 (thành bậc nhất), a = b = 0 (vô số nghiệm nếu c = 0, vô nghiệm nếu c ≠ 0).
- Nhầm dấu so sánh: "nghiệm âm" là `< 0`; với TRR1_1011 (đặt y = x²) cần `y >= 0` (có `=`), không phải `> 0`.
- Bậc hai: quên xét Δ < 0; chỉ kiểm tra một nghiệm.
- Tập hợp: input xâu nhị phân **có dấu cách** giữa các chữ số (`0 1 0 0 1`) → đọc từng số `int`, đừng đọc cả dòng bằng `string`. Quên in dòng 2 khi k > 0 / in dòng 2 rỗng khi k = 0.

## Đếm (TRR1_20xx)
- Bù trừ (TRR1_2002): đếm trên đoạn [a, b] = f(b) − f(a − 1), hay quên "− 1"; BCNN tính `k / UCLN * m` để không tràn.
- Truy hồi xâu nhị phân (TRR1_2011, 2014): sai điều kiện biên F[i] với i < k và i = k; "chứa k số 1 liên tiếp" = 2^n − (không chứa).
- Đếm phân số (TRR1_2009): quên phân số 0/1; dùng UCLN cho từng cặp (O(n²)) vẫn qua nhưng sàng φ nhanh hơn.

## Liệt kê: sinh và quay lui (TRR1_30xx)
| Triệu chứng | Nguyên nhân hay gặp |
|---|---|
| Thiếu cấu hình cuối cùng | Dùng `while (Sinh()) Result();` thay vì `do Result(); while (Sinh());` |
| Không dừng / lặp vô hạn | Sinh() không trả về false ở cấu hình cuối (điều kiện `i == 0`) |
| Sinh tổ hợp ra số > n hoặc trùng | Sai giới hạn `X[i] == n − k + i`; quên đặt lại đoạn sau `X[j] = X[i] + j − i` |
| Sinh hoán vị sai thứ tự | Quên lật đoạn `X[i+1..n]` sau khi đổi chỗ, hoặc tìm j sai (`X[j] < X[i]` thay vì `X[j] > X[i]`) |
| Liệt kê "trước" (TRR1_3006, 3008, 3016) sai | Phải làm **ngược hoàn toàn** từng bước của Sinh() (đổi vai trò 0↔1, tìm X[i] > X[i+1]...), không chỉ đảo một chỗ |
| "Liệt kê một phần": in sai số dòng | Khác nhau từng bài: TRR1_3015 hết xâu thì in 0 **rồi dừng**; TRR1_3011 hết hoán vị thì **mọi dòng còn lại** đều in 0 – đọc đề và test |
| Quay lui hoán vị in trùng số | Quên đánh dấu `vs[j] = 1` hoặc quên bỏ đánh dấu `vs[j] = 0` sau khi gọi đệ quy |
| Quay lui tổ hợp sai | Quên `X[0] = 0`; vòng `j` sai cận `X[i−1] + 1 .. n − k + i` |
| Có điều kiện (X[1] = t, X[k] = t, k vị trí cố định) | Kiểm tra điều kiện quá muộn (sau khi đã liệt kê hết) → đúng nhưng chậm; hoặc kiểm tra sai chỉ số |

## Tối ưu: duyệt toàn bộ, nhánh cận (TRR1_40xx, LT004)
| Triệu chứng | Nguyên nhân hay gặp |
|---|---|
| Người du lịch: chi phí nhỏ hơn đáp án | Quên cộng đoạn quay về `c[x[n]][1]` |
| Cái túi: chọn đúng giá trị nhưng in phương án khác | Thứ tự thử: đáp án chuẩn thử `x[i] = 1` trước `0` (TRR1_4001) – nhiều phương án cùng tối ưu thì lấy phương án gặp trước |
| Cái túi nhánh cận sai | Quên sắp xếp v/w giảm dần; cận tính bằng **chia nguyên** (phải `double`); quên hoàn trả `delta` và `b` khi quay lui |
| Nhánh cận cho kết quả kém hơn duyệt toàn bộ | Cận sai chiều (bài min dùng `g < FOPT`, bài max dùng `g > FOPT`) hoặc cận không phải cận dưới thật (vd. `(n − k)·cmin` thay vì `(n − k + 1)·cmin` cho du lịch) |
| Phân việc "năng suất lớn nhất" (TRR1_4004, 4009) | Giữ nguyên code tìm min: phải đổi FOPT = −∞ và đảo dấu so sánh (cả cận) |
| LT004 in thiếu phương án | Đề yêu cầu in **tất cả** phương án tối ưu: phải lưu danh sách, reset khi tìm được giá trị tốt hơn hẳn |
| TLE | Duyệt toàn bộ n! với n lớn → dùng nhánh cận; hoặc tính lại tổng từ đầu ở mỗi lá thay vì cộng dồn `delta` |

## Dirichlet (TRR1_50xx)
- Công thức "xấu nhất + 1": quên "+ 1" hoặc cộng thừa.
- Đếm số lượng "loại xấu" sai biên: số lẻ trong [1, n] là `(n + 1) / 2`, số chia 4 dư 2 là `(n + 2) / 4`.
- Quên trường hợp không chọn được (kết quả > tổng số phần tử thì in 0 – TRR1_5021).
