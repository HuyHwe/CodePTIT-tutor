// TRR1_1010. Phuong trinh 02
// p = "ax^2 + bx + c = 0 co it nhat mot nghiem thuc duong"
#include <bits/stdc++.h>
using namespace std;

double a, b, c;

int main(){
    cin >> a >> b >> c;
    int p = 0;
    if (a == 0){
        // 0 = 0: vo so nghiem, co nghiem duong
        if (b == 0) p = (c == 0);
        // bac nhat: x = -c/b
        else p = (-c / b > 0);
    }
    else {
        // bac hai: xet delta
        double D = b * b - 4 * a * c;
        if (D >= 0){
            double x1 = (-b + sqrt(D)) / (2 * a), x2 = (-b - sqrt(D)) / (2 * a);
            p = (x1 > 0 || x2 > 0);
        }
    }
    cout << p;
}

/*
Test case
Input:
5.0 7.5 1.3
Output:
0
*/
