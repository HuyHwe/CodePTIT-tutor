// 3.1. Dijkstra
#include <bits/stdc++.h>
using namespace std;
const int N = 105, INF = 1e9;
int n, m, a[N][N], vs[N], truoc[N];
// Nhap canh co trong so: n m, roi m dong "u v w"
void nhapCanhTS(bool coHuong){
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) a[i][j] = (i == j ? 0 : INF);
    for (int u, v, w; m--; ){
        cin >> u >> v >> w;
        a[u][v] = w; if (!coHuong) a[v][u] = w;
    }
}

int d[N];
void Dijkstra(int s){
    for (int v = 1; v <= n; v++){ d[v] = a[s][v]; truoc[v] = s; }
    // vs = da co nhan co dinh
    d[s] = 0; vs[s] = 1;
    for (int i = 1; i < n; i++){
        int u = 0;
        // u = dinh tam thoi co d nho nhat
        for (int v = 1; v <= n; v++)
            if (!vs[v] && (!u || d[v] < d[u])) u = v;
        // cac dinh con lai khong toi duoc
        if (d[u] == INF) break;
        // co dinh nhan u
        vs[u] = 1;
        for (int v = 1; v <= n; v++)
            if (!vs[v] && d[u] + a[u][v] < d[v]){ d[v] = d[u] + a[u][v]; truoc[v] = u; }
    }
}
void inDuong(int s, int t){
    if (d[t] == INF){ cout << "Khong co duong di\n"; return; }
    vector<int> p;
    for (int v = t; v != s; v = truoc[v]) p.push_back(v);
    p.push_back(s); reverse(p.begin(), p.end());
    cout << "d = " << d[t] << ": ";
    for (int x : p) cout << x << " ";
    cout << "\n";
}
int main(){
    nhapCanhTS(true); int s = 1;
    Dijkstra(s);
    for (int t = 1; t <= n; t++) inDuong(s, t);
}

/*
input:
5 7
1 2 4
1 3 1
3 2 2
2 4 1
3 4 5
4 5 3
3 5 8
expected output:
d = 0: 1
d = 3: 1 3 2
d = 1: 1 3
d = 4: 1 3 2 4
d = 7: 1 3 2 4 5
*/
