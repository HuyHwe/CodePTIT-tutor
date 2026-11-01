// 3.3. Floyd
#include <bits/stdc++.h>
using namespace std;
const int N = 105, INF = 1e9;
int n, m, a[N][N];
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

// p[i][j] = dinh dung truoc j tren duong i -> j
int d[N][N], p[N][N];
void Floyd(){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++){ d[i][j] = a[i][j]; p[i][j] = (a[i][j] < INF ? i : 0); }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][k] < INF && d[k][j] < INF && d[i][k] + d[k][j] < d[i][j]){
                    d[i][j] = d[i][k] + d[k][j]; p[i][j] = p[k][j];
                }
}
void inDuong(int u, int v){
    if (d[u][v] == INF){ cout << "Khong co duong di\n"; return; }
    vector<int> path;
    for (int x = v; x != u; x = p[u][x]) path.push_back(x);
    path.push_back(u); reverse(path.begin(), path.end());
    cout << "d = " << d[u][v] << ": ";
    for (int x : path) cout << x << " ";
    cout << "\n";
}
int main(){
    nhapCanhTS(true); Floyd();
    for (int i = 1; i <= n; i++) if (d[i][i] < 0){ cout << "Co chu trinh am"; return 0; }
    for (int u = 1; u <= n; u++) for (int v = 1; v <= n; v++) if (u != v) inDuong(u, v);
}

/*
input:
3 4
1 2 3
2 3 1
1 3 6
3 1 2
expected output:
d = 3: 1 2
d = 4: 1 2 3
d = 3: 2 3 1
d = 1: 2 3
d = 2: 3 1
d = 5: 3 1 2
*/
