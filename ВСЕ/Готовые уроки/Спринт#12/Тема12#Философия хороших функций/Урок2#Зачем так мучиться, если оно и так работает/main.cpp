#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
 
using namespace std;
 
enum class Gender {FEMALE, MALE};
 
struct Person {
    int age;           
    Gender gender;     
    bool is_employed;  
};
 
struct Stats {
    int people;
    int females;
    int males;
    int employed_females;
    int not_employed_females;
    int employed_males;
    int not_employed_males;
};
 
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
 
    if (range_begin == range_end) {
        return 0;
    }
    
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = range_copy.begin() + range_copy.size() / 2;
    nth_element(range_copy.begin(), middle, range_copy.end(), [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
    });
    
    return middle->age;
}
 
Stats PrintStats(vector<Person>& people_) {
    
    auto males_it = std::partition(begin(people_), end(people_),
                                [](const Person& person) {return person.gender == Gender::MALE;});
                         
    auto employed_males_it = std::partition(begin(people_), males_it,
                                         [](const Person& person) {return person.is_employed;});
                                    
    auto employed_females_it = std::partition(males_it, end(people_),
                                           [](const Person& person) {return person.is_employed;});
 
    std::cout  << "Median age = "
               << ComputeMedianAge(begin(people_), end(people_)) << std::endl
               
               << "Median age for females = "
               << ComputeMedianAge(males_it, end(people_)) << std::endl
               
               << "Median age for males = "
               << ComputeMedianAge(begin(people_), males_it) << std::endl
               
               << "Median age for employed females = "
               << ComputeMedianAge(males_it,  employed_females_it) << std::endl
               
               << "Median age for unemployed females = "
               << ComputeMedianAge(employed_females_it, end(people_)) << std::endl
               
               << "Median age for employed males = "
               << ComputeMedianAge(begin(people_), employed_males_it) << std::endl
               
               << "Median age for unemployed males = "
               << ComputeMedianAge(employed_males_it, males_it) << std::endl;
 
    return {
        ComputeMedianAge(begin(people_), end(people_)),
        ComputeMedianAge(males_it, end(people_)),
        ComputeMedianAge(begin(people_), males_it),
        ComputeMedianAge(males_it,  employed_females_it),
        ComputeMedianAge(employed_females_it, end(people_)),
        ComputeMedianAge(begin(people_), employed_males_it),
        ComputeMedianAge(employed_males_it, males_it)
    };
}
 
int main() {
    vector<Person> persons = {
        {31, Gender::MALE, false},   {40, Gender::FEMALE, true},  {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},  {80, Gender::FEMALE, false}, {78, Gender::MALE, false},
        {10, Gender::FEMALE, false}, {55, Gender::MALE, true},
    };
    PrintStats(persons);
}