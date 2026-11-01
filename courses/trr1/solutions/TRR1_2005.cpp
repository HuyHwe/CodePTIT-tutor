// TRR1_2005. Dem so hinh vuong
// Chon cac canh nho nhat 1, 2, ..., t sao cho 1^2 + 2^2 + ... + t^2 <= n
#include <bits/stdc++.h>
using namespace std;

long long n;

int main(){
    cin >> n;
    long long t = 0, S = 0;
    // con du o vuong cho hinh canh t + 1 thi lay tiep
    while (S + (t + 1) * (t + 1) <= n){ t++; S += t * t; }
    cout << t;
}

/*
Test case
Input:
10
Output:
2
*/
