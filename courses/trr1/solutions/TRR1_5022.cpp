// TRR1_5022. Chon xau nhi phan 08
// Nguyen ly Dirichlet: xau nhat la chon het cac xau KHONG co dung k so 1,
// chon them 1 xau nua => t = 2^n - C(n, k) + 1
#include <bits/stdc++.h>
using namespace std;

int n, k;
long long C[55][55];

int main(){
    cin >> n >> k;
    if (k < 0 || k > n){ cout << 0; return 0; }
    // tam giac Pascal
    for (int i = 0; i <= n; i++){
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
    cout << (1LL << n) - C[n][k] + 1;
}

/*
Test case
Input:
3 2
Output:
6
*/
