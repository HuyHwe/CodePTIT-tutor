// TRR1_5021. Chon cap so 08
// Nguyen ly Dirichlet: xau nhat la chon het cac cap (x, y) co x * y KHONG chia het cho 4,
// sau do chon them k cap nua => t = (so cap xau) + k
#include <bits/stdc++.h>
using namespace std;

long long n, k;

int main(){
    cin >> n >> k;
    // le = so le trong [1, n], du2 = so chia 4 du 2 trong [1, n]
    long long le = (n + 1) / 2, du2 = (n + 2) / 4;
    // x * y khong chia het cho 4: (le, le), (le, du2), (du2, le)
    long long xau = le * le + 2 * le * du2;
    long long kq = xau + k;
    // khong du n * n cap thi khong tim duoc
    if (kq > n * n) cout << 0;
    else cout << kq;
}

/*
Test case
Input:
4 2
Output:
10
*/
