#include <iostream>
#include <string>

using namespace std;

int main() {
    int count;
    for (int i = 0; i < 10; ++i) { // Напишите цикл for, выполняющий 10 подходов к холодильнику.
        cin >> count;
        if (count == 0) {
            cout << "No cake :(" << endl;// Если торт не найдён выведите текст так:
            break;
        }
        cout << "Om-nom-nom :P" << endl;// А если найден, то так:  
    }
}