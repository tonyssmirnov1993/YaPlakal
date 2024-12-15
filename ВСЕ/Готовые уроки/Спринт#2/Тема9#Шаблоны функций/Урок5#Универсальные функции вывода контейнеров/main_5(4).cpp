#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;
template <typename Container>
void Print(ostream& out, const Container& container) {
    bool is_first = true;
    for (const auto& element : container) {
        if (!is_first) {
            out << ", "s;
        }
        else {
            is_first = false;
        }  
        out << element;
    }
}
template <typename Element>

ostream& operator<<(ostream& out, const vector<Element>& container) {
    Print(out, container);
    return out;
}  
template <typename Element>
ostream& operator<<(ostream& out, const set<Element>& container) {
    Print(out, container);
   return out;
}  

int main() {
    const set<string> cats = {"Мурка"s, "Белка"s, "Георгий"s, "Рюрик"s};
    cout << cats << endl; 
    const vector<int> ages = {10, 5, 2, 12};
    cout << ages << endl; 
    return 0;
}