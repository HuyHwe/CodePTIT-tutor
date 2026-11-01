// TRR1_1018. Tap hop 02 (Giao cua hai tap hop)
// Nhap: n, roi 2 xau nhi phan bieu dien tap A va B
#include <bits/stdc++.h>
using namespace std;

int n, A[1005], B[1005], X[1005];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= n; i++) cin >> B[i];
    // i thuoc A giao B khi A[i] = 1 va B[i] = 1
    int k = 0;
    for (int i = 1; i <= n; i++) if (A[i] == 1 && B[i] == 1) X[++k] = i;
    cout << k << "\n";
    if (k > 0) Result(k);
}

/*
Test case
Input:
5
0 1 1 0 1
1 1 0 1 1
Output:
2
2 5
*/
