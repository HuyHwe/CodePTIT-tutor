// TRR1_3016. Liet ke mot phan xau nhi phan su dung phuong phap sinh nguoc
// Ap dung 1.2. Sinh xau nhi phan, doi vai tro 0 <-> 1 de sinh theo thu tu nguoc
#include <bits/stdc++.h>
using namespace std;

int n, t, X[105];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

// false = da la cau hinh cuoi (00...0)
bool Sinh(){
    int i = n;
    while (i >= 1 && X[i] == 0){ X[i] = 1; i--; }
    if (i == 0) return false;
    X[i] = 0;
    return true;
}
int main(){
    cin >> n >> t;
    for (int i = 1; i <= n; i++) cin >> X[i];
    for (int d = 1; d <= t; d++)
        if (Sinh()) Result(n);
        else cout << 0 << "\n";
}

/*
Test case
Input:
5 2
1 0 1 0 1
Output:
1 0 1 0 0
1 0 0 1 1
*/
