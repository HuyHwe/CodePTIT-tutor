// 4.2. Cay khung bang BFS
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

vector<pair<int,int>> T;
void TreeBFS(int u){
    queue<int> q; q.push(u); vs[u] = 1;
    while (!q.empty()){
        int s = q.front(); q.pop();
        for (int t = 1; t <= n; t++)
            if (a[s][t] && !vs[t]){ q.push(t); vs[t] = 1; T.push_back({s, t}); }
    }
}
int main(){
    nhapMaTran(); TreeBFS(1);
    if ((int)T.size() < n - 1){ cout << "Do thi khong lien thong"; return 0; }
    for (auto e : T) cout << "(" << e.first << "," << e.second << ") ";
}

/*
input:
5
0 1 1 0 0
1 0 1 1 0
1 1 0 0 1
0 1 0 0 1
0 0 1 1 0
expected output:
(1,2) (1,3) (2,4) (3,5)
*/
