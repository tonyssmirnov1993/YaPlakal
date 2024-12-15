#include <iostream>
#include <string>

using namespace std;

void PrintSpacesPositions(string& str) {
    auto pos = str.find(' ');           // Находим первый пробел и сохраняем его индекс
    while (pos != string::npos)         // Если пробел в строке есть
    {
        cout << pos << endl;            // Выводим индекс
        pos = str.find(' ', pos + 1);   // Ищем следующий пробел
    }
}
int main() {
    string str = "He said: one and one and one is three"s;
    PrintSpacesPositions(str);
    return 0;
}