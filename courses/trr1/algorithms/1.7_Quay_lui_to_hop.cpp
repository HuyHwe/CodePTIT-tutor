// 1.7. Quay lui to hop chap k cua n
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao + Result) =====
int n, k, X[25];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

// ===== Code nguyen van =====
void Try(int i){
    for (int j = X[i-1] + 1; j <= n - k + i; j++){
        X[i] = j;
        if (i == k) Result(k);
        else Try(i + 1);
    }
}
int main(){ cin >> n >> k; X[0] = 0; Try(1); }

/*
Test case
Input:
5 3
Output:
1 2 3
1 2 4
1 2 5
1 3 4
1 3 5
1 4 5
2 3 4
2 3 5
2 4 5
3 4 5
*/
