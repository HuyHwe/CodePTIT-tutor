// 2.8. Nhanh can: phan viec
// Nhap: n, roi ma tran thoi gian n x n
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao) =====
int n, c[25][25], x[25], xopt[25], vs[25], fopt, delta;

// ===== Code nguyen van =====
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
    cout << "FOPT = " << fopt << "\n";
    for (int i = 1; i <= n; i++)
        cout << "Nguoi " << i << " -> viec " << xopt[i] << "\n";
}

/*
Test case
Input:
3
9 2 7
6 4 3
5 8 1
Output:
FOPT = 9
Nguoi 1 -> viec 2
Nguoi 2 -> viec 1
Nguoi 3 -> viec 3
*/
