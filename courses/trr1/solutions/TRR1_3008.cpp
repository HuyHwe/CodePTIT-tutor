// TRR1_3008. Liet ke to hop truoc 01
// Ap dung 1.3. Sinh to hop, lam nguoc lai de tim to hop lien ke TRUOC
#include <bits/stdc++.h>
using namespace std;

int n, k, X[105];
void Result(int m){ for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

// false = da la cau hinh dau (1 2 ... k)
bool Sinh(){
    X[0] = 0;
    int i = k;
    // tim i tu phai: X[i] > X[i-1] + 1 (con giam duoc)
    while (i >= 1 && X[i] == X[i-1] + 1) i--;
    if (i == 0) return false;
    X[i]--;
    // cac phan tu sau i nhan gia tri lon nhat: X[j] = n - k + j
    for (int j = i + 1; j <= k; j++) X[j] = n - k + j;
    return true;
}
int main(){
    cin >> n >> k;
    for (int i = 1; i <= k; i++) cin >> X[i];
    if (Sinh()) Result(k);
    else cout << 0;
}

/*
Test case
Input:
5 3
1 2 5
Output:
1 2 4
*/
