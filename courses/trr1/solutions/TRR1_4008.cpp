// TRR1_4008. Bai toan phan viec 03
// Ap dung 2.8. Nhanh can: phan viec (tong thoi gian nho nhat)
// Nhap: n, roi ma tran thoi gian n x n
#include <bits/stdc++.h>
using namespace std;

int n, c[25][25], x[25], xopt[25], vs[25], fopt, delta;

int cmin = INT_MAX;

void Try(int i){
    for (int j = 1; j <= n; j++) if (!vs[j]){
        x[i] = j; vs[j] = 1; delta += c[i][j];
        if (i == n){
            if (delta < fopt){ fopt = delta; memcpy(xopt, x, sizeof x); }
        }
        else if (delta + (n - i) * cmin < fopt)
            // can duoi g < fopt
            Try(i + 1);
        // quay lui
        vs[j] = 0; delta -= c[i][j];
    }
}
int main(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++){
            cin >> c[i][j]; cmin = min(cmin, c[i][j]);
        }
    fopt = INT_MAX; delta = 0; Try(1);
    cout << fopt << "\n";
    for (int i = 1; i <= n; i++) cout << xopt[i] << " ";
}

/*
Test case
Input:
4
8 1 8 9
7 4 9 2
1 9 5 8
7 8 2 9
Output:
6
2 4 1 3
*/
