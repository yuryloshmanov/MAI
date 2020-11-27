//
//  List.hpp
//  lab5
//  Группа М8О-206Б-19
//  Вариант 15
//  Created by Юрий Лошманов on 12.11.2020.
//

#ifndef LAB5_LIST_HPP
#define LAB5_LIST_HPP


#include <memory>
#include <cstddef>


template <class T>
class List {
    struct ListNode {
        T value;
        std::shared_ptr<ListNode> next;
        std::weak_ptr<ListNode> prev;

        ListNode(): next(nullptr), prev(std::shared_ptr<ListNode>(nullptr)) {}
        explicit ListNode(T value): value(value), next(nullptr), prev(std::shared_ptr<ListNode>(nullptr)) {}
    };

    std::shared_ptr<ListNode> head_;
    std::shared_ptr<ListNode> tail_;
    std::shared_ptr<ListNode> end_;
    size_t size_;

public:
    class Iterator {
        std::shared_ptr<ListNode> node_;

    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef int64_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        Iterator(): node_(nullptr) {}
        explicit Iterator(std::shared_ptr<ListNode> node): node_(node) {}
        ~Iterator() = default;

        auto operator++() -> List<T>::Iterator;
        auto operator++(int) -> List<T>::Iterator;
        auto operator--() -> List<T>::Iterator;
        auto operator--(int) -> List<T>::Iterator;
        auto operator*() const -> T;
        auto operator*() -> T&;
        auto operator->() const -> std::shared_ptr<T>;
        auto operator==(const List<T>::Iterator& rhs) const noexcept -> bool;
        auto operator!=(const List<T>::Iterator& rhs) const noexcept -> bool;

        friend auto List<T>::Iterator::operator*() const -> T;
        friend auto List<T>::Iterator::operator*() -> T&;
        friend auto List<T>::insert(const List<T>::Iterator& iter, T&& value) -> void;
        friend auto List<T>::erase(const List<T>::Iterator& iter) -> void;
    };

    auto begin() -> Iterator;
    auto end() -> Iterator;

    List();
    ~List() = default;

    auto operator[](size_t index) const -> T;
    auto operator[](size_t index) -> T&;

    [[nodiscard]] auto size() const -> size_t;
    auto insert(const List<T>::Iterator& iter, T&& value) -> void;
    auto erase(const List<T>::Iterator& iter) -> void;
    auto pushFront(T&& value) noexcept -> void;
    auto pushBack(T&& value) noexcept -> void;
    auto popFront() noexcept -> void;
    auto popBack() noexcept -> void;
};




template<class T>
auto List<T>::Iterator::operator++() -> List<T>::Iterator {
    node_ = node_->next;
    return *this;
}

template<class T>
auto List<T>::Iterator::operator++(int) -> List<T>::Iterator {
    auto tmp = *this;
    node_ = node_->next;
    return tmp;
}

template<class T>
auto List<T>::Iterator::operator--() -> List<T>::Iterator {
    node_ = node_->prev.lock();
    return *this;
}

template<class T>
auto List<T>::Iterator::operator--(int) -> List<T>::Iterator {
    auto tmp = *this;
    node_ = node_->prev.lock();
    return tmp;
}

template<class T>
auto List<T>::Iterator::operator*() const -> T {
    return node_->value;
}


template<class T>
auto List<T>::Iterator::operator==(const List<T>::Iterator& rhs) const noexcept -> bool {
    return this->node_ == rhs.node_;
}


template<class T>
auto List<T>::Iterator::operator!=(const List<T>::Iterator& rhs) const noexcept -> bool {
    return this->node_ != rhs.node_;
}

template<class T>
auto List<T>::Iterator::operator*() -> T& {
    return node_->value;
}

template<class T>
auto List<T>::Iterator::operator->() const -> std::shared_ptr<T> {
    return std::make_shared<T>(node_->value);
}


template <class T>
List<T>::List(): head_(nullptr), tail_(nullptr), end_(std::make_shared<ListNode>()), size_(0) {
    end_->prev = tail_;
}


template <class T>
auto List<T>::operator[](size_t index) const -> T {
    if (index < 0 || index >= size_) {
        throw std::range_error("Index out of range\n");
    }
    std::shared_ptr<ListNode> tmp = head_;
    for (size_t i = 0; i < index; i++) {
        tmp = tmp->next;
    }
    return tmp->value;
}


template<class T>
auto List<T>::operator[](size_t index) -> T& {
    if (index < 0 || index >= size_) {
        throw std::range_error("Index out of range\n");
    }
    std::shared_ptr<ListNode> tmp = head_;
    for (size_t i = 0; i < index; i++) {
        tmp = tmp->next;
    }
    return tmp->value;
}

template <class T>
auto List<T>::size() const -> size_t {
    return size_;
}

template <class T>
auto List<T>::pushFront(T&& value) noexcept -> void {
    if (head_ == nullptr) {
        head_ = std::make_shared<ListNode>(value);
        tail_ = head_;
        end_->prev = tail_;
        tail_->next = end_;
    } else {
        auto tmp = head_;
        auto newNode = std::make_shared<ListNode>(value);
        newNode->next = tmp;
        tmp->prev = newNode;
        head_ = newNode;
    }
    size_++;
}

template<class T>
auto List<T>::pushBack(T &&value) noexcept -> void {
    if (head_ == nullptr) {
        head_ = std::make_shared<ListNode>(value);
        tail_ = head_;
    } else {
        auto tmp = tail_;
        tmp->next = std::make_shared<ListNode>(value);
        tail_ = tmp->next;
        tail_->prev = tmp;
    }
    end_->prev = tail_;
    tail_->next = end_;

    size_++;
}

template<class T>
auto List<T>::popBack() noexcept -> void {
    if (head_ != nullptr) {
        if (head_ == tail_) {
            head_ = nullptr;
            tail_ = nullptr;
        } else {
            auto tmp = tail_->prev.lock();
            tail_ = tmp;
            end_->prev = tail_;
            tail_->next = end_;
        }
        size_--;
    }
}

template<class T>
auto List<T>::begin() -> List::Iterator {
    return Iterator(head_);
}

template<class T>
auto List<T>::end() -> List::Iterator {
    return Iterator(end_);
}

template<class T>
auto List<T>::insert(const List<T>::Iterator &iter, T &&value) -> void {
    if (iter == begin()) {
        this->pushFront(std::move(value));
    } else if (iter == end()) {
        this->pushBack(std::move(value));
    } else {
        auto tmp = iter.node_->prev.lock();
        auto newNode = std::make_shared<ListNode>(value);
        tmp->next = newNode;
        newNode->prev = tmp;
        newNode->next = iter.node_;
        iter.node_->prev = newNode;
        size_++;
    }
}

template<class T>
auto List<T>::popFront() noexcept -> void {
    if (head_ != nullptr) {
        if (head_ == tail_) {
            head_ = nullptr;
            tail_ = nullptr;
        } else {
            head_ = head_->next;
        }
        size_--;
    }
}

template<class T>
auto List<T>::erase(const List<T>::Iterator& iter) -> void {
    if (iter.node_ == nullptr) {
        throw std::range_error("Erasing at null pointer");
    } if (iter == end()) {
        throw std::range_error("Erasing at end");
    } else if (iter == begin()) {
        this->popFront();
    } else {
        auto right = iter.node_->next;
        auto left = iter.node_->prev.lock();
        left->next = right;
        right->prev = left;
        size_--;
    }
}


#endif //LAB5_LIST_HPP
