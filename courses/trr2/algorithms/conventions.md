# Cách dùng tài liệu và khung code chung

**Cách học một thuật toán:**
1. Đọc lời văn, gấp lại, tự nói lại ý chính trong 3–4 câu.
2. Chép mã giả ra giấy 2 lần cho thuộc khung.
3. Gõ code từ mã giả (không nhìn code mẫu), rồi so lại.

**Quy ước dùng chung cho mọi bài:**
- Đỉnh đánh số 1..n. Đồ thị lưu bằng ma trận a[u][v]. Vòng for (v = 1..n) duyệt đỉnh kề theo thứ tự tăng dần
- vs[u] = 1 nghĩa là đã xét. truoc[v] là đỉnh đứng trước v
- Đồ thị có trọng số: không có cạnh thì a[u][v] = INF. Với ma trận đề cho dùng 0 làm "không có cạnh", gọi doiINF() sau khi nhập.
- Đồ thị có hướng hay vô hướng: code giống hệt nhau, chỉ khác lúc nhập (vô hướng thì gán cả a[v][u]).

**Khung chung (các bước nhập liệu, tùy bài mà dùng cái nào)**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105, INF = 1e9;
int n, m, a[N][N], vs[N], truoc[N];
// Nhap ma tran n x n
void nhapMaTran(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
// Nhap danh sach canh: n m, roi m dong "u v"
void nhapCanh(bool coHuong){
    cin >> n >> m;
    for (int u, v; m--; ){
        cin >> u >> v;
        a[u][v]++; if (!coHuong) a[v][u]++;
    }
}
// Nhap canh co trong so: n m, roi m dong "u v w"
void nhapCanhTS(bool coHuong){
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) a[i][j] = (i == j ? 0 : INF);
    for (int u, v, w; m--; ){
        cin >> u >> v >> w;
        a[u][v] = w; if (!coHuong) a[v][u] = w;
    }
}
// Ma tran trong so dung 0 = khong co canh -> doi thanh INF
void doiINF(){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j && !a[i][j]) a[i][j] = INF;
}
```

**Lưu ý cho bài CodePTIT:** đề TRR2 dùng **10000** làm "không có cạnh" trong ma trận trọng số. Lời giải chuẩn các bài đó đặt `INF = 10000` (đủ lớn vì trọng số ≤ 50, n ≤ 100). Nếu dùng `INF = 1e9` thì phải đổi 10000 → INF ngay sau khi nhập.
