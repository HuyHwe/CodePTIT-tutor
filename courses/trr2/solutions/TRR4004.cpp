// TRR4004 - Cay khung nho nhat bang Prim, bat dau tai s
// Khong lien thong thi in 0
#include <bits/stdc++.h>
using namespace std;
// de bai dung 10000 cho "khong co canh" -> dung luon lam INF, khong can doiINF()
const int N = 105, INF = 10000;
int n, a[N][N], vs[N], truoc[N];
// Nhap ma tran n x n (n da doc truoc o main)
void nhapMaTran(){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
// d[v] = canh re nhat noi v voi cay
int d[N];
// muc 4.4
void Prim(int s){
    for (int v = 1; v <= n; v++){ d[v] = a[s][v]; truoc[v] = s; }
    // vs = da thuoc cay
    vs[s] = 1;
    int dT = 0; vector<array<int,3>> T;
    for (int i = 1; i < n; i++){
        int u = 0;
        // u = dinh ngoai cay gan cay nhat
        for (int v = 1; v <= n; v++)
            if (!vs[v] && (!u || d[v] < d[u])) u = v;
        if (d[u] == INF){ cout << 0; return; }
        vs[u] = 1; T.push_back({truoc[u], u, d[u]}); dT += d[u];
        for (int v = 1; v <= n; v++)
            if (!vs[v] && a[u][v] < d[v]){ d[v] = a[u][v]; truoc[v] = u; }
    }
    cout << dT << "\n";
    // de yeu cau in canh voi dinh nho hon truoc
    for (auto e : T) cout << min(e[0], e[1]) << " " << max(e[0], e[1]) << " " << e[2] << "\n";
}
int main(){
    freopen("CK.INP", "r", stdin);
    freopen("CK.OUT", "w", stdout);
    int s; cin >> n >> s;
    nhapMaTran();
    Prim(s);
}

/*
input:
4 1
0 7 8 2
7 0 1 5
8 1 0 1
2 5 1 0
expected output:
4
1 4 2
3 4 1
2 3 1
*/
