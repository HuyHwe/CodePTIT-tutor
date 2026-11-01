// 2.3. Liet ke chu trinh Hamilton (quay lui)
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

int X[N], dem;
void Hamilton(int k){
    for (int y = 1; y <= n; y++) if (a[X[k-1]][y]){
        // quay ve v0: ghi nhan
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
    nhapMaTran();
    // v0 = 1
    X[1] = 1; vs[1] = 1;
    Hamilton(2);
    if (!dem) cout << "Khong co chu trinh Hamilton";
}

/*
input:
4
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
expected output:
1 2 3 4 1
1 4 3 2 1
*/
