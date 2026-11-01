// TRR1005 - Do thi vo huong cho bang danh sach canh
// t = 1: in bac cac dinh; t = 2: in danh sach ke
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
// bac cua u = tong hang u
void inBac(){
    for (int u = 1; u <= n; u++){
        int deg = 0;
        for (int v = 1; v <= n; v++) deg += a[u][v];
        cout << deg << " ";
    }
}
// moi dong: k = so dinh ke cua u, roi k dinh ke tang dan
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
    nhapCanh(false);
    if (t == 1) inBac();
    else inDSKe();
}

/*
Test 1
input:
1
4 3
1 2
1 4
2 3
expected output:
2 2 1 1

Test 2
input:
2
4 3
1 2
1 4
2 3
expected output:
4
2 2 4
2 1 3
1 2
1 1
*/
