// 5.1. Ford-Fulkerson (tim duong tang luong bang BFS)
// Nhap: n m s t, roi m dong u v c
#include <bits/stdc++.h>
using namespace std;
const int N = 105, INF = 1e9;
int n, m, a[N][N], vs[N], truoc[N];

// c = kha nang thong qua ban dau, a = do thi tang luong
int c[N][N];
// tim duong tang luong s -> t tren a
bool BFS(int s, int t){
    memset(vs, 0, sizeof vs);
    queue<int> q; q.push(s); vs[s] = 1;
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (int v = 1; v <= n; v++)
            if (a[u][v] > 0 && !vs[v]){ vs[v] = 1; truoc[v] = u; q.push(v); }
    }
    return vs[t];
}
int FordFulkerson(int s, int t){
    int val = 0;
    while (BFS(s, t)){
        int delta = INF;
        for (int v = t; v != s; v = truoc[v]) delta = min(delta, a[truoc[v]][v]);
        for (int v = t; v != s; v = truoc[v]){
            // cung thuan giam
            a[truoc[v]][v] -= delta;
            // cung nghich tang
            a[v][truoc[v]] += delta;
        }
        val += delta;
    }
    return val;
}
int main(){
    int s, t; cin >> n >> m >> s >> t;
    for (int u, v, w; m--; ){ cin >> u >> v >> w; c[u][v] = a[u][v] = w; }
    cout << "val(f) = " << FordFulkerson(s, t) << "\n";
    // luong tren tung cung
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            if (c[u][v]) cout << u << "->" << v << ": " << max(0, c[u][v] - a[u][v]) << "/" << c[u][v] << "\n";
    // lat cat hep nhat: X = cac dinh BFS cuoi cung tham duoc
    cout << "X = { ";
    for (int u = 1; u <= n; u++) if (vs[u]) cout << u << " ";
    cout << "}";
}

/*
input:
4 5 1 4
1 2 3
1 3 2
2 3 1
2 4 2
3 4 3
expected output:
val(f) = 5
1->2: 3/3
1->3: 2/2
2->3: 1/1
2->4: 2/2
3->4: 3/3
X = { 1 }
*/
