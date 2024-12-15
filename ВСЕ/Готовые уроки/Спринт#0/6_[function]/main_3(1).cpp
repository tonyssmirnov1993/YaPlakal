#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(string query) {	//Описываем функцию
    vector<string> words;
    string word;
    for (char c : query) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word); //заполняем вектор
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
	vector<string> words;	
    string query;
	getline(cin, query);
		for (string word : SplitIntoWords(query)) { //Проходя по циклу, вызываем функцию на каждой итерации
				cout << '[' << word << ']' << endl;
		}
}