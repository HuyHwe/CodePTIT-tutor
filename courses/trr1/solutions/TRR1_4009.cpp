// TRR1_4009. Bai toan phan viec 04
// Ap dung 2.8. Nhanh can: phan viec, doi sang tim tong nang suat LON NHAT
// Nhap: n, roi ma tran nang suat n x n
#include <bits/stdc++.h>
using namespace std;

int n, c[25][25], x[25], xopt[25], vs[25], fopt, delta;

// bai toan max: dung cmax de tinh can tren
int cmax = 0;

void Try(int i){
    for (int j = 1; j <= n; j++) if (!vs[j]){
        x[i] = j; vs[j] = 1; delta += c[i][j];
        if (i == n){
            if (delta > fopt){ fopt = delta; memcpy(xopt, x, sizeof x); }
        }
        else if (delta + (n - i) * cmax > fopt)
            // can tren g > fopt
            Try(i + 1);
        // quay lui
        vs[j] = 0; delta -= c[i][j];
    }
}
int main(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++){
            cin >> c[i][j]; cmax = max(cmax, c[i][j]);
        }
    fopt = -1; delta = 0; Try(1);
    cout << fopt << "\n";
    for (int i = 1; i <= n; i++) cout << xopt[i] << " ";
}

/*
Test case
Input:
4
1 1 3 6
7 1 3 2
1 9 2 5
3 3 8 2
Output:
30
4 1 2 3
*/
