#include <cassert>
#include <vector>
#include <algorithm>
 
template <typename T>
void ReverseArray(T* start, size_t size) {
    // Напишите тело функции самостоятельно
    //auto end = new T[size];
    
    int j = size-1, i = 0;
    while (i < j){
        auto temp = *(start + i);
        *(start + i) = *(start + j);
        *(start + j) = temp;
        i++; j--;
    }
}
 
int main() {
    using namespace std;
    
    vector<int> v = {1, 2};
    ReverseArray(v.data(), v.size());
    assert(v == (vector<int>{2, 1}));
}