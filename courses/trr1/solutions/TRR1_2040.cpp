// TRR1_2040. Xau nhi phan 14
// Xau do dai n co tong chu so = s <=> chon s vi tri dat so 1: t = C(n, s)
#include <bits/stdc++.h>
using namespace std;

int n, s;
long long C[55][55];

int main(){
    cin >> n >> s;
    // tam giac Pascal
    for (int i = 0; i <= n; i++){
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
    if (s < 0 || s > n) cout << 0;
    else cout << C[n][s];
}

/*
Test case
Input:
3 1
Output:
3
*/
