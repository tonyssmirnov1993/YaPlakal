#include <iostream>
#include <numeric>

using namespace std;

class Rational {
public:
    Rational() = default;

    Rational(int value)
        : numerator_(value)
        , denominator_(1) {
    }

    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator)
    {
        Normalize();
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }
                    //---===ÏÅĞÅÃĞÓÇ ÑÓÌÌÀ Ñ ÏĞÈÑÂÀÈÂÀÍÈÅÌ===---
    Rational operator += (Rational right) {
        numerator_      = numerator_ * right.denominator_ + right.numerator_ * denominator_;
        denominator_   *= right.denominator_;
        Normalize();
        return *this;
    }
                    //---===ÏÅĞÅÃĞÓÇ ĞÀÇÍÎÑÒÜ Ñ ÏĞÈÑÂÀÈÂÀÍÈÅÌ===---
    Rational operator -= (Rational right) {
        numerator_      = numerator_ * right.denominator_ - right.numerator_ * denominator_;
        denominator_    *= right.denominator_;
        Normalize();
        return *this;
    }
                    //---===ÏÅĞÅÃĞÓÇ ÓÌÍÎÆÅÍÈÅ Ñ ÏĞÈÑÂÀÈÂÀÍÈÅÌ===---
    Rational operator *= (Rational right) {
        numerator_     *= right.numerator_;
        denominator_   *= right.denominator_;
        Normalize();
        return *this;
    }
                    //---===ÏÅĞÅÃĞÓÇ ÄÅËÅÍÈÅ Ñ ÏĞÈÑÂÀÈÂÀÍÈÅÌ===---
    Rational operator /= (Rational right) {
        numerator_     *= right.denominator_;
        denominator_   *= right.numerator_;
        Normalize();
        return *this;
    }

private:
    void Normalize() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        int n = gcd(numerator_, denominator_);//ïîèñê ÍÎÄ ñ ïîñëåäóşùèì ñîêğàùåíèåì
        numerator_ /= n;
        denominator_ /= n;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

                        //---===ÂÛÂÎÄ===---
ostream& operator<<(ostream& output, Rational rational) {
    return output << rational.Numerator() << '/' << rational.Denominator();
}
                         //---===ÂÂÎÄ===---
istream& operator>>(istream& input, Rational& rational) {
    int numerator;
    int denominator;
    char slash;
    if ((input >> numerator) && (input >> slash) && (slash == '/') && (input >> denominator)) {
        rational = Rational{ numerator, denominator };
    }
    return input;
}

                        //ÓÍÀĞÍÎÅ ÑËÎÆÅÍÈÅ
Rational operator + (Rational value) {
    return value;
}
                        //ÓÍÀĞÍÎÅ ÂÛ×ÈÒÀÍÈÅ
Rational operator - (Rational value) {
    return { -value.Numerator(), value.Denominator() };
}
                        //ÑËÎÆÅÍÈÅ
Rational operator + (Rational left, Rational right) {
    return left += right;
}
                         //ÂÛ×ÈÒÀÍÈÅ
Rational operator - (Rational left, Rational right) {
    return left -= right;
}
                        //ÓÌÍÎÆÅÍÈÅ
Rational operator * (Rational left, Rational right) {
    return left *= right;
}
                        //ÄÅËÅÍÈÅ
Rational operator / (Rational left, Rational right) {
    return left /= right;
}

int main() {
    Rational minus_r1(2, 4);
    Rational minus_r2(3, 4);
    minus_r1 -= minus_r2;
    cout << minus_r1 << endl; // -1/4
}