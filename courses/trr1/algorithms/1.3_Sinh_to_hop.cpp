// 1.3. Sinh to hop chap k cua n
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao + Result) =====
int n, k, X[25];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

// ===== Code nguyen van =====
bool Sinh(){
    int i = k;
    // tim t tu phai: X[t] < n - k + t
    while (i >= 1 && X[i] == n - k + i) i--;
    if (i == 0) return false;
    X[i]++;
    for (int j = i + 1; j <= k; j++) X[j] = X[i] + j - i;
    return true;
}
int main(){
    cin >> n >> k;
    // cau hinh dau: 1 2 ... k
    for (int i = 1; i <= k; i++) X[i] = i;
    do Result(k); while (Sinh());
}

/*
Test case
Input:
4 2
Output:
1 2
1 3
1 4
2 3
2 4
3 4
*/
