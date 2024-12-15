#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;


vector<string> SplitIntoWords(string text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}


int main() {
    /* Считайте строку со стоп-словами */
    set<string> stop_words; // создаём множество стоп-слов
    vector<string> zapros; 
    string query,stop_query; 
    getline(cin, query);// Считываем строку-запрос
    for (string word : SplitIntoWords(query)) {
            stop_words.insert(word);
    }
    getline(cin, stop_query);
    for (string word : SplitIntoWords(stop_query)) {
        if (stop_words.count(word)==0) {
            zapros.push_back(word);
        }
    }
    for (string word : zapros) {
        cout << '[' << word << ']' << endl;// Выведите только те слова, которых нет среди стоп-слов
    }
}