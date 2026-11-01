// 1.8. Tim dinh tru
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

// DFS (muc 1.1)
void DFS(int u){
    vs[u] = 1;
    for (int v = 1; v <= n; v++)
        if (a[u][v] == 1 && !vs[v]) DFS(v);
}
// demTPLT (muc 1.4)
int demTPLT(){
    int d = 0;
    for (int u = 1; u <= n; u++)
        if (!vs[u]){ d++; DFS(u); }
    return d;
}

int main(){
    nhapMaTran();
    int goc = demTPLT();
    for (int u = 1; u <= n; u++){
        memset(vs, 0, sizeof vs);
        // cam di qua u = xoa u
        vs[u] = 1;
        if (demTPLT() > goc) cout << u << " ";
    }
}

/*
input:
5
0 1 1 0 0
1 0 1 0 0
1 1 0 1 0
0 0 1 0 1
0 0 0 1 0
expected output:
3 4
*/
