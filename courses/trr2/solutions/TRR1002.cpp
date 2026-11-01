// TRR1002 - Do thi vo huong cho bang ma tran ke
// t = 1: in bac cac dinh; t = 2: in danh sach ke
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
1 0 1 0
0 1 0 0
1 0 0 0
expected output:
2 2 1 1

Test 2
input:
2
4
0 1 0 1
1 0 1 0
0 1 0 0
1 0 0 0
expected output:
4
2 2 4
2 1 3
1 2
1 1
*/
