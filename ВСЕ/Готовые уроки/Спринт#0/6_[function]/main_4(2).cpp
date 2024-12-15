#include <iostream>
#include <string>
#include <vector>

using namespace std;

// определяет, будет ли строка s палиндромом
bool IsPalindrome(string s) {
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

vector<string> PalindromeFilter(vector<string> words, int min_length) {
    // Возвращает из words все строки-палиндромы длиной не меньше min_length
    // Эта функция должна вызывать написанную выше функцию IsPalindrome
    vector<string> palindrome_words;
    for (string word : words) {
        if (word.size()>=min_length && IsPalindrome(word)==true){
            palindrome_words.push_back(word);
        }
    }
    return palindrome_words;
}

int main (){
    
}