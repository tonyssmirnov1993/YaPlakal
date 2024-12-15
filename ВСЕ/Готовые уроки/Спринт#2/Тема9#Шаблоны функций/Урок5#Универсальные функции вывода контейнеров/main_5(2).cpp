#include <iostream>
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

int main() {
    const vector<int> ages = {10, 5, 2, 12};
    cout << ages << endl;
    return 0;
}