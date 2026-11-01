// TRR2030 - Tim cac canh cau cua do thi vo huong bang BFS
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N], vs[N];
// Nhap ma tran n x n
void nhapMaTran(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
void BFS(int u){
    queue<int> q; q.push(u); vs[u] = 1;
    while (!q.empty()){
        int s = q.front(); q.pop();
        for (int t = 1; t <= n; t++)
            if (a[s][t] && !vs[t]){ q.push(t); vs[t] = 1; }
    }
}
// demTPLT phai tu xoa vs o dau (muc 1.9)
int demTPLT(){
    memset(vs, 0, sizeof vs); int d = 0;
    for (int u = 1; u <= n; u++)
        if (!vs[u]){ d++; BFS(u); }
    return d;
}
int main(){
    freopen("TK.INP", "r", stdin);
    freopen("TK.OUT", "w", stdout);
    nhapMaTran();
    int goc = demTPLT();
    vector<pair<int,int>> cau;
    // duyet u < v tang dan nen cac cau tu dong theo thu tu tu dien
    for (int u = 1; u <= n; u++)
        for (int v = u + 1; v <= n; v++) if (a[u][v]){
            a[u][v] = a[v][u] = 0;  // xoa canh
            if (demTPLT() > goc) cau.push_back({u, v});
            a[u][v] = a[v][u] = 1;  // tra lai
        }
    cout << cau.size() << "\n";
    for (auto e : cau) cout << e.first << " " << e.second << "\n";
}

/*
input:
5
0 1 0 0 0
1 0 1 0 0
0 1 0 1 1
0 0 1 0 1
0 0 1 1 0
expected output:
2
1 2
2 3
*/
