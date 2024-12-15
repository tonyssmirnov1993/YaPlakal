#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string, string> BuildReversedMap(const map<string, string>& input_map) {
    // Напишите реализацию функции тут
    map<string, string> temp;
    for (const auto&[animal, zov] : input_map) {
       // temp[animal]=zov; //они стали одинаковые два ключа и почему нельзя animal=zov, а zov=animal можно?!
        temp[zov]=animal;
    }
    return temp;
}

int main() {
    map<string, string> test1_input = {{"cat"s, "felis catus"s}, 
                                       {"dog"s, "canis lupus"s}};
    map<string, string> test1_output = {{"felis catus"s, "cat"s}, 
                                        {"canis lupus"s, "dog"s}};

    // Проверяем корректность BuildReversedMap на примере 
    if (BuildReversedMap(test1_input) != test1_output) {
        cout << "BuildReversedMap returned wrong dictionary"s << endl;
    }

    // Добавьте ещё тесты, чтобы убедиться, что ваша функция работает верно
}