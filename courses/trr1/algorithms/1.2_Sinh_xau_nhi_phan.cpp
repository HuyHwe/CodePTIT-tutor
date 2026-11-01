// 1.2. Sinh xau nhi phan do dai n
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao + Result) =====
int n, X[25];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

// ===== Code nguyen van =====
// false = da la cau hinh cuoi
bool Sinh(){
    int i = n;
    while (i >= 1 && X[i] == 1){ X[i] = 0; i--; }
    if (i == 0) return false;
    X[i] = 1;
    return true;
}
int main(){
    cin >> n;
    // cau hinh dau: 00...0
    for (int i = 1; i <= n; i++) X[i] = 0;
    do Result(n); while (Sinh());
}

/*
Test case
Input:
3
Output:
0 0 0
0 0 1
0 1 0
0 1 1
1 0 0
1 0 1
1 1 0
1 1 1
*/
