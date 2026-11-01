// 1.5. Tim duong di tu s den t
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N], vs[N], truoc[N];
// Nhap ma tran n x n
void nhapMaTran(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}

void DFS(int u){
    vs[u] = 1;
    for (int v = 1; v <= n; v++)
        if (a[u][v] && !vs[v]){ truoc[v] = u; DFS(v); }
}
void BFS(int s){
    queue<int> q; q.push(s); vs[s] = 1;
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (int v = 1; v <= n; v++)
            if (a[u][v] && !vs[v]){ q.push(v); vs[v] = 1; truoc[v] = u; }
    }
}
void inDuong(int s, int t){
    if (!vs[t]){ cout << "Khong co duong di"; return; }
    vector<int> p;
    for (int v = t; v != s; v = truoc[v]) p.push_back(v);
    p.push_back(s);
    reverse(p.begin(), p.end());
    for (int x : p) cout << x << " ";
}
int main(){ nhapMaTran(); int s, t; cin >> s >> t; BFS(s); inDuong(s, t); }

/*
input:
6
0 1 0 1 0 0
1 0 1 0 0 0
0 1 0 0 0 1
1 0 0 0 1 0
0 0 0 1 0 1
0 0 1 0 1 0
1 6
expected output:
1 2 3 6
*/
