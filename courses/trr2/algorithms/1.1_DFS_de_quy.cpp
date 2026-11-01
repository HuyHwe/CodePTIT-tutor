// 1.1. DFS de quy
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
        if (a[u][v] == 1 && !vs[v]) DFS(v);
}
// in cac dinh tham duoc tu 1
int main(){
    nhapMaTran(); DFS(1);
    for (int u = 1; u <= n; u++) if (vs[u]) cout << u << " ";
}

/*
input:
6
0 1 1 0 0 0
1 0 0 1 0 0
1 0 0 0 0 0
0 1 0 0 0 0
0 0 0 0 0 1
0 0 0 0 1 0
expected output:
1 2 3 4
*/
