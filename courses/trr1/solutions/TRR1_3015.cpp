// TRR1_3015. Liet ke mot phan xau nhi phan su dung phuong phap sinh thuan
// Ap dung 1.2. Sinh xau nhi phan: goi Sinh() t lan
#include <bits/stdc++.h>
using namespace std;

int n, t, X[105];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

// false = da la cau hinh cuoi
bool Sinh(){
    int i = n;
    while (i >= 1 && X[i] == 1){ X[i] = 0; i--; }
    if (i == 0) return false;
    X[i] = 1;
    return true;
}
int main(){
    cin >> n >> t;
    for (int i = 1; i <= n; i++) cin >> X[i];
    for (int d = 1; d <= t; d++){
        if (Sinh()) Result(n);
        // het xau: in 0 roi dung
        else { cout << 0 << "\n"; break; }
    }
}

/*
Test case
Input:
5 2
1 0 0 0 1
Output:
1 0 0 1 0
1 0 0 1 1
*/
