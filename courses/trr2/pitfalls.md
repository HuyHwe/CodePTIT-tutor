# Lỗi hay gặp – TRR2 (Lý thuyết đồ thị)

Dùng khi chẩn đoán: khớp **triệu chứng** với **nguyên nhân**, rồi kiểm chứng bằng cách chạy test, đừng đoán.

## Chung cho mọi bài (CodePTIT)
| Triệu chứng | Nguyên nhân hay gặp |
|---|---|
| Chạy máy đúng, nộp bị sai hết / "không có output" | Đề yêu cầu đọc **file** (`DT.INP`/`DT.OUT`, `TK`, `CT`, `CK`, `DN`, `BN`) mà code đọc bàn phím, hoặc sai tên file (`dt.inp`, `DT.IN`) |
| Thứ tự in khác đáp án dù "cũng đúng" | Đề chấm theo **một** thứ tự: duyệt đỉnh kề tăng dần (`for v = 1..n`), danh sách cạnh theo thứ tự từ điển (u < v), cạnh cây khung theo thứ tự thuật toán chọn |
| Lệch 1 đỉnh / truy cập ngoài mảng | Đỉnh đánh số 1..n nhưng code dùng 0..n−1 hoặc khai báo `a[n][n]` |
| Đúng test đầu, sai test sau (đa test hoặc gọi nhiều lần) | Không reset `vs[]`, `truoc[]`, bậc, biến đếm giữa các lần DFS/BFS |
| Bài có `t = 1` / `t = 2` | Chỉ xử lý một trường hợp; đọc input khác nhau theo t (vd TRR3001: t = 2 dòng 2 có thêm u) |

## Biểu diễn đồ thị (TRR10xx)
- Vô hướng: nhập danh sách cạnh phải gán **cả** `a[u][v]` và `a[v][u]`; có hướng chỉ `a[u][v]`.
- Bậc vô hướng = tổng hàng; có hướng: **bán bậc ra** = tổng hàng, **bán bậc vào** = tổng cột – đề TRR1012–1022 yêu cầu in `deg−` (vào) **trước**, `deg+` (ra) sau, mỗi đỉnh một dòng.
- Danh sách cạnh từ ma trận kề vô hướng: chỉ lấy `j > i`, nếu không mỗi cạnh in 2 lần; có hướng thì lấy mọi `a[i][j] = 1`.
- Ma trận liên thuộc: số dòng = n, số cột = m; có hướng dùng 1 (đỉnh đầu) / −1 (đỉnh cuối); cột (cung) xếp theo thứ tự từ điển; dòng đầu in `n m`.
- Trọng số: "không có cạnh" là **10000** (không phải 0); đường chéo = 0. Ghi chú: test gốc TRR1011 có ô (3,4) sai, đáp án chuẩn dùng 10000.
- Danh sách kề trong input (TRR1007–1009): mỗi dòng bắt đầu bằng **số lượng** đỉnh kề rồi mới đến các đỉnh.

## DFS / BFS và ứng dụng (TRR20xx)
| Triệu chứng | Nguyên nhân hay gặp |
|---|---|
| BFS ra thứ tự sai / đỉnh bị thăm 2 lần | Đánh dấu `vs[t] = 1` lúc **lấy ra** thay vì lúc **đẩy vào** hàng đợi |
| Đường đi DFS khác đáp án | Không duyệt đỉnh kề theo thứ tự tăng dần, hoặc dùng DFS ngăn xếp không đúng kiểu (mục 1.2) |
| In đường đi ngược | Lần `truoc[]` từ t về s phải **đảo ngược** trước khi in |
| "Không có đường đi" in sai | Đề quy định in 0 (hoặc giá trị riêng): kiểm tra `vs[t]` trước khi lần đường |
| Đếm TPLT sai | Gọi DFS mà không kiểm tra `!vs[u]` trước, hoặc tăng biến đếm trong DFS |
| Đỉnh trụ: mọi đỉnh đều là trụ / không đỉnh nào | Quên `memset(vs, 0)` trước mỗi lần đếm lại, hoặc quên đặt `vs[u] = 1` (xóa u) **trước** khi đếm; so với số TPLT **ban đầu** chứ không phải với 1 |
| Cạnh cầu: thiếu/thừa cạnh | Xóa cạnh vô hướng phải xóa cả `a[u][v]` và `a[v][u]`, và **trả lại** sau khi đếm; chỉ xét `u < v` |
| Liên thông mạnh / yếu (TRR2015) | Liên thông yếu phải DFS theo **cả hai chiều** (`a[u][v] || a[v][u]`); mạnh phải DFS từ mọi đỉnh (hoặc Kosaraju) |

## Euler, Hamilton (TRR30xx)
- Kiểm tra Euler quên điều kiện **liên thông** (chỉ đếm bậc lẻ). Có hướng: so `deg+` với `deg−`, không phải tính chẵn/lẻ.
- Tìm chu trình Euler: dùng `top()` (xem), chỉ `pop()` khi đỉnh hết cạnh; vô hướng phải xóa cả `a[t][s]`; quên **lật ngược** CE.
- Bắt đầu sai đỉnh: đề cho sẵn u (t = 2).
- Hamilton: quên kiểm tra cạnh quay về `v0`; quên `vs[y] = 0` khi quay lui; in thiếu dòng tổng số chu trình (TRR3007).

## Cây khung (TRR40xx)
| Triệu chứng | Nguyên nhân hay gặp |
|---|---|
| Không in 0 khi đồ thị không liên thông | Phải kiểm tra `|T| < n − 1` |
| Kruskal: đúng tổng trọng số, sai thứ tự/cạnh | Hai cạnh cùng trọng số: đáp án xét theo (w, u, v) – cạnh có đỉnh nhỏ hơn trước. Hàm so sánh chỉ theo w (kể cả `stable_sort`) giữ thứ tự input nên sai; cần tiêu chí phụ (u, v) |
| Kruskal ra chu trình | Quên khởi tạo `par[i] = i`, hoặc so `u != v` thay vì `Find(u) != Find(v)` |
| Prim sai | Quên `doiINF()` khi ma trận dùng 0 = không có cạnh; dùng `d[u] + a[u][v]` (của Dijkstra) thay vì `a[u][v]` |
| Cây khung DFS/BFS sai cạnh | Ghi cạnh (u, v) khi gặp v **chưa thăm** – không ghi cạnh tới đỉnh đã thăm |

## Đường đi ngắn nhất (TRR50xx)
| Triệu chứng | Nguyên nhân hay gặp |
|---|---|
| Dijkstra cho số âm / quá lớn | Cộng `INF + w` bị tràn khi INF = 1e9 và dùng `int`; hoặc dùng 0 làm "không có cạnh" |
| Nhầm giá trị INF | Đề TRR2 dùng **10000** cho "không có cạnh". Hoặc đặt `INF = 10000` (đủ lớn vì trọng số ≤ 50, n ≤ 100 nên đường đi ngắn nhất ≤ 4950), hoặc đổi 10000 → INF ngay sau khi nhập; trộn hai cách (INF = 1e9 nhưng không đổi 10000) sẽ coi 10000 là cạnh thật |
| Dijkstra chọn lại đỉnh đã cố định | Quên `vs[u] = 1` (cố định nhãn) hoặc không kiểm tra `!vs[v]` khi chọn min |
| Bellman-Ford sai khi có cạnh âm | Thiếu điều kiện `d[u] < INF && a[u][v] < INF` trước khi nới lỏng |
| Bellman-Ford không phát hiện chu trình âm | Không chạy thêm 1 vòng kiểm tra sau n − 2 vòng; đề TRR5007 quy định in −1 |
| Floyd sai | Đặt vòng `k` **không ở ngoài cùng**; truy vết dùng `p[i][j] = k` thay vì `p[k][j]` |
| TRR5016 chọn sai cặp khi bằng nhau | Phải lấy cặp nhỏ nhất theo thứ tự từ điển: duyệt (u, v) tăng dần và chỉ cập nhật khi **lớn hơn hẳn** |
| In thiếu đường đi | Đề yêu cầu in độ dài **và** dãy đỉnh |
