#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

string GetLine(istream& in) {
    string s;
    getline(in, s);
    return s;
}

// реализуйте эту функцию:
void CreateFiles(const string& config_file) {
    ifstream input(config_file);
    ofstream out;
    while (true) {
        string str = GetLine(input);
        if (str.empty()) {
            return;
        }
        if (str[0] != '>') {
            out.close();
            out.open(str);
        }
        else {
            str.erase(0, 1);
            out << str << endl;;
        }   
    }
}

int main() {
    ofstream("test_config.txt"s) << "a.txt\n"
                                    ">10\n"
                                    ">abc\n"
                                    "b.txt\n"
                                    ">123"s;

    CreateFiles("test_config.txt"s);
    ifstream in_a("a.txt"s);
    assert(GetLine(in_a) == "10"s && GetLine(in_a) == "abc"s);

    ifstream in_b("b.txt"s);
    assert(GetLine(in_b) == "123"s);
}