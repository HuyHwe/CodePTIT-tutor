// TRR1_4003. Bai toan phan viec 01
// Ap dung 2.4. Duyet toan bo: phan viec (tong thoi gian nho nhat)
// Nhap: n, roi ma tran thoi gian n x n
#include <bits/stdc++.h>
using namespace std;

int n, c[25][25], x[25], xopt[25], fopt;

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
