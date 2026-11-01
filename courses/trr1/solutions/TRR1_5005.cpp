// TRR1_5005. Chon so 03
// Nguyen ly Dirichlet: xau nhat la chon het cac so co so du p,
// chon them 1 so nua thi chac chan co so du khac p => t = (so luong so du p) + 1
// So luong so du p dem trong doan [0, n - 1] (giu nhu loi giai da nop)
#include <bits/stdc++.h>
using namespace std;

long long n, m, p;

int main(){
    cin >> n >> m >> p;
    p %= m;
    // cac so p, p + m, p + 2m, ... <= n - 1
    long long dem = (n - 1 >= p) ? (n - 1 - p) / m + 1 : 0;
    cout << dem + 1;
}

/*
Test case
Input:
10 5 3
Output:
3
*/
