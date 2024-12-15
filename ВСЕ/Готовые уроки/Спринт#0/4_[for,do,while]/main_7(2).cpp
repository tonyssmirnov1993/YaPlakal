#include <iostream>
using namespace std;

int main() {
    int bill;
    int sum = 0;

    do {
        cin >> bill; 
        if (bill > 0) {// подобное сочетание if и continue позволяет игнорировать ненужный случай
             cout << "Income: " << bill << endl;
            sum += bill;
        }
    } while (bill != 0);// признаком конца программы будет счёт ноль
    cout << "Total income: " << sum << endl;
}