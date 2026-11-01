// TRR1015 - Do thi co huong cho bang danh sach canh
// t = 1: in ban bac vao, ban bac ra; t = 2: in ma tran ke
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, m, a[N][N];
// Nhap danh sach canh: n m, roi m dong "u v"
void nhapCanh(bool coHuong){
    cin >> n >> m;
    for (int u, v; m--; ){
        cin >> u >> v;
        a[u][v]++; if (!coHuong) a[v][u]++;
    }
}
// deg-(u) = tong cot u (cung di vao), deg+(u) = tong hang u (cung di ra)
void inBac(){
    for (int u = 1; u <= n; u++){
        int vao = 0, ra = 0;
        for (int v = 1; v <= n; v++){ vao += a[v][u]; ra += a[u][v]; }
        cout << vao << " " << ra << "\n";
    }
}
void inMaTran(){
    cout << n << "\n";
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++) cout << a[i][j] << " ";
        cout << "\n";
    }
}
int main(){
    freopen("DT.INP", "r", stdin);
    freopen("DT.OUT", "w", stdout);
    int t; cin >> t;
    nhapCanh(true);
    if (t == 1) inBac();
    else inMaTran();
}

/*
Test 1
input:
1
4 7
1 2
1 4
2 3
2 4
3 1
3 2
4 3
expected output:
1 2
2 2
2 2
2 1

Test 2
input:
2
4 7
1 2
1 4
2 3
2 4
3 1
3 2
4 3
expected output:
4
0 1 0 1
0 0 1 1
1 1 0 0
0 0 1 0
*/
