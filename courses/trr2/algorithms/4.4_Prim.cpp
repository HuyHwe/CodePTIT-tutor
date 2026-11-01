// 4.4. Prim (cay khung nho nhat, theo dinh)
#include <bits/stdc++.h>
using namespace std;
const int N = 105, INF = 1e9;
int n, a[N][N], vs[N], truoc[N];
// Nhap ma tran n x n
void nhapMaTran(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
// Ma tran trong so dung 0 = khong co canh -> doi thanh INF
void doiINF(){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j && !a[i][j]) a[i][j] = INF;
}

int d[N];
void Prim(int s){
    for (int v = 1; v <= n; v++){ d[v] = a[s][v]; truoc[v] = s; }
    // vs = da thuoc VT
    vs[s] = 1;
    int dT = 0; vector<array<int,3>> T;
    for (int i = 1; i < n; i++){
        int u = 0;
        // u = dinh ngoai VT gan cay nhat
        for (int v = 1; v <= n; v++)
            if (!vs[v] && (!u || d[v] < d[u])) u = v;
        if (d[u] == INF){ cout << "Do thi khong lien thong"; return; }
        vs[u] = 1; T.push_back({truoc[u], u, d[u]}); dT += d[u];
        for (int v = 1; v <= n; v++)
            if (!vs[v] && a[u][v] < d[v]){ d[v] = a[u][v]; truoc[v] = u; }
    }
    cout << "dH = " << dT << "\n";
    for (auto e : T) cout << e[0] << " " << e[1] << " " << e[2] << "\n";
}
int main(){ nhapMaTran(); doiINF(); Prim(1); }

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
3 5 5
5 4 4
*/
