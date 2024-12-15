#include <string>
#include <vector> // не забудьте подключить библиотеку <vector>

using namespace std;

int main() {
    vector<string> words;// Объявите переменную-вектор, которая будет хранить слова.// Назовите её words.
    string query;
    getline(cin, query);
    string word; 
    for (char c : query) {// Мы заменили обычный for на range-based.
        if (c == ' ') {
            if (!word.empty()){
            // Удалите вывод в cout и замените его на добавление элемента в вектор.
            words.push_back(query);
            cout << '[' << word << ']' << endl;
            word = ""s;
            }
        } else {
            word += c;// Добавьте в вектор последнее слово вместо вывода.
        }
    }   
    cout << '[' << word << ']' << endl;// Сюда вставьте вывод элементов вектора. 
}