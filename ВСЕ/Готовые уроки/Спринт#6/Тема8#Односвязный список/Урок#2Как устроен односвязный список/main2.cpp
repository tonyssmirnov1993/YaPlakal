#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
 
template <typename Type>
class SingleLinkedList {
    // Узел списка
    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }
        Type value;
        Node* next_node = nullptr;
    };
 
public:
    SingleLinkedList() {
    }
    
    // Возвращает количество элементов в списке за время O(1)
    [[nodiscard]] size_t GetSize() const noexcept {
        // Заглушка. Реализуйте метод самостоятельно
        return size_;
        //assert(false);
        //return 42;
    }
 
    // Сообщает, пустой ли список за время O(1)
    [[nodiscard]] bool IsEmpty() const noexcept {
        // Заглушка. Реализуйте метод самостоятельно
        if (size_ != 0) {
        return false;
        }
        return true;
    }
 
private:
    // Фиктивный узел, используется для вставки "перед первым элементом"
    Node head_;
    size_t size_ = 0;
};
 
void Test0() {
    using namespace std;
    {
        const SingleLinkedList<int> empty_int_list;
        assert(empty_int_list.GetSize() == 0u);
        assert(empty_int_list.IsEmpty());
    }
 
    {
        const SingleLinkedList<string> empty_string_list;
        assert(empty_string_list.GetSize() == 0u);
        assert(empty_string_list.IsEmpty());
    }
}
 
int main() {
    Test0();
}