// 2.2. Duyet toan bo: cai tui 0/1
// Nhap: n b, roi n cap w v voi tung do vat
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao) =====
int n, b, x[25], xopt[25], fopt;

// ===== Code nguyen van =====
// w = trong luong, v = gia tri
int w[25], v[25];
// quay lui nhi phan
void Try(int i){
    for (int j = 0; j <= 1; j++){
        x[i] = j;
        if (i < n){ Try(i + 1); continue; }
        // du n do vat: tinh f(X)
        int W = 0, V = 0;
        for (int t = 1; t <= n; t++){
            W += w[t] * x[t]; V += v[t] * x[t];
        }
        if (W <= b && V > fopt){
            fopt = V; memcpy(xopt, x, sizeof x); }
    }
}
int main(){
    cin >> n >> b;
    for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
    fopt = -1; Try(1);
    cout << "FOPT = " << fopt << "\nXOPT = ";
    for (int i = 1; i <= n; i++) cout << xopt[i] << " ";
}

/*
Test case
Input:
4 8
3 4
4 5
5 7
2 3
Output:
FOPT = 11
XOPT = 1 0 1 0
*/
