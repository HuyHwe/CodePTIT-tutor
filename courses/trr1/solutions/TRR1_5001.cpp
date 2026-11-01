// TRR1_5001. Cac qua cau
// Nguyen ly Dirichlet: co m * n loai qua cau (mau x kich thuoc)
// Xau nhat moi loai lay t - 1 qua => can m * n * (t - 1) + 1 qua
#include <bits/stdc++.h>
using namespace std;

long long h, m, n, t;

int main(){
    cin >> h >> m >> n >> t;
    long long kq = m * n * (t - 1) + 1;
    // hop khong du qua cau thi khong thuc hien duoc
    if (kq > h) cout << 0;
    else cout << kq;
}

/*
Test case 1
Input:
10 3 2 2
Output:
7

Test case 2
Input:
10 2 3 3
Output:
0
*/
