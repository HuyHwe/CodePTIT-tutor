// TRR2024 - Tim cac dinh tru cua do thi vo huong bang BFS
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
        int s = q.front(); q.pop();
        for (int t = 1; t <= n; t++)
            if (a[s][t] && !vs[t]){ q.push(t); vs[t] = 1; }
    }
}
// dem TPLT (muc 1.4) dung BFS, khong xoa vs de giu dinh bi cam
int demTPLT(){
    int d = 0;
    for (int u = 1; u <= n; u++)
        if (!vs[u]){ d++; BFS(u); }
    return d;
}
int main(){
    freopen("TK.INP", "r", stdin);
    freopen("TK.OUT", "w", stdout);
    nhapMaTran();
    int goc = demTPLT();
    vector<int> tru;
    // muc 1.8: bo u ma so TPLT tang -> u la dinh tru
    for (int u = 1; u <= n; u++){
        memset(vs, 0, sizeof vs);
        // cam di qua u = xoa u
        vs[u] = 1;
        if (demTPLT() > goc) tru.push_back(u);
    }
    cout << tru.size() << "\n";
    for (int u : tru) cout << u << " ";
}

/*
input:
5
0 1 0 0 0
1 0 1 0 0
0 1 0 1 1
0 0 1 0 1
0 0 1 1 0
expected output:
2
2 3
*/
