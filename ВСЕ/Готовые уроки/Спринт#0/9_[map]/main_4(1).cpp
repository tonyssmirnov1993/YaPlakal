#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

string FindWidespreadBird(const vector<string>& types) {
    // напишите здесь ваше решение
    map<string, int> birds;
    for (auto& names : types) {
        ++birds[names];
    }
    string widespread_birds;
    int current_max=0;
    for (auto [value, key] : birds) { 
        if (birds[value]>current_max) {
            current_max=birds[value];
            widespread_birds=value;
        }
    }
    return widespread_birds;
}

int main() {
    vector<string> bird_types1 = {"zyablik"s, "sinica"s, "vorobey"s, "zyablik"s, "sinica"s, "sinica"s};
    if (FindWidespreadBird(bird_types1) == "sinica"s) {
        cout << "Correct"s << endl;
    } else {
        cout << "Not correct"s << endl;
    }

    vector<string> bird_types2 = {"ruh"s, "sirin"s, "blue bird of fortune"s, "finist"s, "fenix"s};
    if (FindWidespreadBird(bird_types2) == "blue bird of fortune"s ) {
        cout << "Correct"s << endl;
    } else {
        cout << "Not correct"s << endl;
    }
}