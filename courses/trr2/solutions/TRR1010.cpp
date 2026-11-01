// TRR1010 - Do thi vo huong co trong so cho bang ma tran trong so
// t = 1: in bac cac dinh; t = 2: in danh sach canh kem trong so
#include <bits/stdc++.h>
using namespace std;
// de bai dung 10000 cho "khong co canh"
const int N = 105, INF = 10000;
int n, a[N][N];
// Nhap ma tran n x n
void nhapMaTran(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
// co canh u-v khi trong so khac 0 va khac INF
bool coCanh(int u, int v){ return a[u][v] != 0 && a[u][v] != INF; }
// bac cua u = so dinh v co canh voi u
void inBac(){
    for (int u = 1; u <= n; u++){
        int deg = 0;
        for (int v = 1; v <= n; v++) if (coCanh(u, v)) deg++;
        cout << deg << " ";
    }
}
// canh (u,v,w) lay u < v; duyet u, v tang dan nen dung thu tu tu dien
void inDSCanh(){
    vector<array<int,3>> E;
    for (int u = 1; u <= n; u++)
        for (int v = u + 1; v <= n; v++)
            if (coCanh(u, v)) E.push_back({u, v, a[u][v]});
    cout << n << " " << E.size() << "\n";
    for (auto e : E) cout << e[0] << " " << e[1] << " " << e[2] << "\n";
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
0 1 10000 2
1 0 3 10000
10000 3 0 0
2 10000 10000 0
expected output:
2 2 1 1

Test 2
input:
2
4
0 1 10000 2
1 0 3 10000
10000 3 0 0
2 10000 10000 0
expected output:
4 3
1 2 1
1 4 2
2 3 3
*/
