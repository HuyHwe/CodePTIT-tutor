// 1.3. BFS
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

void BFS(int u){
    queue<int> q; q.push(u); vs[u] = 1;
    while (!q.empty()){
        int s = q.front(); q.pop(); cout << s << " ";
        for (int t = 1; t <= n; t++)
            if (a[s][t] && !vs[t]){ q.push(t); vs[t] = 1; }
    }
}
int main(){ nhapMaTran(); BFS(1); }

/*
input:
6
0 1 1 0 0 0
1 0 0 1 0 0
1 0 0 0 1 0
0 1 0 0 0 1
0 0 1 0 0 0
0 0 0 1 0 0
expected output:
1 2 3 4 5 6
*/
