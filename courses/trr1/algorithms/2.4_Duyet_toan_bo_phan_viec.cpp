// 2.4. Duyet toan bo: phan viec
// Nhap: n, roi ma tran thoi gian n x n
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao) =====
int n, c[25][25], x[25], xopt[25], fopt;

// ===== Code nguyen van =====
int main(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> c[i][j];
    // x tang dan: 1, 2, ..., n

    for (int i = 1; i <= n; i++) x[i] = i;
    fopt = INT_MAX;

    do {
        int S = 0;
        for (int t = 1; t <= n; t++) S += c[t][x[t]];
        if (S < fopt){ fopt = S; memcpy(xopt, x, sizeof x); }
    } while (next_permutation(x + 1, x + n + 1));   // hoan vi x[1..n]

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
