// TRR5016 - Dung Floyd tim cap (u, v) co duong di ngan nhat dai nhat
// Nhieu cap bang nhau thi lay cap nho nhat theo tu dien; khong co cap nao thi in 0
#include <bits/stdc++.h>
using namespace std;
// de bai dung 10000 cho "khong co canh" -> dung luon lam INF
const int N = 105, INF = 10000;
int n, a[N][N];
// Nhap ma tran n x n
void nhapMaTran(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
// p[i][j] = dinh dung truoc j tren duong i -> j
int d[N][N], p[N][N];
// muc 3.3
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
int main(){
    freopen("DN.INP", "r", stdin);
    freopen("DN.OUT", "w", stdout);
    nhapMaTran(); Floyd();
    // tim cap (u, v) co d lon nhat; duyet u, v tang dan va so sanh ">" nen giu cap nho nhat
    int bu = 0, bv = 0;
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            if (u != v && d[u][v] < INF && (!bu || d[u][v] > d[bu][bv])){ bu = u; bv = v; }
    if (!bu){ cout << 0; return 0; }
    cout << bu << " " << bv << " " << d[bu][bv] << "\n";
    // lan nguoc tu bv ve bu theo p[][] roi dao nguoc
    vector<int> path;
    for (int x = bv; x != bu; x = p[bu][x]) path.push_back(x);
    path.push_back(bu); reverse(path.begin(), path.end());
    for (int x : path) cout << x << " ";
}

/*
input:
4
0 7 8 2
10000 0 10000 10000
10000 1 0 10000
10000 5 1 0
expected output:
1 2 4
1 4 3 2
*/
