#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;
                    //Print element
template <typename Container>
ostream& Print(ostream& out, const Container& container) {
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
    return out;
}
                    //перегруз функции print для случая с map
template <typename Key, typename Value>
ostream& Print(ostream& out, const map<Key, Value>& container) {
    bool is_first = true;
    for (const auto& [key, value] : container) {
        if (!is_first) {
            out <<  ", "s << "("s << key << ", "s << value << ")"s;
        } else {
            out << "("s << key << ", "s << value << ")"s;
            is_first = false;
        }      
    }
    return out;
}
                        //---===VECTOR===---
template <typename Element>
ostream& operator<<(ostream& out, const vector<Element>& container) {
    cout << "["s;
    Print(out, container);
    cout << "]"s;
    return out;
} 
                        //---===SET===---
template <typename Element>
ostream& operator<<(ostream& out, const set<Element>& container) {
   cout << "{"s;
   Print(out, container);
   cout << "}"s;
   return out;
}  
                        //---===MAP===---
template <typename Key, typename Value>
ostream& operator<<(ostream& out, const map<Key, Value>& container) {
    cout << "<"s;
    Print(out, container);
    cout << ">"s;
    return out;
}  

int main() {
    const set<string> cats = {"Мурка"s, "Белка"s, "Георгий"s, "Рюрик"s};
    cout << cats << endl; 
    const vector<int> ages = {10, 5, 2, 12};
    cout << ages << endl; 
    const map<string, int> cat_ages = {
                                            {"Мурка"s, 10}, 
                                            {"Белка"s, 5},
                                            {"Георгий"s, 2}, 
                                            {"Рюрик"s, 12}
    };
    cout << cat_ages << endl; 
    return 0;
}