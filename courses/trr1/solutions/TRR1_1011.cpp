// TRR1_1011. Phuong trinh 03
// p = "ax^4 + bx^2 + c = 0 co it nhat mot nghiem thuc"
// Dat y = x^2: chi can phuong trinh theo y co nghiem y >= 0
#include <bits/stdc++.h>
using namespace std;

double a, b, c;

int main(){
    cin >> a >> b >> c;
    int p = 0;
    if (a == 0){
        // 0 = 0: vo so nghiem
        if (b == 0) p = (c == 0);
        // by + c = 0: y = -c/b
        else p = (-c / b >= 0);
    }
    else {
        // bac hai theo y: xet delta
        double D = b * b - 4 * a * c;
        if (D >= 0){
            double y1 = (-b + sqrt(D)) / (2 * a), y2 = (-b - sqrt(D)) / (2 * a);
            p = (y1 >= 0 || y2 >= 0);
        }
    }
    cout << p;
}

/*
Test case
Input:
5.0 -7.5 1.3
Output:
1
*/
