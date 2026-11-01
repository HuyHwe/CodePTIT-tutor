// TRR2009 - Tim cac thanh phan lien thong cua do thi vo huong bang DFS
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
// vs[u] = so thu tu TPLT chua u (0 = chua xet)
int n, a[N][N], vs[N], soTPLT;
// Nhap ma tran n x n
void nhapMaTran(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
// cac dinh tham duoc deu thuoc TPLT thu soTPLT
void DFS(int u){
    vs[u] = soTPLT;
    for (int v = 1; v <= n; v++)
        if (a[u][v] && !vs[v]) DFS(v);
}
int main(){
    freopen("TK.INP", "r", stdin);
    freopen("TK.OUT", "w", stdout);
    nhapMaTran();
    // dem TPLT (muc 1.4)
    for (int u = 1; u <= n; u++)
        if (!vs[u]){ soTPLT++; DFS(u); }
    cout << soTPLT << "\n";
    // in TPLT thu i: cac dinh co vs = i, duyet u tang dan
    for (int i = 1; i <= soTPLT; i++){
        for (int u = 1; u <= n; u++) if (vs[u] == i) cout << u << " ";
        cout << "\n";
    }
}

/*
input:
5
0 1 1 0 0
1 0 1 0 0
1 1 0 0 0
0 0 0 0 1
0 0 0 1 0
expected output:
2
1 2 3
4 5
*/
