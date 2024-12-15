#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

template<typename Container, typename Element>
void FindAndPrint(Container container, Element element) {
    auto element_position = find(container.begin(), container.end(), element);
    for (auto it = container.begin(); it != element_position; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
    for (auto it = element_position; it != container.end(); ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

int main() {
    set<int> test = {1, 1, 1, 2, 3, 4, 5, 5};
    cout << "Tест_1"s << endl;
    FindAndPrint(test, 3);
    cout << "Tест_2"s << endl;
    FindAndPrint(test, 0); // элемента 0 нет в контейнере
    cout << "Конец тестирования..."s << endl;
} 