// TRR5007 - Duong di ngan nhat tu s den t bang Bellman-Ford (co the co canh am)
// Co chu trinh am thi in -1; khong co duong di thi in 0
#include <bits/stdc++.h>
using namespace std;
// de bai dung 10000 cho "khong co canh" -> dung luon lam INF
const int N = 105, INF = 10000;
int n, a[N][N], truoc[N];
// Nhap ma tran n x n (n da doc truoc o main)
void nhapMaTran(){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
int d[N];
// muc 3.2: tra ve false neu co chu trinh am
bool BellmanFord(int s){
    for (int v = 1; v <= n; v++){ d[v] = a[s][v]; truoc[v] = s; }
    d[s] = 0;
    for (int k = 1; k <= n - 2; k++)
        for (int v = 1; v <= n; v++) if (v != s)
            for (int u = 1; u <= n; u++)
                if (d[u] < INF && a[u][v] < INF && d[u] + a[u][v] < d[v]){
                    d[v] = d[u] + a[u][v]; truoc[v] = u;
                }
    // con giam duoc => co chu trinh am
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            if (d[u] < INF && a[u][v] < INF && d[u] + a[u][v] < d[v]) return false;
    return true;
}
int main(){
    freopen("BN.INP", "r", stdin);
    freopen("BN.OUT", "w", stdout);
    int s, t; cin >> n >> s >> t;
    nhapMaTran();
    if (!BellmanFord(s)){ cout << -1; return 0; }
    if (d[t] == INF){ cout << 0; return 0; }
    // lan nguoc tu t ve s theo truoc[] roi dao nguoc
    vector<int> p;
    for (int v = t; v != s; v = truoc[v]) p.push_back(v);
    p.push_back(s); reverse(p.begin(), p.end());
    cout << d[t] << "\n";
    for (int x : p) cout << x << " ";
}

/*
Test 1
input:
4 1 4
0 4 3 10000
10000 0 -2 10000
10000 10000 0 1
-1 10000 10000 0
expected output:
3
1 2 3 4

Test 2
input:
4 1 4
0 4 2 10000
10000 0 -2 10000
10000 10000 0 1
-4 10000 10000 0
expected output:
-1
*/
