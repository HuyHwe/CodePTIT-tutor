// TRR1_1009. Phuong trinh 01
// p = "ax + b = 0 co it nhat mot nghiem thuc am"
#include <bits/stdc++.h>
using namespace std;

double a, b;

int main(){
    cin >> a >> b;
    int p;
    // a = 0: b = 0 thi vo so nghiem (co nghiem am), b != 0 thi vo nghiem
    if (a == 0) p = (b == 0);
    // a != 0: nghiem duy nhat x = -b/a
    else p = (-b / a < 0);
    cout << p;
}

/*
Test case
Input:
5.0 7.5
Output:
1
*/
