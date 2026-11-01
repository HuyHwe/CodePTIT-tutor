// TRR1_3027. Liet ke xau nhi phan co dieu kien su dung phuong phap quay lui
// Ap dung 1.6. Quay lui xau nhi phan, them dieu kien k vi tri cho truoc
#include <bits/stdc++.h>
using namespace std;

// co[u] = v: vi tri u bat buoc la v (-1 = tu do)
int n, k, X[105], co[105], dem;
void Result(int m){ dem++; for (int i = 1; i <= m; i++) cout << X[i] << " "; cout << "\n"; }

void Try(int i){
    for (int j = 0; j <= 1; j++){
        // chap thuan j: vi tri tu do, hoac j dung gia tri cho truoc
        if (co[i] != -1 && j != co[i]) continue;
        X[i] = j;
        if (i == n) Result(n);
        else Try(i + 1);
    }
}
int main(){
    cin >> n >> k;
    for (int i = 1; i <= n; i++) co[i] = -1;
    for (int i = 1; i <= k; i++){
        int u, v; cin >> u >> v;
        co[u] = v;
    }
    Try(1);
    if (dem == 0) cout << 0;
}

/*
Test case
Input:
3 1
2 1
Output:
0 1 0
0 1 1
1 1 0
1 1 1
*/
