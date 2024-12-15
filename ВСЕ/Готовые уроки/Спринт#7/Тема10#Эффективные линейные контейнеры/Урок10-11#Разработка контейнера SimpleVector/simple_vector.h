#pragma once

#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <utility>

#include "array_ptr.h"

class ReserveProxyObj {
public:
    ReserveProxyObj(const size_t capacity_to_reserve) 
    :reverse_assistant_(capacity_to_reserve)
    {
    }
 
    size_t GetSize() { 
        return reverse_assistant_; 
    }
    
private:
    size_t reverse_assistant_;
    
};
 
ReserveProxyObj Reserve(const size_t capacity_to_reserve) {
    return ReserveProxyObj(capacity_to_reserve);
}

template <typename Type>
class SimpleVector {
public:
    using Iterator = Type*;
    using ConstIterator = const Type*;

    SimpleVector() noexcept = default;
 
    SimpleVector(ReserveProxyObj obj) {
        SimpleVector<Type> vec;
        vec.Reserve(obj.GetSize());
        swap(vec);
    }
    
    // Создаёт вектор из size элементов, инициализированных значением по умолчанию
    explicit SimpleVector(size_t size)
        : SimpleVector(size, Type{})
    {
    }

    // Создаёт вектор из size элементов, инициализированных значением value
    SimpleVector(size_t size, const Type& value)
        : items_(size)
        , size_(size)
        , capacity_(size)
    {
        std::fill(items_.Get(), items_.Get() + size_, value);
    }

    // Создаёт вектор из std::initializer_list
    SimpleVector(std::initializer_list<Type> init)
        : items_(init.size())
        , size_(init.size())
        , capacity_(init.size())
    {
        ConstructorAssistant(init);
    }
    
    SimpleVector(const SimpleVector& other)
        : items_(other.size_)
        , size_(other.size_)
        , capacity_(other.size_)
    {
        ConstructorAssistant(other);
    }
    
    SimpleVector(SimpleVector&& other)
    {
        items_ = std::move(other.items_);
		size_ = std::exchange(other.size_, 0);
		capacity_ = std::exchange(other.capacity_, 0);
    }

    SimpleVector& operator=(const SimpleVector& rhs) {
        if (this != &rhs) {
            if (rhs.IsEmpty()) {
                Clear();
                return *this;
            }
            SimpleVector<Type> arr_ptr(rhs.size_);
            std::copy(rhs.begin(), rhs.end(), arr_ptr.begin());
            arr_ptr.capacity_ = rhs.capacity_;
            swap(arr_ptr);
        }
        return *this;
    }
    
    SimpleVector& operator=(SimpleVector&& rhs) {
        if (this != &rhs) {
            if (rhs.IsEmpty()) {
                Clear();
                return *this;
            }
            SimpleVector<Type> arr_ptr(rhs.size_);
            std::copy(rhs.begin(), rhs.end(), arr_ptr.begin());
            arr_ptr.capacity_ = rhs.capacity_;
            swap(arr_ptr);
        }
        return *this;
    }
    
    void Reserve(size_t capacity_to_reserve) {
        if (capacity_to_reserve > capacity_) {
            SimpleVector<Type> tmp_items(capacity_to_reserve);
            std::copy(cbegin(), cend(), tmp_items.begin());
            tmp_items.size_ = size_;
            swap(tmp_items);
        }
    }
    
    template <typename Container>
    void ConstructorAssistant(Container& other) {
        std::copy(other.begin(), other.end(), items_.Get());
    }

    // Возвращает количество элементов в массиве
    size_t GetSize() const noexcept {
        return size_;
    }

    // Возвращает вместимость массива
    size_t GetCapacity() const noexcept {
        return capacity_;
    }

    // Сообщает, пустой ли массив
    bool IsEmpty() const noexcept {
        return size_ == 0;
    }

    // Возвращает ссылку на элемент с индексом index
    Type& operator[](size_t index) noexcept {
        assert(index <= capacity_);
        return items_[index];
    }

    // Возвращает константную ссылку на элемент с индексом index
    const Type& operator[](size_t index) const noexcept {
        assert(index <= capacity_);
        return items_[index];
    }

    // Возвращает константную ссылку на элемент с индексом index
    // Выбрасывает исключение std::out_of_range, если index >= size
    Type& At(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Работа не со соей памятью"); 
        }
        return items_[index];
    }

    // Возвращает константную ссылку на элемент с индексом index
    // Выбрасывает исключение std::out_of_range, если index >= size
    const Type& At(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Работа не со соей памятью");
        }
        return items_[index];
    }

    // Обнуляет размер массива, не изменяя его вместимость
    void Clear() noexcept {
        size_ = 0;
    }

    // Изменяет размер массива.
    // При увеличении размера новые элементы получают значение по умолчанию для типа Type
    void Resize(size_t new_size) {                                                             
        if (new_size == size_) return;
        
        if (new_size < size_) {
            for (auto it = &items_[new_size]; it != &items_[size_]; ++it) {
                *(it) = std::move(Type{});
            }
        }
        
        if (new_size > capacity_) {
            auto new_capacity = std::max(new_size, 2 * capacity_);
            ArrayPtr<Type> arr_ptr(new_capacity);
            std::move(&items_[0], &items_[size_], &arr_ptr[0]);
            for (auto it = &arr_ptr[size_]; it != &arr_ptr[new_size]; ++it) {
                *(it) = std::move(Type{});
            }
            items_.swap(arr_ptr);
            capacity_ = new_capacity;
        }
        
        size_ = new_size;
    }

    // Возвращает итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    Iterator begin() noexcept {
        return Iterator{items_.Get()};
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    Iterator end() noexcept {
        return Iterator{&items_[size_]};
    }

    // Возвращает константный итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator begin() const noexcept {
        return ConstIterator{items_.Get()};
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator end() const noexcept {
        return ConstIterator{&items_[size_]};
    }

    // Возвращает константный итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator cbegin() const noexcept {
        return ConstIterator{items_.Get()};
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator cend() const noexcept {
        return ConstIterator{&items_[size_]};
    }
    
    // Добавляет элемент в конец вектора
    // При нехватке места увеличивает вдвое вместимость вектора
    void PushBack(const Type& item) {
        if (size_ < capacity_) {
            items_[size_] = item;
        } else {
            auto new_capacity = std::max(size_t(1), 2 * capacity_); //защита, если capacity_=0
            ArrayPtr<Type> arr_ptr(new_capacity);
            std::copy(&items_[0], &items_[size_], &arr_ptr[0]);
            arr_ptr[size_] = item;
            items_.swap(arr_ptr);
            capacity_ = new_capacity;
        }
        ++size_;
    }
    
    void PushBack(Type&& item) {
        if (size_ < capacity_) {
            items_[size_] = std::move(item);
        } else {
            auto new_capacity = std::max(size_t(1), 2 * capacity_); //защита, если capacity_=0
            ArrayPtr<Type> arr_ptr(new_capacity);
            std::move(&items_[0], &items_[size_], &arr_ptr[0]);
            arr_ptr[size_] = std::move(item);
            items_.swap(arr_ptr);
            capacity_ = new_capacity;
        }
        ++size_;
    }

    // Вставляет значение value в позицию pos.
    // Возвращает итератор на вставленное значение
    // Если перед вставкой значения вектор был заполнен полностью,
    // вместимость вектора должна увеличиться вдвое, а для вектора вместимостью 0 стать равной 1
    Iterator Insert(ConstIterator pos, const Type& value) {
        assert(pos >= cbegin() && pos <= cend());
        
        auto pos_element = std::distance(cbegin(), pos);
        
        if (size_ < capacity_) {
            std::copy_backward(pos, cend(), &items_[(size_ + 1)]);
            items_[pos_element] = value;
        } else {
            auto new_capacity = std::max(size_t(1), 2 * capacity_); //защита, если capacity_=0
            ArrayPtr<Type> arr_ptr(new_capacity);
            std::copy(&items_[0], &items_[pos_element], &arr_ptr[0]);
            std::copy_backward(pos, cend(), &arr_ptr[(size_ + 1)]);
            arr_ptr[pos_element] = value;
            items_.swap(arr_ptr);
            capacity_ = new_capacity;
        }
        
        ++size_;
        return Iterator{&items_[pos_element]};
    }
    
    Iterator Insert(ConstIterator pos, Type&& value) {
        assert(pos >= cbegin() && pos <= cend());
        
        auto no_const_pos = const_cast<Iterator>(pos);
        auto pos_element = std::distance(begin(), no_const_pos);
        
        if (size_ < capacity_) {
            std::move_backward(no_const_pos, end(), &items_[(size_ + 1)]);
            items_[pos_element] = std::move(value);
        } else {
            auto new_capacity = std::max(size_t(1), 2 * capacity_); //защита, если capacity_=0
            ArrayPtr<Type> arr_ptr(new_capacity);
            std::move(&items_[0], &items_[pos_element], &arr_ptr[0]);
            std::move_backward(no_const_pos, end(), &arr_ptr[(size_ + 1)]);
            arr_ptr[pos_element] = std::move(value);
            items_.swap(arr_ptr);
            capacity_ = new_capacity;
        }
        
        ++size_;
        return Iterator{&items_[pos_element]};
    }

    // "Удаляет" последний элемент вектора. Вектор не должен быть пустым
    void PopBack() noexcept {
        assert(!IsEmpty());
        --size_;  
    }

    // Удаляет элемент вектора в указанной позиции
    Iterator Erase(ConstIterator pos) {
        assert(pos >= cbegin() && pos < cend());
        auto no_const_pos = const_cast<Iterator>(pos);
        auto pos_element = std::distance(begin(), no_const_pos);
        std::move(++no_const_pos, end(), &items_[pos_element]);
        --size_;
        return &items_[pos_element];
    }

    // Обменивает значение с другим вектором
    void swap(SimpleVector& other) noexcept {
        items_.swap(other.items_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
    
private:
    ArrayPtr<Type> items_;

    size_t size_ = 0;
    size_t capacity_ = 0;
    
};

template <typename Type>
inline bool operator==(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    if (lhs.GetSize() != rhs.GetSize()) return false;
    return std::equal(lhs.begin(),lhs.end(),rhs.begin());
}

template <typename Type>
inline bool operator!=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(lhs == rhs);
}

template <typename Type>
inline bool operator<(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
inline bool operator<=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(rhs < lhs);
}

template <typename Type>
inline bool operator>(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return rhs < lhs;
}

template <typename Type>
inline bool operator>=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(rhs > lhs);
}