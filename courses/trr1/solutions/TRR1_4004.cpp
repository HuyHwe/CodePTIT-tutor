// TRR1_4004. Bai toan phan viec 02
// Ap dung 2.4. Duyet toan bo: phan viec, doi sang tim tong nang suat LON NHAT
// Nhap: n, roi ma tran nang suat n x n
#include <bits/stdc++.h>
using namespace std;

int n, c[25][25], x[25], xopt[25], fopt;

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> c[i][j];
    // x tang dan: 1, 2, ..., n

    for (int i = 1; i <= n; i++) x[i] = i;
    // bai toan max: fopt = -vo cung
    fopt = -1;

    do {
        int S = 0;
        for (int t = 1; t <= n; t++) S += c[t][x[t]];
        if (S > fopt){ fopt = S; memcpy(xopt, x, sizeof x); }
    } while (next_permutation(x + 1, x + n + 1));   // hoan vi x[1..n]

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
