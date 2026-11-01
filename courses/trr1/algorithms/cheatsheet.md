# Bảng tra nhanh trước giờ thi

| Thuật toán | Cấu hình đầu → cuối / tập phương án | Câu chốt cần nhớ |
|---|---|---|
| Sinh nhị phân | 00…0 → 11…1 | Từ phải: 1 thành 0 đến khi gặp 0, đổi 0 đó thành 1 |
| Sinh tổ hợp | (1..k) → (n−k+1..n) | Tìm X[i] < n−k+i từ phải; tăng 1; phía sau nối tiếp tăng dần |
| Sinh hoán vị | (1..n) → (n..1) | Tìm X[i] < X[i+1] từ phải; đổi với số nhỏ nhất lớn hơn nó; lật đoạn sau |
| Quay lui nhị phân | X[i] ∈ {0, 1} | for j = 0..1 |
| Quay lui tổ hợp | X[i] từ X[i−1]+1 đến n−k+i | Nhớ X[0] = 0 |
| Quay lui hoán vị | X[i] ∈ 1..n, chưa dùng | Đánh dấu vs[j] trước khi gọi, bỏ đánh dấu sau khi gọi |
| Duyệt toàn bộ cái túi | Quay lui nhị phân | Đủ n vật mới kiểm tra W ≤ b và so V với FOPT |
| Duyệt toàn bộ du lịch | Hoán vị x[2..n], x[1] = 1 | Nhớ cộng đoạn quay về c[x[n]][1] |
| Duyệt toàn bộ phân việc | Hoán vị x[1..n] | S = Σ c[i][x[i]] |
| Nhánh cận cái túi 0/1 | Sắp v/w giảm dần, thử 1 trước 0 | Cận trên g = delta + b·v[k+1]/w[k+1] > FOPT thì đi tiếp |
| Nhánh cận du lịch | Như duyệt toàn bộ | Cận dưới g = delta + (n−k+1)·cmin < FOPT thì đi tiếp |
| Nhánh cận phân việc | Như duyệt toàn bộ | Cận dưới g = delta + (n−i)·cmin < FOPT thì đi tiếp |

**Lỗi hay gặp khi code:**
- Quay lui hoán vị quên bỏ đánh dấu vs[j] = 0 sau khi gọi đệ quy.
- Quay lui tổ hợp quên gán X[0] = 0.
- Nhánh cận quên hoàn trả delta (và b ở bài cái túi) khi quay lui.
- Cái túi: quên sắp xếp v/w giảm dần trước khi chạy, hoặc tính cận bằng phép chia nguyên (phải ép kiểu double).
- Người du lịch: quên cộng đoạn quay về thành phố 1.
