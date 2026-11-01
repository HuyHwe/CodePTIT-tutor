// 1.4. Sinh hoan vi cua 1..n
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao + Result) =====
int n, X[25];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

// ===== Code nguyen van =====
bool Sinh(){
    int i = n - 1;
    // tu phai: vi tri dau tien X[i] < X[i+1]
    while (i >= 1 && X[i] > X[i+1]) i--;
    if (i == 0) return false;
    int j = n;
    // X[j] = so nho nhat ben phai ma > X[i]
    while (X[j] < X[i]) j--;
    swap(X[i], X[j]);
    // doan ben phai: giam -> tang
    int k = i+1, l = n;
    while (k < l) {
      swap(X[k], X[l]);
      k++; l--;
    }
    return true;
}
int main(){
    cin >> n;
    // cau hinh dau: 1 2 ... n
    for (int i = 1; i <= n; i++) X[i] = i;
    do Result(n); while (Sinh());
}

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
