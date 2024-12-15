#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
                                   //под нижний регистр
string NizRegistr(string& S) { 
string stroka;
for (auto& word : S) {
    stroka += tolower(word);
}
    return stroka;
}
 
int main()
{
    int kol_word;
    string stroka;
    vector<string> nabor_S; 
    cin >> kol_word;
    for (int i=0; i < kol_word; ++i) {
        cin >> stroka;
        nabor_S.push_back(stroka);
    } 
    sort(begin(nabor_S), end(nabor_S), []( string& str1,  string& str2) { //сортировка с лямбдой
        return NizRegistr(str1) < NizRegistr (str2);
    }); 
    for (const auto& sort_item : nabor_S) {
        cout << sort_item << " "s;
    }
    return 0;
}