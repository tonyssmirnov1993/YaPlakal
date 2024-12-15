#include "log_duration.h"
 
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>
 
using namespace std;
 
vector<float> ComputeAvgTemp(const vector<vector<float>>& vs) {
    // место для вашего решения
    if (vs.empty()) return {};
    int n = vs[0].size();
    int m = vs.size();
    vector<float> result(n);
    vector<float> sum(n);
    vector<float> size(n);
    
    for (int i = 0; i < n; ++i) {
        sum = {};
        size = {};
        
        for (int j = 0; j < m; ++j) {
            sum[i] += (vs[j][i] > 0 ? vs[j][i] : 0);
            size[i] += (vs[j][i] > 0 ? 1 : 0);
        }
        result[i] += (size[i] > 0 ? sum[i] / size[i] : 0);
    }
    return result;
}
 
vector<float> GetRandomVector(int size) {
    static mt19937 engine;
    uniform_real_distribution<float> d(-100, 100);
 
    vector<float> res(size);
    for (int i = 0; i < size; ++i) {
        res[i] = d(engine);
    }
 
    return res;
}
 
int main() {
    vector<vector<float>> data;
    data.reserve(5000);
 
    for (int i = 0; i < 5000; ++i) {
        data.push_back(GetRandomVector(5000));
    }
 
    vector<float> avg;
    {
        LOG_DURATION("ComputeAvgTemp"s);
        avg = ComputeAvgTemp(data);
    }
 
    cout << "Total mean: "s << accumulate(avg.begin(), avg.end(), 0.f) / avg.size() << endl;
}