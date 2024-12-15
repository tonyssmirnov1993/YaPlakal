#include <iostream>

using namespace std;

void Egg(int x) {
    if (1 == x) {
        cout << "Яйцо вызывает курицу"s << endl;
    } else {
        cout << "А вот и цыплёнок!"s << endl;
    }
}

int main() {
    Egg(1);
}
void Hen() {
    cout << "Курица вызывает яйцо"s << endl;
    Egg(0);
}