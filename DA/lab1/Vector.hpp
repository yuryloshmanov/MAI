#ifndef Vector_hpp
#define Vector_hpp


template <class T>
class Vector {
    T* data_;
    size_t capacity_;
    size_t size_;

public:
    Vector();
    explicit Vector(size_t n);
    ~Vector();

    auto operator[](size_t index) -> T&;
    auto operator[](size_t index) const -> T;
    auto operator=(const Vector<T>& rhs) -> Vector<T>&;

    auto size() const -> size_t;
    auto pushBack(const T& value) -> void;

    auto begin() -> T*;
    auto end() -> T*;
};


template <class T>
Vector<T>::Vector(): data_(new T[100]), capacity_(100), size_(0) {}


template <class T>
Vector<T>::Vector(size_t n): data_(new T[static_cast<size_t>(n * 1.5)]()),
capacity_(static_cast<size_t>(n * 1.5)), size_(n) {}


template <class T>
Vector<T>::~Vector() {
    delete[] data_;
}


template <class T>
auto Vector<T>::operator[](size_t index) -> T& {
    return data_[index];
}


template <class T>
auto Vector<T>::operator[](size_t index) const -> T {
    return data_[index];
}


template <class T>
auto Vector<T>::operator=(const Vector<T>& rhs) -> Vector<T>& {
    if (&rhs != this) {
        capacity_ = rhs.capacity_;
        size_ = rhs.size_;
        T* newData = new T[capacity_];
        for (size_t i = 0; i < size(); i++) {
            newData[i] = rhs.data_[i];
        }

        auto tmp = data_;
        data_ = newData;
        delete[] tmp;
    }
    return *this;
}


template <class T>
auto Vector<T>::size() const -> size_t {
    return size_;
}


template <class T>
auto Vector<T>::pushBack(const T& value) -> void {
    if (size_ == capacity_) {
        capacity_ = static_cast<size_t>(capacity_ * 1.5);
        T* newData = new T[capacity_];
        for (size_t i = 0; i < size(); i++) {
            newData[i] = data_[i];
        }

        auto tmp = data_;
        data_ = newData;
        delete[] tmp;
    }
    data_[size_] = value;
    size_++;
}


template <class T>
auto Vector<T>::begin() -> T* {
    return data_;
}

template <class T>
auto Vector<T>::end() -> T* {
    return data_ + size();
}


#endif /* Vector_hpp */
