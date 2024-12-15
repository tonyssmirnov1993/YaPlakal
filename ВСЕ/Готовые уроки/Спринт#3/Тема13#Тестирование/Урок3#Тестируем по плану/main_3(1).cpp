#include <iostream>
#include <string>

using namespace std;

// Определяет, будет ли слово палиндромом
// text может быть строкой, содержащей строчные буквы английского алфавита и пробелы
// Пустые строки и строки, состоящие только из пробелов, - это не палиндромы
string SplitWord(const string& text){
    string word;
    for (char c : text) {
        if (c == ' ') {
            continue;
        }
        else {
            word+=c;
        }
    }
    return word;
}

bool IsPalindrome(const string& text) {
    // Напишите недостающий код
    string word = SplitWord(text);
    if (word.empty()){
        return false;
    }
    for (int i=0; i < word.size() / 2 ; ++i){
        int from_back = word[word.size()-i-1];
        if (word[i] != from_back){
            return false;
        }
    } 
    return true;
}

int main() {
    string text;
    getline(cin, text);

    if (IsPalindrome(text)) {
        cout << "palindrome"s << endl;
    } else {
        cout << "not a palindrome"s << endl;
    }
}