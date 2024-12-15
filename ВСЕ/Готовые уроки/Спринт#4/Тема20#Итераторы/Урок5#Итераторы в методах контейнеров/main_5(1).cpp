#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Container, typename It>
void EraseAndPrint(Container& container, It del_position){
    auto erase_position = container.erase(del_position);
    PrintRange(container.begin(),erase_position);
    PrintRange(erase_position,container.end());
}

int main() {
    vector<string> langs = {"Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s};
    EraseAndPrint(langs, langs.begin());
    return 0;
} 