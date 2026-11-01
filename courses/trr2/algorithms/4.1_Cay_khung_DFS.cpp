// 4.1. Cay khung bang DFS
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
void TreeDFS(int u){
    vs[u] = 1;
    for (int v = 1; v <= n; v++)
        if (a[u][v] && !vs[v]){ T.push_back({u, v}); TreeDFS(v); }
}
int main(){
    nhapMaTran(); TreeDFS(1);
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
(1,2) (2,3) (3,5) (5,4)
*/
