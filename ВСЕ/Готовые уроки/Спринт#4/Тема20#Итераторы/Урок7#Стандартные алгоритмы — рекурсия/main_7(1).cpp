/* самостоятельно напишите код, требуемый по условию задачи */
#include <iostream>

using namespace std;

int Fibonacci(int N) {
    if (N <= 1) 
        return N; 
    return Fibonacci(N - 1) + Fibonacci(N - 2); 
} 

int main() {
    cout << Fibonacci(6) << endl;
} 