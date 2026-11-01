// TRR1001 - Do thi vo huong cho bang ma tran ke
// t = 1: in bac cac dinh; t = 2: in danh sach canh
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
// canh (u,v) lay u < v; duyet u, v tang dan nen dung thu tu tu dien
void inDSCanh(){
    vector<pair<int,int>> E;
    for (int u = 1; u <= n; u++)
        for (int v = u + 1; v <= n; v++)
            if (a[u][v]) E.push_back({u, v});
    cout << n << " " << E.size() << "\n";
    for (auto e : E) cout << e.first << " " << e.second << "\n";
}
int main(){
    freopen("DT.INP", "r", stdin);
    freopen("DT.OUT", "w", stdout);
    int t; cin >> t;
    nhapMaTran();
    if (t == 1) inBac();
    else inDSCanh();
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
4 3
1 2
1 4
2 3
*/
