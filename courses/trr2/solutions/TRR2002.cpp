// TRR2002 - Cho ma tran ke va hai dinh u, v
// t = 1: dem so duong di do dai 2 tu u den v; t = 2: tim duong di u -> v bang BFS
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N], vs[N], truoc[N];
// Nhap ma tran n x n (n da doc truoc o main)
void nhapMaTran(){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
// duong di do dai 2: u -> k -> v
int demDuongDi2(int u, int v){
    int d = 0;
    for (int k = 1; k <= n; k++)
        if (a[u][k] && a[k][v]) d++;
    return d;
}
// BFS ghi truoc[] (muc 1.5)
void BFS(int s){
    queue<int> q; q.push(s); vs[s] = 1;
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (int v = 1; v <= n; v++)
            if (a[u][v] && !vs[v]){ q.push(v); vs[v] = 1; truoc[v] = u; }
    }
}
// lan nguoc tu t ve s theo truoc[] roi dao nguoc
void inDuong(int s, int t){
    if (!vs[t]){ cout << 0; return; }
    vector<int> p;
    for (int v = t; v != s; v = truoc[v]) p.push_back(v);
    p.push_back(s);
    reverse(p.begin(), p.end());
    for (int x : p) cout << x << " ";
}
int main(){
    freopen("TK.INP", "r", stdin);
    freopen("TK.OUT", "w", stdout);
    int t, u, v; cin >> t >> n >> u >> v;
    nhapMaTran();
    if (t == 1) cout << demDuongDi2(u, v);
    else { BFS(u); inDuong(u, v); }
}

/*
Test 1
input:
1
4 2 4
0 1 0 1
1 0 1 0
0 1 0 1
1 0 1 0
expected output:
2

Test 2
input:
2
4 1 4
0 0 1 0
0 0 0 1
0 1 0 1
1 0 0 0
expected output:
1 3 4
*/
