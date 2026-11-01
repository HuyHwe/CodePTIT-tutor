# Bảng tra nhanh trước giờ thi

| Thuật toán | Dùng khi | Câu chốt cần nhớ | Ma trận | DS kề | DS cạnh |
|---|---|---|---|---|---|
| DFS | Duyệt sâu, làm nền ứng dụng | Gặp đỉnh kề chưa xét là đi vào ngay | O(n²) | O(n + m) | O(n·m) |
| BFS | Duyệt rộng, đường ít cạnh nhất | Đánh dấu lúc đẩy vào, không phải lúc lấy ra | O(n²) | O(n + m) | O(n·m) |
| Đếm TPLT | Số mảnh của đồ thị | Mỗi lần phải gọi DFS mới = thêm 1 TPLT | O(n²) | O(n + m) | O(n·m) |
| Đường đi s→t | Có đường hay không, in đường | Ghi truoc[v] = u, lần ngược từ t | O(n²) | O(n + m) | O(n·m) |
| Liên thông mạnh | Đồ thị có hướng | DFS từ mọi đỉnh đều phải thăm đủ n | O(n³) | O(n·(n + m)) | O(n²·m) |
| Đỉnh trụ | Bỏ đỉnh làm tăng TPLT | vs[u] = 1 trước rồi đếm lại TPLT | O(n³) | O(n·(n + m)) | O(n²·m) |
| Cạnh cầu | Bỏ cạnh làm tăng TPLT | Xóa cạnh, đếm, trả cạnh | O(m·n²) | O(m·(n + m)) | O(n·m²) |
| Định chiều | Vô hướng → có hướng liên thông mạnh | Liên thông và không có cầu | O(m·n²) | O(m·(n + m)) | O(n·m²) |
| Kiểm tra Euler | Có chu trình / đường đi Euler không | Liên thông + 0 bậc lẻ (Euler) / 2 bậc lẻ (nửa) | O(n²) | O(n + m) | O(n·m) |
| Tìm Euler | In chu trình / đường đi Euler | Xem top: còn cạnh thì đẩy và xóa cạnh, hết cạnh thì pop sang CE; lật CE | O(n·m) | O(n + m) | O(m²) |
| Hamilton | Chu trình qua mọi đỉnh | Quay lui; k = n + 1 và y = v0 thì ghi nhận | O(n!) | O(n!) | O(m·n!) |

| Thuật toán | Dùng khi | Câu chốt cần nhớ | Ma trận | DS kề | DS cạnh |
|---|---|---|---|---|---|
| Dijkstra | 1 nguồn, trọng số ≥ 0 | Chọn min nhãn tạm → cố định → nới lỏng | O(n²) | O(n²) | O(n·m) |
| Bellman-Ford | 1 nguồn, có cạnh âm | n − 2 vòng nới lỏng mọi cặp; vòng thêm còn giảm = chu trình âm | O(n³) | O(n·m) | O(n·m) |
| Floyd | Mọi cặp đỉnh | Vòng k ngoài cùng; p[i][j] = p[k][j] | O(n³) | O(n³) | O(n³) |
| Cây khung DFS/BFS | Cây khung bất kỳ | Đi sang đỉnh mới thì kết nạp cạnh vừa đi | O(n²) | O(n + m) | O(n·m) |
| Kruskal | Cây khung nhỏ nhất, đồ thị thưa | Sắp cạnh tăng dần, Find(u) != Find(v) thì lấy | O(m log m) | O(m log m) | O(m log m) |
| Prim | Cây khung nhỏ nhất, đồ thị dày | Dijkstra với a[u][v] thay cho d[u] + a[u][v] | O(n²) | O(n²) | O(n·m) |
| Ford-Fulkerson | Luồng cực đại s → t | BFS trên a > 0; δ = min; thuận −= δ, nghịch += δ | O(val · n²) | O(val · (n + m)) | O(val · n · m) |

**Lỗi hay gặp khi code:**
- Quên memset(vs, 0, sizeof vs) giữa các lần DFS (liên thông mạnh, trụ, cầu, kosaraju…).
- Với đồ thị vô hướng: quên gán a[v][u] khi nhập, hoặc quên xóa a[t][s] khi tìm Euler.
- Trọng số âm mà thiếu điều kiện < INF (Bellman-Ford, Floyd).
- Ma trận đề cho dùng 0 làm "không có cạnh" mà quên doiINF() trước Dijkstra, Prim, Floyd.
- Floyd đặt vòng k vào trong, hoặc Kruskal quên khởi tạo par[i] = i.
