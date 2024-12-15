/* самостоятельно напишите код, требуемый по условию задачи */
#include <iostream>

using namespace std;

bool IsPowOfTwo(int N){
    if (N%2 == 0 && N != 0){
        return N/2;
    }
    if (N == 1){
        return 1;
    }
    return 0;
}

int main() {
    cout << IsPowOfTwo(1024) << endl;
} 