// TRR1009 - Do thi vo huong cho bang danh sach ke
// t = 1: in bac cac dinh; t = 2: in ma tran lien thuoc
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N];
// Nhap danh sach ke: n, roi n dong "k v1 v2 ... vk"
void nhapDSKe(){
    cin >> n;
    for (int u = 1; u <= n; u++){
        int k; cin >> k;
        for (int v; k--; ){ cin >> v; a[u][v] = 1; }
    }
}
// bac cua u = tong hang u
void inBac(){
    for (int u = 1; u <= n; u++){
        int deg = 0;
        for (int v = 1; v <= n; v++) deg += a[u][v];
        cout << deg << " ";
    }
}
// hang = dinh, cot = canh (thu tu tu dien); o (u, e) = 1 neu u la mot dau cua canh e
void inMTLienThuoc(){
    vector<pair<int,int>> E;
    for (int u = 1; u <= n; u++)
        for (int v = u + 1; v <= n; v++)
            if (a[u][v]) E.push_back({u, v});
    cout << n << " " << E.size() << "\n";
    for (int u = 1; u <= n; u++){
        for (auto e : E) cout << (e.first == u || e.second == u) << " ";
        cout << "\n";
    }
}
int main(){
    freopen("DT.INP", "r", stdin);
    freopen("DT.OUT", "w", stdout);
    int t; cin >> t;
    nhapDSKe();
    if (t == 1) inBac();
    else inMTLienThuoc();
}

/*
Test 1 (test goc trong de ghi input dang danh sach canh, sai voi de bai -> doi sang danh sach ke)
input:
1
4
2 2 4
2 1 3
1 2
1 1
expected output:
2 2 1 1

Test 2
input:
2
4
2 2 4
2 1 3
1 2
1 1
expected output:
4 3
1 1 0
1 0 1
0 0 1
0 1 0
*/
