#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<pair<int, string>> kandidaty;//сначала возраст (для сортировки)
    int count;
    cin >> count;
    for (int i = 0; i < count; ++i) {
        string name;
        int age;
        cin >> name >> age;
        kandidaty.push_back({age, name}); // сохраните в вектор пар
    }
    sort(kandidaty.begin(), kandidaty.end());//сортировка по возрасту?
    reverse(kandidaty.begin(), kandidaty.end()); //по убыванию
    for (const auto& elem : kandidaty) {
        cout << elem.second << endl; //вывод имени (2ой ключ)
    }
    // Выведите только имена в порядке убывания возраста
    // Имена людей одинакового возраста нужно вывести в порядке, обратном алфавитному
}