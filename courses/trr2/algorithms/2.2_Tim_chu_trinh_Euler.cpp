// 2.2. Tim chu trinh Euler va duong di Euler (do thi vo huong)
// Do thi co huong: trong vong for cua main thay deg += a[i][j] bang deg += a[i][j] - a[j][i],
// dieu kien deg % 2 bang deg == 1, va goi Euler(u, true).
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n, a[N][N];
// Nhap ma tran n x n
void nhapMaTran(){
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
}

void Euler(int u){
    stack<int> st; vector<int> CE; st.push(u);
    while (!st.empty()){
        int s = st.top(), t = 1;
        // t = dinh ke dau tien cua s
        while (t <= n && !a[s][t]) t++;
        if (t <= n){
            st.push(t);
            // xoa canh (s,t)
            a[s][t]--; a[t][s]--;
        } else { st.pop(); CE.push_back(s); }
    }
    reverse(CE.begin(), CE.end());
    for (int x : CE) cout << x << " ";
}
int main(){
    nhapMaTran();
    // chu trinh: bat dau tu dinh bat ky
    int u = 1;
    // duong di: dinh bac le dau tien
    for (int i = n; i >= 1; i--){
        int deg = 0;
        for (int j = 1; j <= n; j++) deg += a[i][j];
        if (deg % 2) u = i;
    }
    Euler(u);
}

/*
input:
4
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
expected output:
1 2 3 1 4 3
*/
