// TRR1_2002. Dem so 02
// Nguyen ly bu tru: |boi k hoac m| = |boi k| + |boi m| - |boi BCNN(k, m)|
#include <bits/stdc++.h>
using namespace std;

long long a, b, k, m;

long long UCLN(long long x, long long y){ return y == 0 ? x : UCLN(y, x % y); }
// so luong boi cua k hoac m trong [1, x]
long long Dem(long long x){
    long long bcnn = k / UCLN(k, m) * m;
    return x / k + x / m - x / bcnn;
}
int main(){
    cin >> a >> b >> k >> m;
    // [a, b] = [1, b] bo di [1, a-1]
    cout << Dem(b) - Dem(a - 1);
}

/*
Test case
Input:
1 10 2 3
Output:
7
*/
