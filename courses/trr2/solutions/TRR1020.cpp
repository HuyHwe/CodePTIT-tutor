// TRR1020 - Do thi co huong cho bang danh sach ke
// t = 1: in ban bac vao, ban bac ra; t = 2: in ma tran lien thuoc
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
// deg-(u) = tong cot u (cung di vao), deg+(u) = tong hang u (cung di ra)
void inBac(){
    for (int u = 1; u <= n; u++){
        int vao = 0, ra = 0;
        for (int v = 1; v <= n; v++){ vao += a[v][u]; ra += a[u][v]; }
        cout << vao << " " << ra << "\n";
    }
}
// hang = dinh, cot = cung (thu tu tu dien)
// o (u, e) = 1 neu u la dinh dau cua e, -1 neu u la dinh cuoi, 0 neu khong lien quan
void inMTLienThuoc(){
    vector<pair<int,int>> E;
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            if (a[u][v]) E.push_back({u, v});
    cout << n << " " << E.size() << "\n";
    for (int u = 1; u <= n; u++){
        for (auto e : E){
            if (e.first == u) cout << 1 << " ";
            else if (e.second == u) cout << -1 << " ";
            else cout << 0 << " ";
        }
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
Test 1
input:
1
4
2 2 4
2 3 4
2 1 2
1 3
expected output:
1 2
2 2
2 2
2 1

Test 2
input:
2
4
2 2 4
2 3 4
2 1 2
1 3
expected output:
4 7
1 1 0 0 -1 0 0
-1 0 1 1 0 -1 0
0 0 -1 0 1 1 -1
0 -1 0 -1 0 0 1
*/
