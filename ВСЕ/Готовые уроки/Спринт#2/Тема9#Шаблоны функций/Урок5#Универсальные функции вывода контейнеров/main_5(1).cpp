#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename Element>

ostream& operator<<(ostream& out, const vector<Element>& ages) {
    for (const Element& element : ages) {
        out << element << " "s;
    }
    return out;
}  

int main() {
    const vector<int> ages = {10, 5, 2, 12};
    cout << ages << endl;
    return 0;
}