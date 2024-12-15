#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

template <typename Element>

ostream& operator<<(ostream& out, const vector<Element>& ages) {
    bool is_first = true;
    for (const Element& element : ages) {
        if (!is_first) {
            out << ", "s;
        }
        else {
            is_first = false;
        }  
        out << element;
    }
    return out;
}  
template <typename Element>
ostream& operator<<(ostream& out, const set<Element>& cats) {
    bool is_first = true;
    for (const Element& element : cats) {
        if (!is_first) {
            out << ", "s;
        }
        else {
            is_first = false;
        }  
        out << element;
    }
    return out;
}  

int main() {
    const vector<int> ages = {10, 5, 2, 12};
    cout << ages << endl;
    const set<string> cats = {"Мурка"s, "Белка"s, "Георгий"s, "Рюрик"s};
    cout << cats << endl; 
    return 0;
}