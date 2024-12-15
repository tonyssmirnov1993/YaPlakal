#include <string_view>
#include <map>
#include <cassert>
#include "my_assert.h"
 
using namespace std;
 
class Translator {
public:
    Translator() = default;
 
    void Add(string_view source, string_view target) {
        rus_eng_[static_cast<string>(source)] = target;
        eng_rus_[static_cast<string>(target)] = source;
    }
 
    string_view TranslateForward(string_view source) const {
        if (rus_eng_.count(static_cast<string>(source))) {
            return rus_eng_.at(static_cast<string>(source));
        }
        return {};
    }
    
    string_view TranslateBackward(string_view target) const {
        if (eng_rus_.count(static_cast<string>(target))){
            return eng_rus_.at(static_cast<string>(target));
    }
        return {};
    }
 
private:
    map<string, string> rus_eng_{};
    map<string, string> eng_rus_{};
};
 
void TestSimple() {
    Translator translator;
    translator.Add(string("okno"s), string("window"s));
    translator.Add(string("stol"s), string("table"s));
 
    assert(translator.TranslateForward("okno"s) == "window"s);
    assert(translator.TranslateBackward("table"s) == "stol"s);
    assert(translator.TranslateForward("table"s) == ""s);
}
 
int main() {
    TestSimple();
    return 0;
}