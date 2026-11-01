// TRR2015 - Xac dinh tinh lien thong cua do thi co huong bang DFS
// In 1 = lien thong manh, 2 = chi lien thong yeu, 0 = khong lien thong
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N], vs[N], dem;
// Nhap ma tran n x n
void nhapMaTran(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
// DFS theo chieu cung, dem so dinh tham duoc (muc 1.7)
void DFS(int u){
    vs[u] = 1; dem++;
    for (int v = 1; v <= n; v++)
        if (a[u][v] && !vs[v]) DFS(v);
}
// DFS di ca 2 chieu = do thi vo huong tuong ung (muc 2.1.2)
void DFSVoHuong(int u){
    vs[u] = 1; dem++;
    for (int v = 1; v <= n; v++)
        if ((a[u][v] || a[v][u]) && !vs[v]) DFSVoHuong(v);
}
// lien thong manh: DFS tu moi dinh deu tham du n dinh
bool lienThongManh(){
    for (int u = 1; u <= n; u++){
        memset(vs, 0, sizeof vs); dem = 0;
        DFS(u);
        if (dem < n) return false;
    }
    return true;
}
// lien thong yeu: do thi vo huong tuong ung lien thong
bool lienThongYeu(){
    memset(vs, 0, sizeof vs); dem = 0;
    DFSVoHuong(1);
    return dem == n;
}
int main(){
    freopen("TK.INP", "r", stdin);
    freopen("TK.OUT", "w", stdout);
    nhapMaTran();
    if (lienThongManh()) cout << 1;
    else if (lienThongYeu()) cout << 2;
    else cout << 0;
}

/*
Test 1
input:
4
0 0 1 0
0 0 0 1
0 1 0 0
1 0 0 0
expected output:
1

Test 2
input:
4
0 0 1 0
0 0 0 1
0 1 0 0
0 0 1 0
expected output:
2
*/
