// TRR1_3006. Liet ke hoan vi truoc 01
// Ap dung 1.4. Sinh hoan vi, lam nguoc lai de tim hoan vi lien ke TRUOC
#include <bits/stdc++.h>
using namespace std;

int n, X[10005];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

// false = da la cau hinh dau (1 2 ... n)
bool Sinh(){
    int i = n - 1;
    // tu phai: vi tri dau tien X[i] > X[i+1]
    while (i >= 1 && X[i] < X[i+1]) i--;
    if (i == 0) return false;
    int j = n;
    // X[j] = so lon nhat ben phai ma < X[i]
    while (X[j] > X[i]) j--;
    swap(X[i], X[j]);
    // doan ben phai: tang -> giam
    int k = i+1, l = n;
    while (k < l) {
      swap(X[k], X[l]);
      k++; l--;
    }
    return true;
}
int main(){
    // input co the gom nhieu bo test
    while (cin >> n){
        for (int i = 1; i <= n; i++) cin >> X[i];
        if (Sinh()) Result(n);
        else cout << 0 << "\n";
    }
}

/*
Test case
Input:
5
3 1 2 5 4
Output:
3 1 2 4 5
*/
