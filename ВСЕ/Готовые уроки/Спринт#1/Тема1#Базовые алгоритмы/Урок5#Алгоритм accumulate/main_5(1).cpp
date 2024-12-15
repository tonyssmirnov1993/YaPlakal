#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

double Average(const vector<int>& xs) {   
    // суммирование начните с 0.0 - тогда результат выражения будет вещественным числом
    if (!xs.empty()){
        return accumulate(xs.begin(), xs.end(),0.0)/xs.size();// посчитайте среднее арифметическое: поделите сумму на размер
    }
    return 0;
}

int main() {
    // не меняйте код main
    cout << Average({1, 2, 2}) << endl;
    return 0;
}