// 1.10. Kiem tra do thi dinh chieu duoc
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

int demTPLT(){
    memset(vs, 0, sizeof vs); int d = 0;
    for (int u = 1; u <= n; u++)
        if (!vs[u]){ d++; DFS(u); }
    return d;
}
int main(){
    nhapMaTran();
    int goc = demTPLT();
    if (goc > 1) {
        cout << "Khong dinh chieu duoc";
        return 0;
    }

    for (int u = 1; u <= n; u++)
        for (int v = u + 1; v <= n; v++) if (a[u][v]){
            a[u][v] = a[v][u] = 0;  // xoa canh
            if (demTPLT() > goc) {
                cout << "Khong dinh chieu duoc";
                return 0;
            }
            a[u][v] = a[v][u] = 1;  // tra lai
        }
    cout << "Dinh chieu duoc";
    return 0;
}

/*
input:
4
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
expected output:
Dinh chieu duoc
*/
