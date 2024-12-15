#include <set>
#include <string>
#include <numeric>

using namespace std;

string VSP_Func(string word, string dash) {
    return word+" -"s+dash;
}

string AddStopWords(const string& query, const set<string>& stop_words) {
    // Напишите тело функции.
    return accumulate(stop_words.begin(), stop_words.end(), query, VSP_Func);
}

int main() {
    
}