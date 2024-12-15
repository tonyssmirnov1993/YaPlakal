#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool StartWithA (const string& str) {
  /*  if (!str.empty()) {
        if (str=='A' || str=='a'){
           return true;
        }
    }*/
     return !str.empty() && (str[0]=='A' || str[0]=='a');
}
int CountStartsWithA(const vector<string>& xs) {
    // посчитайте число строк, начинающихся на букву A или a
    int kol_vo=count_if(xs.begin(),xs.end(),StartWithA);
    return kol_vo;
}

int main() {
    // не меняйте тело main
    cout << CountStartsWithA({"And"s, "another"s, "one"s, "gone"s, "another"s,
                              "one"s
                              "bites"s,
                              "the"s, "dust"s});

}