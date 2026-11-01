// LT004. Duyet toan bo 03 (Bai toan nguoi du lich)
// Ap dung 2.3. Duyet toan bo: nguoi du lich, luu them TAT CA phuong an toi uu
// Nhap: n, roi ma tran chi phi n x n
#include <bits/stdc++.h>
using namespace std;

int n, c[35][35], x[35], fopt;
// cac hanh trinh toi uu
vector<vector<int>> xopt;

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> c[i][j];

    for (int i = 1; i <= n; i++) x[i] = i;
       // hoan vi dau tien
    fopt = INT_MAX;
    do {
        int S = c[x[n]][1];
        for (int i = 1; i < n; i++) S += c[x[i]][x[i+1]];
        // tot hon: bo cac phuong an cu
        if (S < fopt){ fopt = S; xopt.clear(); }
        // bang fopt: them vao danh sach
        if (S == fopt) xopt.push_back(vector<int>(x + 1, x + n + 1));
    } while (next_permutation(x + 2, x + n + 1));   // chi hoan vi x[2..n]

    if (xopt.size() == 1) cout << fopt << "\n";
    else cout << fopt << " " << xopt.size() << "\n";
    for (auto &p : xopt){
        for (int v : p) cout << v << " ";
        cout << "\n";
    }
}

/*
Test case 1
Input:
4
0 1 8 9
7 0 9 2
1 9 0 8
7 8 2 0
Output:
6
1 2 4 3

Test case 2
Input:
4
0 1 1 5
1 0 5 1
1 5 0 1
5 1 1 0
Output:
4 2
1 2 4 3
1 3 4 2
*/
