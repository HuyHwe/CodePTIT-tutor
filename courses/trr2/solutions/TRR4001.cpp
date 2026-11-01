// TRR4001 - Cay khung cua do thi vo huong bat dau tai s
// t = 1: cay khung DFS; t = 2: cay khung BFS. Khong lien thong thi in 0
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N], vs[N];
// Nhap ma tran n x n (n da doc truoc o main)
void nhapMaTran(){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
// T = cac canh cua cay khung, theo thu tu ket nap
vector<pair<int,int>> T;
// muc 4.1
void TreeDFS(int u){
    vs[u] = 1;
    for (int v = 1; v <= n; v++)
        if (a[u][v] && !vs[v]){ T.push_back({u, v}); TreeDFS(v); }
}
// muc 4.2
void TreeBFS(int u){
    queue<int> q; q.push(u); vs[u] = 1;
    while (!q.empty()){
        int s = q.front(); q.pop();
        for (int t = 1; t <= n; t++)
            if (a[s][t] && !vs[t]){ q.push(t); vs[t] = 1; T.push_back({s, t}); }
    }
}
int main(){
    freopen("CK.INP", "r", stdin);
    freopen("CK.OUT", "w", stdout);
    int t, s; cin >> t >> n >> s;
    nhapMaTran();
    if (t == 1) TreeDFS(s);
    else TreeBFS(s);
    // it hon n - 1 canh = do thi khong lien thong
    if ((int)T.size() < n - 1){ cout << 0; return 0; }
    cout << n - 1 << "\n";
    for (auto e : T) cout << e.first << " " << e.second << "\n";
}

/*
Test 1
input:
1
4 1
0 1 1 1
1 0 1 1
1 1 0 1
1 1 1 0
expected output:
3
1 2
2 3
3 4

Test 2
input:
2
4 1
0 1 1 1
1 0 1 1
1 1 0 1
1 1 1 0
expected output:
3
1 2
1 3
1 4
*/
