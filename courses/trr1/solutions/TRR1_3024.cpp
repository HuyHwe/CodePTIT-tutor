// TRR1_3024. Liet ke hoan vi co dieu kien su dung phuong phap quay lui
// Ap dung 1.8. Quay lui hoan vi, them dieu kien k vi tri cho truoc
#include <bits/stdc++.h>
using namespace std;

// co[u] = v: vi tri u bat buoc la so v (0 = tu do)
// giu[v] = 1: so v da danh cho mot vi tri cho truoc
int n, k, X[25], vs[25], co[25], giu[25], dem;
void Result(int m){ dem++; for (int i = 1; i <= m; i++) cout << X[i] << (i < m ? " " : ""); cout << "\n"; }

void Try(int i){
    // chi lay so j chua dung
    for (int j = 1; j <= n; j++) if (!vs[j]){
        // chap thuan j: vi tri cho truoc thi j phai dung gia tri,
        // vi tri tu do thi j khong duoc la so da danh rieng
        if (co[i] ? j != co[i] : giu[j]) continue;
        X[i] = j; vs[j] = 1;
        if (i == n) Result(n);
        else Try(i + 1);
        // tra lai j (quay lui)
        vs[j] = 0;
    }
}
int main(){
    cin >> n >> k;
    for (int i = 1; i <= k; i++){
        int u, v; cin >> u >> v;
        // cung vi tri u cho nhieu lan thi lay gia tri cuoi
        co[u] = v;
    }
    // danh dau cac so da danh cho vi tri cho truoc;
    // mot so bi cho o 2 vi tri khac nhau thi khong co hoan vi nao
    bool sai = false;
    for (int u = 1; u <= n; u++) if (co[u]){
        if (giu[co[u]]) sai = true;
        giu[co[u]] = 1;
    }
    if (!sai) Try(1);
    if (dem == 0) cout << 0;
}

/*
Test case
Input:
3 1
1 2
Output:
2 1 3
2 3 1
*/
