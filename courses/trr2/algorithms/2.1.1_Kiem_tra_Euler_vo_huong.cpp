// 2.1. Kiem tra do thi Euler / nua Euler - Do thi vo huong
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

void DFS(int u){
    vs[u] = 1;
    for (int v = 1; v <= n; v++)
        if (a[u][v] && !vs[v]) DFS(v);
}
// tra ve: 1 = Euler, 2 = nua Euler, 0 = khong
int ktEulerVH(){
    DFS(1);
    // khong lien thong
    for (int u = 1; u <= n; u++) if (!vs[u]) return 0;
    int le = 0;
    for (int u = 1; u <= n; u++){
        int deg = 0;
        for (int v = 1; v <= n; v++) deg += a[u][v];
        if (deg % 2) le++;
    }
    if (le == 0) return 1;
    return le == 2 ? 2 : 0;
}
int main(){ nhapMaTran(); cout << ktEulerVH(); }

/*
input:
4
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
expected output:
2
*/
