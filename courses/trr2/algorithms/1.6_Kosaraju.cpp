// 1.6. Thuat toan Kosaraju (tim thanh phan lien thong manh)
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

stack<int> st;
void DFS1(int u){
    vs[u] = 1;
    for (int v = 1; v <= n; v++)
        if (a[u][v] && !vs[v]) DFS1(v);
    // u duyet xong -> day vao stack
    st.push(u);
}
// DFS tren do thi dao chieu
void DFS2(int u){
    cout << u << " "; vs[u] = 1;
    for (int v = 1; v <= n; v++)
        // a[v][u]: cung v -> u bi dao thanh u -> v
        if (a[v][u] && !vs[v]) DFS2(v);
}
int main(){
    nhapMaTran();
    for (int u = 1; u <= n; u++) if (!vs[u]) DFS1(u);
    memset(vs, 0, sizeof vs); int d = 0;
    while (!st.empty()){
        int u = st.top(); st.pop();
        if (!vs[u]){ cout << "\nTPLT manh " << ++d << ": "; DFS2(u); }
    }
    cout << "\n" << (d == 1 ? "Lien thong manh" : "Khong lien thong manh");
}

/*
input:
5
0 1 0 0 0
0 0 1 0 0
1 0 0 1 0
0 0 0 0 1
0 0 0 1 0
expected output:
TPLT manh 1: 1 3 2
TPLT manh 2: 4 5
Khong lien thong manh
*/
