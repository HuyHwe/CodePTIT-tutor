// TRR1_2014. Xau nhi phan 04
// Dem xau nhi phan do dai n CO chua k chu so 1 lien tiep
// t = 2^n - (so xau KHONG chua k so 1 lien tiep)
// F[i] tinh giong TRR1_2011 (doi vai tro 0 <-> 1)
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
    cout << (1LL << n) - F[n];
}

/*
Test case
Input:
3 2
Output:
3
*/
