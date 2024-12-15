#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> month_lengths = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//подогнали нумерацию с 1
    vector<string> month_names={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; 
    int month_index;
    cin >> month_index; // считайте номер месяца
    if (month_index>=1 && month_index<=12) {
        cout << "There are "s << month_lengths[month_index] << " days in "s << month_names[month_index-1] << endl;// и выведите количество дней в нём
    }
    else {
        cout << "Incorrect month"s << endl;
    }		
}