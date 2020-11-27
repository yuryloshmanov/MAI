//
//  All.hpp
//  lab6
//  Группа М8О-206Б-19
//  Вариант 15
//  Created by Юрий Лошманов on 21.11.2020.
//


#ifndef LAB6_ALLOCATOR_HPP
#define LAB6_ALLOCATOR_HPP


#include <iostream>
#include <cstdlib>


#include <stack>


template<class T, size_t BlockCount = 100>
class Allocator {
private:
    char *occupiedBlocks_;
    std::stack<void **> freeBlocks_;

public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    Allocator() {
        occupiedBlocks_ = (char *)malloc(sizeof(T) * BlockCount);

        for (uint64_t i = 0; i < BlockCount; i++) {
            freeBlocks_.push((void **)(occupiedBlocks_ + i * sizeof(T)));
        }
    }

    ~Allocator(){
        delete[] occupiedBlocks_;
    }

    template<typename U>
    struct rebind {
        using other = Allocator<U,BlockCount>;
    };


    T* allocate(size_t n) {
        if (freeBlocks_.size() <= 0) {
            freeBlocks_ = std::stack<void **>();
        }

        T *result = (T *)freeBlocks_.top();
        freeBlocks_.pop();
        return result;
    }


    void deallocate(T* pointer,  size_t ) {
        freeBlocks_.push((void **)pointer);
    }


    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        new (p) U(std::forward<Args>(args)...);
    }


    void destroy(pointer p) {
        p->~T();
    }
};


#endif //LAB6_ALLOCATOR_HPP
