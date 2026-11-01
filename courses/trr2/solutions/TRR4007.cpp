// TRR4007 - Cay khung nho nhat bang Kruskal, do thi cho bang danh sach canh co trong so
// Khong lien thong thi in 0
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, m;
// par[x] = cha cua x trong cay DSU
int par[N];
int Find(int x){ return par[x] == x ? x : par[x] = Find(par[x]); }
int main(){
    freopen("CK.INP", "r", stdin);
    freopen("CK.OUT", "w", stdout);
    cin >> n >> m;
    // {w, u, v}: dat w len dau de sort theo trong so
    vector<array<int,3>> E(m);
    for (auto &e : E) cin >> e[1] >> e[2] >> e[0];
    // muc 4.3
    sort(E.begin(), E.end());
    for (int i = 1; i <= n; i++) par[i] = i;
    vector<array<int,3>> T; int dT = 0;
    for (auto e : E){
        if ((int)T.size() == n - 1) break;
        int x = Find(e[1]), y = Find(e[2]);
        // khong tao chu trinh
        if (x != y){ par[x] = y; T.push_back(e); dT += e[0]; }
    }
    if ((int)T.size() < n - 1){ cout << 0; return 0; }
    cout << dT << "\n";
    for (auto e : T) cout << e[1] << " " << e[2] << " " << e[0] << "\n";
}

/*
input:
4 6
1 2 7
1 3 8
1 4 2
2 3 1
2 4 2
3 4 1
expected output:
4
2 3 1
3 4 1
1 4 2
*/
