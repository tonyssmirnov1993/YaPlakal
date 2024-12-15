#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int CountAndAddNewDogs(const vector<string>& new_dogs, const map<string, int>& max_amount,
                       map<string, int>& shelter) {
    return count_if(new_dogs.begin(), new_dogs.end(), [&max_amount, &shelter](const string& poroda) {
            //объявляем и инициализируем ссылку на количество собак в приюте нужной породы
            int& current_amount = shelter[poroda];
            //текущее количество собак данной породы меньше максимальной вместимости этой породы в приюте
            if (current_amount < max_amount.at(poroda)) {
                ++current_amount; // увеличиваем количество собак этой породы  
                return true;//эта собака добавлена
            } else {    
                return false; //не добавляем эту собаку
            }
        });
}

int main() {
    map<string, int> shelter {
        {"shepard"s, 1},
        {"corgie"s, 3},
    };

    map<string, int> max_amount {
        {"shepard"s, 2},
        {"corgie"s, 3},
        {"shiba inu"s, 1},
    };

    cout << CountAndAddNewDogs({"shepard"s, "shiba inu"s, "shiba inu"s, "corgie"s}, max_amount, shelter) << endl;
}