#include <cmath>
#include <numeric>

using namespace std;

class Rational {
public:
    Rational() = default; 
    //с одним пар-ром
    Rational(int a) {
        numerator_ = a;
        denominator_ = 1;
    }
    //с двумя пар-рами
    Rational(int a, int b) {
        numerator_ = a / gcd(a,b);   //сокращение числителя делением на НОД
        denominator_ = b / gcd(a,b); //сокращение знаменателя делением на НОД
        //меняем знаки
        if (denominator_ < 0 && numerator_ < 0) {
            denominator_ = -denominator_;
            numerator_ = -numerator_;
        }
    }
    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};