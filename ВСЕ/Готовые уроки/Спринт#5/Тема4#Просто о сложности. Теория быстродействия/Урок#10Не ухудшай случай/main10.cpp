#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>
 
using namespace std;
 
int EffectiveCount(const vector<int>& v, int n, int i) {
    int limit = static_cast<int64_t>(v.size())*(i + 1)/(n + 1);
    if (limit < log2(v.size())) { // хороший случай
        cout << "Using find_if\n"s;
        auto predicat = [i](int limit) { return limit > i; };
        auto it = find_if(v.begin(), v.end(), predicat);
        return it - v.begin();
    } else { // нехороший случай
        cout << "Using upper_bound\n"s;
        auto it = upper_bound(v.begin(), v.end(), i);
        return it - v.begin();
    }
}
 
int main() {
    static const int NUMBERS = 1'000'000;
    static const int MAX = 1'000'000'000;
 
    mt19937 r;
    uniform_int_distribution<int> uniform_dist(0, MAX);
 
    vector<int> nums;
    for (int i = 0; i < NUMBERS; ++i) {
        int random_number = uniform_dist(r);
        nums.push_back(random_number);
    }
    sort(nums.begin(), nums.end());
 
    int i;
    cin >> i;
    int result = EffectiveCount(nums, MAX, i);
    cout << "Total numbers before "s << i << ": "s << result << endl;
}