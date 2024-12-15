#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename Type>
class Stack {
public:
    void Push(const Type& element) {
        elements_.push_back(element);
    }
    //============
    void Pop() {
        elements_.pop_back();
    }
    //==========
    const Type& Peek() const {
        return elements_.back();
    }
    //============
    Type& Peek() {
        return elements_.back();
    }
    //===========
    void Print() const {
        PrintRange(elements_.begin(), elements_.end());
    }
    //=========
    uint64_t Size() const {
        return elements_.size();
    }
    //==========
    bool IsEmpty() const {
        return elements_.empty();
    }

private:
    vector<Type> elements_;
};
template <typename Type>
class StackMin {
public:
    void Push(const Type& element) {       
        elements_.Push(element);     
        min_elements_[element].push_back(elements_.Peek());
    }
    //========
    void Pop() {
        auto elem = elements_.Peek();
        min_elements_[elem].pop_back();
        if (min_elements_[elem].size() == 0) {
            min_elements_.erase(elem);
        }
        elements_.Pop();      
    }
   //========
   const Type& Peek() const {
        return elements_.Peek();
    }
    //=========
    Type& Peek() {
        return elements_.Peek();
    }
    //=========
    void Print() const {
        elements_.Print();
    }
    //==========
    uint64_t Size() const {
        return elements_.size();
    }
    //===========
    bool IsEmpty() const {
        return elements_.IsEmpty();
    }
   //=========
   const Type& PeekMin() const {   
        const auto  min = *min_elements_.begin();
        return min_elements_.at(min.first).front();
    }
    //============
    Type& PeekMin() {
        const auto min = * min_elements_.begin();
        return min_elements_[min.first].front();
    }
 
private:
   Stack<Type> elements_;
   map<Type, vector <Type>> min_elements_;
};

int main() {
    setlocale(LC_ALL, "");
    StackMin<int> stack;
    vector<int> values(15);
    iota(values.begin(), values.end(), 1); // заполняем вектор для тестирования нашего стека
    random_shuffle(values.begin(), values.end());  // перемешиваем значения
    for (int i = 0; i < 15; ++i) { // заполняем стек
        stack.Push(values[i]);
    }
    while (!stack.IsEmpty()) {// печатаем стек и его минимум, постепенно убирая из стека элементы
        stack.Print();
        cout << "Минимум = "s << stack.PeekMin() << endl;
        stack.Pop();
    }
}