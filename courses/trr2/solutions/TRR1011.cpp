// TRR1011 - Do thi vo huong co trong so cho bang danh sach canh kem trong so
// t = 1: in bac cac dinh; t = 2: in ma tran trong so
#include <bits/stdc++.h>
using namespace std;
// de bai dung 10000 cho "khong co canh"
const int N = 105, INF = 10000;
int n, m, a[N][N];
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
// bac cua u = so dinh v != u co a[u][v] < INF
void inBac(){
    for (int u = 1; u <= n; u++){
        int deg = 0;
        for (int v = 1; v <= n; v++) if (v != u && a[u][v] < INF) deg++;
        cout << deg << " ";
    }
}
void inMaTran(){
    cout << n << "\n";
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++) cout << a[i][j] << " ";
        cout << "\n";
    }
}
int main(){
    freopen("DT.INP", "r", stdin);
    freopen("DT.OUT", "w", stdout);
    int t; cin >> t;
    nhapCanhTS(false);
    if (t == 1) inBac();
    else inMaTran();
}

/*
Test 1
input:
1
4 3
1 2 1
1 4 2
2 3 3
expected output:
2 2 1 1

Test 2 (de goc ghi o (3,4) = 0, nhung khong co canh 3-4 nen dung phai la 10000 nhu o (4,3))
input:
2
4 3
1 2 1
1 4 2
2 3 3
expected output:
4
0 1 10000 2
1 0 3 10000
10000 3 0 10000
2 10000 10000 0
*/
