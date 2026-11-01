// TRR1_2009. Dem phan so
// Moi phan so a/b toi gian (1 <= a <= b) ung voi a nguyen to cung nhau voi b
// => t = 1 (phan so 0/1) + phi(1) + phi(2) + ... + phi(n)
#include <bits/stdc++.h>
using namespace std;

int n;
long long phi[10005];

int main(){
    cin >> n;
    // sang ham phi Euler
    for (int i = 0; i <= n; i++) phi[i] = i;
    for (int i = 2; i <= n; i++) if (phi[i] == i)
        for (int j = i; j <= n; j += i) phi[j] -= phi[j] / i;
    long long t = 1;
    for (int b = 1; b <= n; b++) t += phi[b];
    cout << t;
}

/*
Test case
Input:
4
Output:
7
*/
