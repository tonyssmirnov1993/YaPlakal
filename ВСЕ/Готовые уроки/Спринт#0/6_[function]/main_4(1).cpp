#include <iostream>
#include <string>

using namespace std;

int Factorial(int x) {
    int f = 1;
    if (x > 0 && x <= 10) {
        for (int i = 1; i <= x; ++i) {
            f *= i;  // здесь вычисляем факториал числа и возвращаем полученное значение
        }
    }
    else {
        return 1;
    }
    return f;
}

int main() {
    int x;
    cin >> x;
    cout << Factorial(x) << endl;
}