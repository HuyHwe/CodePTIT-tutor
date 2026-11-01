// 2.1.2. Kiem tra do thi Euler / nua Euler - Do thi co huong
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N], vs[N];
// Nhap ma tran n x n
void nhapMaTran(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}

// di ca 2 chieu = do thi vo huong tuong ung (lien thong yeu)
void DFS(int u){
    vs[u] = 1;
    for (int v = 1; v <= n; v++)
        if ((a[u][v] || a[v][u]) && !vs[v]) DFS(v);
}
// tra ve: 1 = Euler, 2 = nua Euler, 0 = khong
int ktEulerCH(){
    DFS(1);
    // khong lien thong yeu
    for (int u = 1; u <= n; u++) if (!vs[u]) return 0;
    int ra = 0, vao = 0;
    for (int u = 1; u <= n; u++){
        int d = 0;                          // d = deg+ - deg-
        for (int v = 1; v <= n; v++) d += a[u][v] - a[v][u];
        if (d == 1) ra++;
        else if (d == -1) vao++;
        else if (d != 0) return 0;
    }
    if (ra == 0 && vao == 0) return 1;
    return (ra == 1 && vao == 1) ? 2 : 0;
}
int main(){ nhapMaTran(); cout << ktEulerCH(); }

/*
input:
4
0 1 0 0
0 0 1 0
1 0 0 1
0 0 1 0
expected output:
1
*/
