// TRR1004 - Do thi vo huong cho bang danh sach canh
// t = 1: in bac cac dinh; t = 2: in ma tran ke
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
    nhapCanh(false);
    if (t == 1) inBac();
    else inMaTran();
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
0 1 0 1
1 0 1 0
0 1 0 0
1 0 0 0
*/
