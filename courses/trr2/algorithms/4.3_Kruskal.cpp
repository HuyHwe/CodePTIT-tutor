// 4.3. Kruskal (cay khung nho nhat, theo canh)
// Nhap ma tran trong so, 0 = khong co canh
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

int par[N];
int Find(int x){ return par[x] == x ? x : par[x] = Find(par[x]); }
void Kruskal(){
    // {w, u, v}
    vector<array<int,3>> E;
    for (int u = 1; u <= n; u++)
        for (int v = u + 1; v <= n; v++)
            if (a[u][v]) E.push_back({a[u][v], u, v});
    sort(E.begin(), E.end());
    for (int i = 1; i <= n; i++) par[i] = i;
    vector<array<int,3>> T; int dT = 0;
    for (auto e : E){
        if ((int)T.size() == n - 1) break;
        int x = Find(e[1]), y = Find(e[2]);
        // khong tao chu trinh
        if (x != y){ par[x] = y; T.push_back(e); dT += e[0]; }
    }
    if ((int)T.size() < n - 1){ cout << "Do thi khong lien thong"; return; }
    cout << "dH = " << dT << "\n";
    for (auto e : T) cout << e[1] << " " << e[2] << " " << e[0] << "\n";
}
int main(){ nhapMaTran(); Kruskal(); }

/*
input:
5
0 2 6 0 0
2 0 3 8 0
6 3 0 0 5
0 8 0 0 4
0 0 5 4 0
expected output:
dH = 14
1 2 2
2 3 3
4 5 4
3 5 5
*/
