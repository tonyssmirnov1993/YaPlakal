#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int q;
    cin >> q;
    vector<bool> nervy; // создайте вектор типа vector<bool> для хранения очереди
    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;
        if (operation_code == "WORRY"s) {
            int index;
            cin >> index;
            nervy[index] = true; // Отметьте человека по индексу index как беспокоящегося (значение true)
        } else if (operation_code == "HAPPY"s) {
            int index;
            cin >> index;
            nervy[index] = false; // Отметьте человека по индексу index как спокойного (значение false).
        } else if (operation_code == "COME"s) {
            int count;
            cin >> count;
            nervy.resize(nervy.size() + count, false); //Измените размер на count. Указывайте второй параметр метода resize, чтобы добавлялись только спокойные (значение false).
        } else if (operation_code == "LAST_WORRY"s)  {
            if (nervy.back()) {
                cout << "worry"s << endl;
            } else {
                cout << "happy"s << endl;
            }
        } else if (operation_code == "WORRY_COUNT"s) {
            int worry_count=0;
            for (bool status : nervy) {
                if (status==true) {
                    ++worry_count;
                }
            }
            cout << worry_count << endl;
        }
    }
}