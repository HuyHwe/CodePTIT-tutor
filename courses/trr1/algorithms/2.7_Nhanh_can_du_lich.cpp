// 2.7. Nhanh can: nguoi du lich
// Nhap: n, roi ma tran chi phi n x n
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao) =====
int n, c[25][25], x[25], xopt[25], vs[25], fopt, delta;

// ===== Code nguyen van =====
int cmin = INT_MAX;
void Try(int k){
    for (int j = 2; j <= n; j++) if (!vs[j]){
        x[k] = j; vs[j] = 1; delta += c[x[k-1]][j];
        if (k == n){
            if (delta + c[j][1] < fopt){
                fopt = delta + c[j][1]; memcpy(xopt, x, sizeof x);
            }
        }
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
    cout << "FOPT = " << fopt << "\nHanh trinh: ";
    for (int i = 1; i <= n; i++) cout << xopt[i] << " -> ";
    cout << 1;
}

/*
Test case
Input:
4
0 2 9 10
1 0 6 4
15 7 0 8
6 3 12 0
Output:
FOPT = 21
Hanh trinh: 1 -> 3 -> 4 -> 2 -> 1
*/
