// TRR1021 - Do thi co huong co trong so cho bang ma tran trong so
// t = 1: in ban bac vao, ban bac ra; t = 2: in danh sach canh kem trong so
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
// co cung u -> v khi trong so khac 0 va khac INF
bool coCanh(int u, int v){ return a[u][v] != 0 && a[u][v] != INF; }
// deg-(u) = so cung di vao u, deg+(u) = so cung di ra tu u
void inBac(){
    for (int u = 1; u <= n; u++){
        int vao = 0, ra = 0;
        for (int v = 1; v <= n; v++){
            if (coCanh(v, u)) vao++;
            if (coCanh(u, v)) ra++;
        }
        cout << vao << " " << ra << "\n";
    }
}
// cung (u,v,w); duyet u, v tang dan nen dung thu tu tu dien
void inDSCanh(){
    vector<array<int,3>> E;
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
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
10000 0 3 4
5 6 0 10000
10000 10000 7 0
expected output:
1 2
2 2
2 2
2 1

Test 2
input:
2
4
0 1 10000 2
10000 0 3 4
5 6 0 10000
10000 10000 7 0
expected output:
4 7
1 2 1
1 4 2
2 3 3
2 4 4
3 1 5
3 2 6
4 3 7
*/
