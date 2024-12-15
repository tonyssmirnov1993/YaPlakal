#include <iostream>
#include <vector>

using namespace std;

int main() {
		vector<int> month_lengths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int c;
    cin >> c; // считайте номер месяца
    if (c>=0 && c<=11) {
        cout << month_lengths[c] << endl;// и выведите количество дней в нём
    }
    else {
        cout << "Incorrect input"s << endl;
    }		
}