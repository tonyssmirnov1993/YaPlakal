#include <iostream>
#include <vector>
#include <string>

using namespace std;

void MoveStrings(vector<string>& source, vector<string>& destination) {
    for (string& word : source) {
        destination.push_back(word);
        source.clear();
    }
}

int main() {
    vector<string> source = {"how"s, "to"s, "learn"s};
    vector<string> destination = {"c++"s};
    MoveStrings(source, destination);
    for (string x : destination) {
        cout << x << endl;
    }
    
}