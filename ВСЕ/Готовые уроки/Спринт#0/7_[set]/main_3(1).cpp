#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int CalculateSimilarity(vector<string> first, vector<string> second) {
    // верните размер пересечения множеств слов first и second
    set<string> result_v1,result_v2;
    for (string i : first) {
        result_v1.insert(i); //введенный текст query запихнули в вектор, а здесь через first во множество 
    }
    for (string i : second) {
        result_v2.insert(i); //введенный текст discription запихнули в вектор, а здесь через second во множество
    }
    int kol=0;
    for (string rel_word : result_v1) {
        if (result_v2.count(rel_word)){ //поиск релевантного решения, считаем, что есть в обоих множествах?
            ++kol; 
        }
    }
    return kol;
}

// SplitIntoWords разбивает строку text на слова и возвращает их в виде вектора
// Слово - последовательность непробельных символов,
// разделённых одним или более пробелов.
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
    string query, description;

    getline(cin, query);
    getline(cin, description);

    cout << CalculateSimilarity(SplitIntoWords(query), SplitIntoWords(description)) << endl;
}