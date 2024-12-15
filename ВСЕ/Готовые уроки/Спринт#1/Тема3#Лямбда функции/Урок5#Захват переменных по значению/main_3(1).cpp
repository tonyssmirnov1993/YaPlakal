#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& query){
    vector<string> v;
    string word;
    for (const char& c : query) {
        if (c == ' ') {
            if (!word.empty()) {
                v.push_back(word);
                word.clear();
            }
        } 
        else {
            word += c;
        }
        if (!word.empty()) {
            v.push_back(word);
            }
        }
    return v;
}

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result;
    cin >> result;
    ReadLine();
    return result;
}

int main() {
    const int queryCount = ReadLineWithNumber();

    vector<string> queries(queryCount);
    for (string& query : queries) {
        query = ReadLine();
    }
    const string buzzword = ReadLine();
                                                     // Реализуйте эту лямбда-функцию
    cout << count_if(queries.begin(), queries.end(), [buzzword](const string& query) {  
       const vector<string> v = SplitIntoWords(query);
       return count(v.begin(), v.end(), buzzword) != 0; 
                                        // Верните true, если query содержит слово buzzword
    });
    cout << endl;
}