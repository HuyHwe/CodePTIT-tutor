// 1.7. Kiem tra lien thong manh (do thi co huong)
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

int dem;
void DFS(int u){
    vs[u] = 1; dem++;
    for (int v = 1; v <= n; v++)
        if (a[u][v] && !vs[v]) DFS(v);
}
bool lienThongManh(){
    for (int u = 1; u <= n; u++){
        memset(vs, 0, sizeof vs); dem = 0;
        DFS(u);
        if (dem < n) return false;
    }
    return true;
}
int main(){ nhapMaTran(); cout << (lienThongManh() ? "YES" : "NO"); }

/*
input:
4
0 1 0 0
0 0 1 0
0 0 0 1
1 0 0 0
expected output:
YES
*/
