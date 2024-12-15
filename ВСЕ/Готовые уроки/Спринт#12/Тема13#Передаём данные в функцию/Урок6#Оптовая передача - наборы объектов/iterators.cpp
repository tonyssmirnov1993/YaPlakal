#include <iostream>
#include <list>
#include <set>
#include <string_view>
#include <vector>
 
using namespace std;
 
template <typename Iterator1, typename Iterator2>
void Merge(Iterator1 start_1, Iterator1 end_1,
           Iterator2 start_2, Iterator2 end_2,
           std::ostream& output) {
    
    Iterator1 iter1_begin = start_1;
    Iterator2 iter2_begin = start_2;
 
    while (iter1_begin != end_1 && iter2_begin != end_2) {
        
        if (std::less<>()(*iter1_begin, *iter2_begin)) {
            output << *(iter1_begin++) << std::endl;
        } else {
            output << *(iter2_begin++) << std::endl;
        }
    }
    
    while (iter1_begin != end_1) {
        output << *(iter1_begin++) << std::endl;
    }
    
    while (iter2_begin != end_2) {
        output << *(iter2_begin++) << std::endl;
    }
    
}
 
template <typename Container1,  typename Container2>
void MergeSomething(const Container1& container1, const Container2& container2, ostream& output) {
 
    Merge(container1.begin(), 
          container1.end(), 
          container2.begin(), 
          container2.end(), 
          output);
}
 
template <typename Data>
void MergeHalves(const vector<Data>& container, ostream& output) {
    size_t middl = container.size()/2 + 0.5;
    
    Merge(container.begin(), 
          container.begin() + middl, 
          container.begin() + middl, 
          container.end(), 
          output);
}
 
int main() {
    vector<int> v1{60, 70, 80, 90};
    vector<int> v2{65, 75, 85, 95};
    vector<int> combined{60, 70, 80, 90, 65, 75, 85, 95};
    list<double> my_list{0.1, 72.5, 82.11, 1e+30};
    string_view my_string = "ACNZ"sv;
    set<unsigned> my_set{20u, 77u, 81u};
 
    cout << "Merging vectors:"sv << endl;
    MergeSomething(v1, v2, cout);
 
    cout << "Merging vector and list:"sv << endl;
    MergeSomething(v1, my_list, cout);
 
    cout << "Merging string and list:"sv << endl;
    MergeSomething(my_string, my_list, cout);
 
    cout << "Merging set and vector:"sv << endl;
    MergeSomething(my_set, v2, cout);
 
    cout << "Merging vector halves:"sv << endl;
    MergeHalves(combined, cout);
}