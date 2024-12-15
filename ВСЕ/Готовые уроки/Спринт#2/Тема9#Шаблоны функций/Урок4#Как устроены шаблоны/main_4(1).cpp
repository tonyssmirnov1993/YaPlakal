#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

template <typename Documents, typename Term>

const vector<double> ComputeTfIdfs(const Documents& documents, const Term& term){
    int F = 0;
    vector<double> TF_IDF;
    for (const auto& document : documents) {
        if (count(document.begin(), document.end(), term)) {
            ++F;
        }
    }
    double IDF = log(documents.size()/ static_cast<double>(F));
    for (const auto& document : documents) {
        double TF = count(document.begin(), document.end(), term) / static_cast<double>(document.size());
        TF_IDF.push_back(TF*IDF);
        }
    return TF_IDF;
}

int main() {
    const vector<vector<string>> documents = {
        {"белый"s, "кот"s, "и"s, "модный"s, "ошейник"s},
        {"пушистый"s, "кот"s, "пушистый"s, "хвост"s},
        {"ухоженный"s, "пёс"s, "выразительные"s, "глаза"s},
    };
    const auto& tf_idfs = ComputeTfIdfs(documents, "кот"s);
    for (const double tf_idf : tf_idfs) {
        cout << tf_idf << " "s;
    }
    cout << endl;
    return 0;
}