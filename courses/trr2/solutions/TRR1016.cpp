// TRR1016 - Do thi co huong cho bang danh sach canh
// t = 1: in ban bac vao, ban bac ra; t = 2: in danh sach ke
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, m, a[N][N];
// Nhap danh sach canh: n m, roi m dong "u v"
void nhapCanh(bool coHuong){
    cin >> n >> m;
    for (int u, v; m--; ){
        cin >> u >> v;
        a[u][v]++; if (!coHuong) a[v][u]++;
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
// moi dong: k = so dinh ke (cung di ra) cua u, roi k dinh ke tang dan
void inDSKe(){
    cout << n << "\n";
    for (int u = 1; u <= n; u++){
        int k = 0;
        for (int v = 1; v <= n; v++) k += a[u][v];
        cout << k;
        for (int v = 1; v <= n; v++) if (a[u][v]) cout << " " << v;
        cout << "\n";
    }
}
int main(){
    freopen("DT.INP", "r", stdin);
    freopen("DT.OUT", "w", stdout);
    int t; cin >> t;
    nhapCanh(true);
    if (t == 1) inBac();
    else inDSKe();
}

/*
Test 1
input:
1
4 7
1 2
1 4
2 3
2 4
3 1
3 2
4 3
expected output:
1 2
2 2
2 2
2 1

Test 2
input:
2
4 7
1 2
1 4
2 3
2 4
3 1
3 2
4 3
expected output:
4
2 2 4
2 3 4
2 1 2
1 3
*/
