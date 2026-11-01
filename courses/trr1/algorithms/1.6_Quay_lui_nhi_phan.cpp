// 1.6. Quay lui xau nhi phan do dai n
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao + Result) =====
int n, X[25];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

// ===== Code nguyen van =====
void Try(int i){
    for (int j = 0; j <= 1; j++){
        X[i] = j;
        if (i == n) Result(n);
        else Try(i + 1);
    }
}
int main(){ cin >> n; Try(1); }

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
