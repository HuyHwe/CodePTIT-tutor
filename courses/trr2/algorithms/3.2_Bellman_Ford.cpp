// 3.2. Bellman-Ford
#include <bits/stdc++.h>
using namespace std;
const int N = 105, INF = 1e9;
int n, m, a[N][N], truoc[N];
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
bool BellmanFord(int s){
    for (int v = 1; v <= n; v++){ d[v] = a[s][v]; truoc[v] = s; }
    d[s] = 0;
    for (int k = 1; k <= n - 2; k++)
        for (int v = 1; v <= n; v++) if (v != s)
            for (int u = 1; u <= n; u++)
                if (d[u] < INF && a[u][v] < INF && d[u] + a[u][v] < d[v]){
                    d[v] = d[u] + a[u][v]; truoc[v] = u;
                }
    // con giam duoc => co chu trinh am
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            if (d[u] < INF && a[u][v] < INF && d[u] + a[u][v] < d[v]) return false;
    return true;
}
int main(){
    nhapCanhTS(true); int s = 1;
    if (!BellmanFord(s)){ cout << "Co chu trinh am"; return 0; }
    for (int v = 1; v <= n; v++) cout << v << ": " << d[v] << " (truoc " << truoc[v] << ")\n";
}

/*
input:
4 5
1 2 4
1 3 2
3 2 -3
2 4 2
3 4 4
expected output:
1: 0 (truoc 1)
2: -1 (truoc 3)
3: 2 (truoc 1)
4: 1 (truoc 2)
*/
