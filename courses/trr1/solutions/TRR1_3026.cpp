// TRR1_3026. Liet ke to hop co dieu kien su dung phuong phap quay lui (Dang 2)
// Ap dung 1.7. Quay lui to hop, them dieu kien X[k] = t
#include <bits/stdc++.h>
using namespace std;

int n, k, t, X[35], dem;
void Result(int m){ dem++; for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

void Try(int i){
    for (int j = X[i-1] + 1; j <= n - k + i; j++){
        // chap thuan j: phan tu thu k phai bang t
        if (i == k && j != t) continue;
        X[i] = j;
        if (i == k) Result(k);
        else Try(i + 1);
    }
}
int main(){
    cin >> n >> k >> t; X[0] = 0; Try(1);
    if (dem == 0) cout << 0;
}

/*
Test case
Input:
5 3 4
Output:
1 2 4
1 3 4
2 3 4
*/
