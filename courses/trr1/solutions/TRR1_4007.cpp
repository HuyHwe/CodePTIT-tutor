// TRR1_4007. Bai toan nguoi du lich 02
// Ap dung 2.7. Nhanh can: nguoi du lich
// Nhap: n, roi ma tran chi phi n x n
#include <bits/stdc++.h>
using namespace std;

int n, c[35][35], x[35], xopt[35], vs[35], fopt, delta;

int cmin = INT_MAX;
void Try(int k){
    for (int j = 2; j <= n; j++) if (!vs[j]){
        x[k] = j; vs[j] = 1; delta += c[x[k-1]][j];
        if (k == n){
            if (delta + c[j][1] < fopt){
                fopt = delta + c[j][1]; memcpy(xopt, x, sizeof x);
            }
        }
        // can duoi g = delta + (n - k + 1) * cmin
        else if (delta + (n - k + 1) * cmin < fopt) Try(k + 1);
        vs[j] = 0; delta -= c[x[k-1]][j];
    }
}
int main(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++){
            cin >> c[i][j];
            if (i != j) cmin = min(cmin, c[i][j]);
        }
    fopt = INT_MAX; delta = 0; x[1] = 1; vs[1] = 1; Try(2);
    cout << fopt << "\n";
    for (int i = 1; i <= n; i++) cout << xopt[i] << " ";
}

/*
Test case
Input:
4
0 1 8 9
7 0 9 2
1 9 0 8
7 8 2 0
Output:
6
1 2 4 3
*/
