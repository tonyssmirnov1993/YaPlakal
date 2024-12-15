#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
 
#include "json.h"
 
using namespace std;
 
struct Spending {
    string category;
    int amount;
};
 
int CalculateTotalSpendings(const vector<Spending>& spendings) {
    return accumulate(
        spendings.begin(), spendings.end(), 0, [](int current, const Spending& spending){
            return current + spending.amount;
        });
}
 
string FindMostExpensiveCategory(const vector<Spending>& spendings) {
    assert(!spendings.empty());
    auto compare_by_amount = [](const Spending& lhs, const Spending& rhs) {
        return lhs.amount < rhs.amount;
    };
    return max_element(begin(spendings), end(spendings), compare_by_amount)->category;
}
 
vector<Spending> LoadFromJson(istream& input) {
    std::vector<Spending> result;
 
    auto nod = Load(input).GetRoot().AsArray();
 
    for (auto node : nod) {
        for (auto& [amount_, category_] : node.AsMap()) {
 
            Spending helper;
 
            if (category_.AsString().empty()) {
                continue;
            }
            helper.amount = category_.AsInt();
            helper.category = category_.AsString();
            result.push_back(move(helper));
        }
    }
    return result;
}
 
int main() {
    const vector<Spending> spendings = LoadFromJson(cin);
    cout << "Total "sv << CalculateTotalSpendings(spendings) << '\n';
    cout << "Most expensive is "sv << FindMostExpensiveCategory(spendings) << '\n';
}