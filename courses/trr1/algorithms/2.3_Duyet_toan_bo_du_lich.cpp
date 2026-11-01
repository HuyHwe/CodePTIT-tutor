// 2.3. Duyet toan bo: nguoi du lich
// Nhap: n, roi ma tran chi phi n x n
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao) =====
int n, c[25][25], x[25], xopt[25], fopt;

// ===== Code nguyen van =====
int main(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> c[i][j];

    for (int i = 1; i <= n; i++) x[i] = i;
       // hoan vi dau tien
    fopt = INT_MAX;
    do {
        int S = c[x[n]][1];
        for (int i = 1; i < n; i++) S += c[x[i]][x[i+1]];
        if (S < fopt){
         fopt = S; memcpy(xopt, x, sizeof x);
          }
    } while (next_permutation(x + 2, x + n + 1));   // chi hoan vi x[2..n]

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
