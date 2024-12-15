#include <iostream>
#include <string>
#include <vector>

using namespace std;

string ReadSearchQuery() {
        string query;
        getline(cin, query);
        return query;
} 

vector<string> SplitIntoWords(const string& text) {
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
	  // ваш код
    
    for (const string& x : SplitIntoWords(ReadSearchQuery())){
        cout << "["s << x << "]"s << " "s;
    }
}