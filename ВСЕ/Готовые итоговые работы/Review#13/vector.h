#pragma once
#include <cassert>
#include <utility>
#include <memory>
#include <type_traits>


template <typename T>
class RawMemory {
public:
    RawMemory() = default;

    explicit RawMemory(size_t capacity) : buffer_(Allocate(capacity)),
        capacity_(capacity) {
    }

    RawMemory(const RawMemory&) = delete;
    RawMemory& operator=(const RawMemory& rhs) = delete;

    RawMemory(RawMemory&& other) noexcept : buffer_(std::exchange(other.buffer_, nullptr)),
        capacity_(std::exchange(other.capacity_, 0))
    {
    }

    RawMemory& operator=(RawMemory&& rhs) noexcept {
        if (this != &rhs) {
            Swap(rhs);
        }
        return *this;
    }
    ~RawMemory() {
        Deallocate(buffer_);
    }

    T* operator+(size_t offset) noexcept {
        // Разрешается получать адрес ячейки памяти, следующей за последним элементом массива
        assert(offset <= capacity_);
        return buffer_ + offset;
    }

    const T* operator+(size_t offset) const noexcept {
        return const_cast<RawMemory&>(*this) + offset;
    }

    const T& operator[](size_t index) const noexcept {
        return const_cast<RawMemory&>(*this)[index];
    }

    T& operator[](size_t index) noexcept {
        assert(index < capacity_);
        return buffer_[index];
    }

    void Swap(RawMemory& other) noexcept {
        std::swap(buffer_, other.buffer_);
        std::swap(capacity_, other.capacity_);
    }

    const T* GetAddress() const noexcept {
        return buffer_;
    }

    T* GetAddress() noexcept {
        return buffer_;
    }

    size_t Capacity() const {
        return capacity_;
    }

private:
    // Выделяет сырую память под n элементов и возвращает указатель на неё
    static T* Allocate(size_t n) {
        return n != 0 ? static_cast<T*>(operator new(n * sizeof(T))) : nullptr;
    }

    // Освобождает сырую память, выделенную ранее по адресу buf при помощи Allocate
    static void Deallocate(T* buf) noexcept {
        operator delete(buf);
    }

    T* buffer_ = nullptr;
    size_t capacity_ = 0;
};


template <typename T>
class Vector {
public:

    Vector() = default;

    explicit Vector(size_t size) : data_(size), size_(size) {
        std::uninitialized_value_construct_n(data_.GetAddress(), size);
    }

    Vector(const Vector& other) : data_(other.size_), size_(other.size_) {
        std::uninitialized_copy_n(other.data_.GetAddress(), size_, data_.GetAddress());
    }
    Vector(Vector&& other) noexcept : data_(std::move(other.data_)),
        size_(std::exchange(other.size_, 0))
    {
    }

    Vector& operator=(const Vector& other) {
        if(this != &other){
            if (other.size_ > data_.Capacity()) {
                Vector other_copy(other);
                Swap(other_copy);
            }
            else {
                CopyVector(other);
            }
        }
        return *this;
    }

    Vector& operator=(Vector&& rhs) noexcept {
        if (this != &rhs) {
            Swap(rhs);
        }
        return *this;
    }

    ~Vector() {
        std::destroy_n(data_.GetAddress(), size_);
    }

    void Resize(size_t new_size) {
        if (new_size < size_) {
            std::destroy_n(data_.GetAddress() + new_size, size_ - new_size);
            size_ = new_size;
        }
        else {
            Reserve(new_size);
            std::uninitialized_value_construct_n(data_.GetAddress() + size_, new_size - size_);
            size_ = new_size;
        }
    }


    void PushBack(const T& value) {
        EmplaceBack(std::forward<const T&>(value));
    }

    void PushBack(T&& value) {
        EmplaceBack(std::forward<T&&>(value));
    }

    template <typename... Args>
    T& EmplaceBack(Args&&... args) {
        T* result = nullptr;

        if (size_ == Capacity()) {
            RawMemory<T> new_data(size_ == 0 ? 1 : size_ * 2);
            result = new (new_data + size_) T(std::forward<Args>(args)...);

            if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
                std::uninitialized_move_n(data_.GetAddress(), size_, new_data.GetAddress());
            }
            else {
                try {
                    std::uninitialized_copy_n(data_.GetAddress(), size_, new_data.GetAddress());
                }
                catch (...) {
                    std::destroy_n(new_data.GetAddress() + size_, 1);
                    throw;
                }
            }
            std::destroy_n(data_.GetAddress(), size_);
            data_.Swap(new_data);
        }
        else {
            result = new (data_ + size_) T(std::forward<Args>(args)...);
        }
        ++size_;
        return *result;
    }
    void PopBack() {
        if (size_ > 0) {
            std::destroy_n(data_.GetAddress() + size_ - 1, 1);
            --size_;
        } 
    }

    void Swap(Vector& other) noexcept {
        data_.Swap(other.data_);
        std::swap(size_, other.size_);

    }
    size_t Size() const noexcept {
        return size_;
    }

    size_t Capacity() const noexcept {
        return data_.Capacity();
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity <= data_.Capacity()) {
            return;
        }
        RawMemory<T> new_data(new_capacity);

        if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
            std::uninitialized_move_n(data_.GetAddress(), size_, new_data.GetAddress());
        }
        else {
            std::uninitialized_copy_n(data_.GetAddress(), size_, new_data.GetAddress());
        }

        std::destroy_n(data_.GetAddress(), size_);
        data_.Swap(new_data);
    }


    const T& operator[](size_t index) const noexcept {
        return const_cast<Vector&>(*this)[index];
    }

    T& operator[](size_t index) noexcept {
        assert(index < size_);
        return data_[index];
    }

    using iterator = T*;
    using const_iterator = const T*;

    iterator begin() noexcept {
        return data_.GetAddress();
    };

    iterator end() noexcept {
        return data_.GetAddress() + size_;
    };

    const_iterator begin() const noexcept {
        return data_.GetAddress();
    };

    const_iterator end() const noexcept {
        return data_.GetAddress() + size_;
    };

    const_iterator cbegin() const noexcept {
        return begin();
    };
    const_iterator cend() const noexcept {

        return end();
    };

    template <typename... Args>
    iterator Emplace(const_iterator pos, Args&&... args) {
        assert(pos >= begin() && pos <= end());
        iterator result = nullptr;
        size_t shift = pos - begin();

        if (size_ == Capacity()) {
            RawMemory<T> new_data(size_ == 0 ? 1 : size_ * 2);
            result = new (new_data + shift) T(std::forward<Args>(args)...);
            if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
                std::uninitialized_move_n(begin(), shift, new_data.GetAddress());
                std::uninitialized_move_n(begin() + shift, size_ - shift, new_data.GetAddress() + shift + 1);
            }
            else {
                try {
                    std::uninitialized_copy_n(begin(), shift, new_data.GetAddress());
                    std::uninitialized_copy_n(begin() + shift, size_ - shift, new_data.GetAddress() + shift + 1);
                }
                catch (...) {
                    std::destroy_n(new_data.GetAddress() + shift, 1);
                    throw;
                }
            }
            std::destroy_n(begin(), size_);
            data_.Swap(new_data);
        }
        else {
            if (size_ != 0) {
                new (data_ + size_) T(std::move(*(end() - 1)));
                try {
                    std::move_backward(begin() + shift, end(), end() + 1);
                }
                catch (...) {
                    std::destroy_n(end(), 1);
                    throw;
                }
                std::destroy_at(begin() + shift);
            }
            result = new (data_ + shift) T(std::forward<Args>(args)...);
        }
        ++size_;
        return result;
    }


    iterator Insert(const_iterator pos, const T& value) {
        return Emplace(pos, value);
    };

    iterator Insert(const_iterator pos, T&& value) {
        return Emplace(pos, std::move(value));
    };

    iterator Erase(const_iterator pos) {
        assert(pos >= begin() && pos < begin() + size_);
        auto index_pos = pos - cbegin();
        std::move(data_.GetAddress() + index_pos+1, end(), data_.GetAddress()+index_pos);
        std::destroy_n(end() - 1, 1);
        --size_;
        return data_.GetAddress() + index_pos;
    };
private:
    void CopyVector(const Vector& other) {
        std::copy(other.begin(), other.begin() + std::min(other.size_, size_), begin());
        if (other.size_ <= size_) {
            std::destroy_n(data_.GetAddress() + other.size_, size_ - other.size_);
        }
        else {
            std::uninitialized_copy_n(other.data_.GetAddress() + size_, other.size_ - size_, data_.GetAddress() + size_);
        }
        size_ = other.size_;
    }
    static void CopyConstruct(T* buf, const T& elem) {
        new (buf) T(elem);
    }

    RawMemory<T> data_;
    size_t size_ = 0;
};