// TRR1_2011. Xau nhi phan 01
// Dem xau nhi phan do dai n KHONG chua k chu so 0 lien tiep
// F[i] = so xau hop le do dai i
// i < k : moi xau deu hop le      -> F[i] = 2^i
// i = k : chi bo xau 00...0       -> F[i] = 2^k - 1
// i > k : xau ket thuc bang 1, 10, 100, ..., 10..0 (k-1 so 0)
//         -> F[i] = F[i-1] + F[i-2] + ... + F[i-k]
#include <bits/stdc++.h>
using namespace std;

int n, k;
long long F[55];

int main(){
    cin >> n >> k;
    F[0] = 1;
    for (int i = 1; i <= n; i++){
        if (i < k) F[i] = 1LL << i;
        else if (i == k) F[i] = (1LL << k) - 1;
        else {
            F[i] = 0;
            for (int j = 1; j <= k; j++) F[i] += F[i - j];
        }
    }
    cout << F[n];
}

/*
Test case
Input:
3 2
Output:
5
*/
