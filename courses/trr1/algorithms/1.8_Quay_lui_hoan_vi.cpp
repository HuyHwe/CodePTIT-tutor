// 1.8. Quay lui hoan vi cua 1..n
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao + Result) =====
int n, X[25], vs[25];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

// ===== Code nguyen van =====
void Try(int i){
    // chi lay so j chua dung
    for (int j = 1; j <= n; j++) if (!vs[j]){
        X[i] = j; vs[j] = 1;
        if (i == n) Result(n);
        else Try(i + 1);
        // tra lai j (quay lui)
        vs[j] = 0;
    }
}
int main(){ cin >> n; Try(1); }

/*
Test case
Input:
3
Output:
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
*/
