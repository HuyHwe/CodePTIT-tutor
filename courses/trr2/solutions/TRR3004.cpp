// TRR3004 - Do thi co huong cho bang ma tran ke
// t = 1: kiem tra Euler (1) / nua Euler (2) / khong (0); t = 2: in chu trinh Euler bat dau tu u
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N], vs[N];
// Nhap ma tran n x n (n da doc truoc o main)
void nhapMaTran(){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
// di ca 2 chieu = do thi vo huong tuong ung (lien thong yeu)
void DFS(int u){
    vs[u] = 1;
    for (int v = 1; v <= n; v++)
        if ((a[u][v] || a[v][u]) && !vs[v]) DFS(v);
}
// muc 2.1.2: tra ve 1 = Euler, 2 = nua Euler, 0 = khong
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
// muc 2.2: tim chu trinh Euler bang ngan xep
void Euler(int u){
    stack<int> st; vector<int> CE; st.push(u);
    while (!st.empty()){
        int s = st.top(), t = 1;
        // t = dinh ke dau tien cua s
        while (t <= n && !a[s][t]) t++;
        if (t <= n){
            st.push(t);
            // co huong: chi xoa cung s -> t
            a[s][t]--;
        } else { st.pop(); CE.push_back(s); }
    }
    reverse(CE.begin(), CE.end());
    for (int x : CE) cout << x << " ";
}
int main(){
    freopen("CT.INP", "r", stdin);
    freopen("CT.OUT", "w", stdout);
    int t, u; cin >> t >> n;
    if (t == 2) cin >> u;
    nhapMaTran();
    if (t == 1) cout << ktEulerCH();
    else Euler(u);
}

/*
Test 1
input:
1
4
0 1 0 1
0 0 0 1
1 0 0 0
0 0 1 0
expected output:
2

Test 2
input:
2
4 3
0 1 0 0
0 0 1 0
0 0 0 1
1 0 0 0
expected output:
3 4 1 2 3
*/
