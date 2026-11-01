// TRR3007 - Liet ke tat ca chu trinh Hamilton bat dau tai u (quay lui)
// Khong co thi in 0; co thi in tung chu trinh, dong cuoi in so luong
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N], vs[N];
// Nhap ma tran n x n (n da doc truoc o main)
void nhapMaTran(){
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}
// X[1..n] = chu trinh dang xay, dem = so chu trinh tim duoc
int X[N], dem;
// muc 2.3
void Hamilton(int k){
    for (int y = 1; y <= n; y++) if (a[X[k-1]][y]){
        // da di du n dinh va quay ve X[1]: ghi nhan
        if (k == n + 1 && y == X[1]){
            dem++; for (int i = 1; i <= n; i++) cout << X[i] << " ";
            cout << X[1] << "\n";
        }
        else if (!vs[y]){
            X[k] = y; vs[y] = 1;
            Hamilton(k + 1);
            // quay lui
            vs[y] = 0;
        }
    }
}
int main(){
    freopen("CT.INP", "r", stdin);
    freopen("CT.OUT", "w", stdout);
    int u; cin >> n >> u;
    nhapMaTran();
    X[1] = u; vs[u] = 1;
    Hamilton(2);
    cout << dem;
}

/*
Test 1
input:
4 1
0 1 0 0
0 0 1 0
0 0 0 1
1 0 0 0
expected output:
1 2 3 4 1
1

Test 2
input:
4 1
0 1 0 0
1 0 1 0
0 1 0 1
0 0 1 0
expected output:
0
*/
