// TRR1013 - Do thi co huong cho bang ma tran ke
// t = 1: in ban bac vao, ban bac ra; t = 2: in danh sach ke
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N];
// Nhap ma tran n x n
void nhapMaTran(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
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
    nhapMaTran();
    if (t == 1) inBac();
    else inDSKe();
}

/*
Test 1
input:
1
4
0 1 0 1
0 0 1 1
1 1 0 0
0 0 1 0
expected output:
1 2
2 2
2 2
2 1

Test 2
input:
2
4
0 1 0 1
0 0 1 1
1 1 0 0
0 0 1 0
expected output:
4
2 2 4
2 3 4
2 1 2
1 3
*/
