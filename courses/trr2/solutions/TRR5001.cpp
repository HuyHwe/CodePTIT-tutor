// TRR5001 - Duong di ngan nhat tu s den t bang Dijkstra (trong so khong am)
// Khong co duong di thi in 0
#include <bits/stdc++.h>
using namespace std;
// de bai dung 10000 cho "khong co canh" -> dung luon lam INF
const int N = 105, INF = 10000;
int n, a[N][N], vs[N], truoc[N];
// Nhap ma tran n x n (n da doc truoc o main)
void nhapMaTran(){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
int d[N];
// muc 3.1
void Dijkstra(int s){
    for (int v = 1; v <= n; v++){ d[v] = a[s][v]; truoc[v] = s; }
    // vs = da co nhan co dinh
    d[s] = 0; vs[s] = 1;
    for (int i = 1; i < n; i++){
        int u = 0;
        // u = dinh tam thoi co d nho nhat
        for (int v = 1; v <= n; v++)
            if (!vs[v] && (!u || d[v] < d[u])) u = v;
        // cac dinh con lai khong toi duoc
        if (d[u] == INF) break;
        // co dinh nhan u
        vs[u] = 1;
        for (int v = 1; v <= n; v++)
            if (!vs[v] && d[u] + a[u][v] < d[v]){ d[v] = d[u] + a[u][v]; truoc[v] = u; }
    }
}
void inDuong(int s, int t){
    if (d[t] == INF){ cout << 0; return; }
    vector<int> p;
    for (int v = t; v != s; v = truoc[v]) p.push_back(v);
    p.push_back(s); reverse(p.begin(), p.end());
    cout << d[t] << "\n";
    for (int x : p) cout << x << " ";
}
int main(){
    freopen("DN.INP", "r", stdin);
    freopen("DN.OUT", "w", stdout);
    int s, t; cin >> n >> s >> t;
    nhapMaTran();
    Dijkstra(s);
    inDuong(s, t);
}

/*
Test 1
input:
4 1 2
0 7 8 2
10000 0 10000 10000
10000 1 0 10000
10000 5 1 0
expected output:
4
1 4 3 2

Test 2
input:
4 2 4
0 7 8 2
10000 0 5 10000
10000 1 0 10000
10000 5 1 0
expected output:
0
*/
