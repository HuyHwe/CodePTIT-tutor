// TRR1_4001. Bai toan cai tui 01
// Ap dung 2.2. Duyet toan bo: cai tui 0/1
// Nhap: n b, roi n cap a c (trong luong, gia tri) cua tung do vat
#include <bits/stdc++.h>
using namespace std;

int n, b, x[25], xopt[25], fopt;

// w = trong luong, v = gia tri
int w[25], v[25];
// quay lui nhi phan
void Try(int i){
    // thu x[i] = 1 truoc: neu nhieu phuong an cung toi uu thi lay phuong an
    // chon do vat som hon (CodePTIT yeu cau thu tu nay)
    for (int j = 1; j >= 0; j--){
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
    cout << fopt << "\n";
    for (int i = 1; i <= n; i++) cout << xopt[i] << " ";
}

/*
Test case
Input:
3 8
5 8
7 12
3 7
Output:
15
1 0 1
*/
