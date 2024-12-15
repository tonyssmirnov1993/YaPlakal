#include <iostream>
#include <string>
 
using namespace std;
 
struct Circle {
    double x;
    double y;
    double r;
};
 
struct Dumbbell {
    Circle circle1;
    Circle circle2;
    string text;
};
 
struct DumbbellHash {
 
    size_t operator() (const Dumbbell& dumbbell) const {
 
        auto hash_1x = double_hash_(dumbbell.circle1.x);
        auto hash_1y = double_hash_(dumbbell.circle1.y);
        auto hash_1r = double_hash_(dumbbell.circle1.r);
 
        auto hash_1circle = hash_1x 
                            + hash_1y * 17 
                            + hash_1r * (17 * 17);
 
        auto hash_2x = double_hash_(dumbbell.circle2.x);
        auto hash_2y = double_hash_(dumbbell.circle2.y);
        auto hash_2r = double_hash_(dumbbell.circle2.r);
 
        auto hash_2circle = hash_2x 
                            + hash_2y * 17 
                            + hash_2r * (17 * 17);
 
        return (hash_1circle * (17 * 17 * 17) 
                + hash_2circle 
                + string_hash_(dumbbell.text));
    }
 
private:
    hash<string> string_hash_;
    hash<double> double_hash_;
};
 
int main() {
    DumbbellHash hash;
    Dumbbell dumbbell{{10, 11.5, 2.3}, {3.14, 15, -8}, "abc"s};
    cout << "Dumbbell hash "s << hash(dumbbell);
}