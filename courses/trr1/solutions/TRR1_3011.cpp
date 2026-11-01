// TRR1_3011. Liet ke mot phan hoan vi
// Ap dung 1.4. Sinh hoan vi: goi Sinh() t lan
#include <bits/stdc++.h>
using namespace std;

int n, t, X[1005];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

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
    cin >> n >> t;
    for (int i = 1; i <= n; i++) cin >> X[i];
    // da den hoan vi cuoi thi Sinh() giu nguyen X, cac dong con lai deu in 0
    for (int d = 1; d <= t; d++)
        if (Sinh()) Result(n);
        else cout << 0 << "\n";
}

/*
Test case
Input:
5 2
3 1 2 5 4
Output:
3 1 4 2 5
3 1 4 5 2
*/
