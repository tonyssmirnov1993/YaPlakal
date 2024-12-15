#include "libstat.h" 

#include <iostream>
using namespace std;
 
int main() {
    setlocale(LC_ALL,"RUS");
    statistics::tests::AggregSum();
    statistics::tests::AggregMax();
    statistics::tests::AggregMean();
    statistics::tests::AggregStandardDeviation();
    statistics::tests::AggregMode();
    statistics::tests::AggregPrinter();
    cout << "Тест пройден!"sv << endl;
}