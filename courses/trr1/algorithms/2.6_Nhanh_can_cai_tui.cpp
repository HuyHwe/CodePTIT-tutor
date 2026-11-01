// 2.6. Nhanh can: cai tui 0/1
// Nhap: n b, roi n cap w v
#include <bits/stdc++.h>
using namespace std;

// ===== Phan bo sung de chay duoc (khai bao) =====
int n, b, x[25], xopt[25], fopt, delta;

// ===== Code nguyen van =====
int w[25], v[25], id[25];
void Try(int k){
    for (int j = 1; j >= 0; j--){
        // khong du cho
        if (j * w[k] > b) continue;
        x[k] = j; delta += j * v[k]; b -= j * w[k];
        if (k == n){
            if (delta > fopt){ fopt = delta; memcpy(xopt, x, sizeof x); }
        }
        else if (delta + (double)b * v[k+1] / w[k+1] > fopt) Try(k + 1);
        delta -= j * v[k]; b += j * w[k];
    }
}

bool cmp(array<int,3> p, array<int,3> q){
    // v/w giam dan
    return p[1] * q[0] > q[1] * p[0];
}


int main(){
    cin >> n >> b;
    // {w, v, chi so goc}
    vector<array<int,3>> d(n);
    for (int i = 0; i < n; i++){
        cin >> d[i][0] >> d[i][1]; d[i][2] = i + 1;
    }
    sort(d.begin(), d.end(), cmp);
    for (int i = 1; i <= n; i++){
        w[i] = d[i-1][0]; v[i] = d[i-1][1]; id[i] = d[i-1][2];
    }
    fopt = 0; delta = 0; Try(1);
    int kq[25] = {};
    for (int i = 1; i <= n; i++) kq[id[i]] = xopt[i];
    cout << "FOPT = " << fopt << "\nXOPT = ";
    for (int i = 1; i <= n; i++) cout << kq[i] << " ";
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
