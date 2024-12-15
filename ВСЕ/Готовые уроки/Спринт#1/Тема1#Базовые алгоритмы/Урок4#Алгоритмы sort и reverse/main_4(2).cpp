#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

pair<bool, double> CalcMedian(vector<double> samples) {
    if (!samples.empty()) {// то есть вектор непустой,
        auto temp = samples;
        auto sr = samples.size()/2;
        sort(temp.begin(), temp.end());
            if (samples.size()%2 != 0) {
                return {true, temp[sr]};// верните {true, медиана}, если она существует,
            }
            return {true, (temp[sr - 1] + temp[sr])/2};
        }
    else { 
        return { false, 0.0 } ;// иначе - {false, 0}
    }
}

int main() {
    int size;
    cin >> size;

    vector<double> samples;
    for (int i = 0; i < size; ++i) {
        double sample;
        cin >> sample;
        samples.push_back(sample);
    }

    pair<bool, double> result = CalcMedian(samples);
    if (result.first) {
        cout << result.second << endl;
    } else {
        cout << "Empty vector"s << endl;
    }
}