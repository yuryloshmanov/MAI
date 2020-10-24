//
//  Figure.hpp
//  lab4
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 20.10.2020.
//

#ifndef Figure_hpp
#define Figure_hpp


#include <iostream>
#include <utility>
#include <vector>


template <class T>
class Figure {
public:
    std::vector<std::pair<T, T>> coord;
    double square;
    
    Figure() = default;
    explicit Figure(std::vector<std::pair<T, T>> coordinates);
    virtual ~Figure() = default;
};


template <class T>
Figure<T>::Figure(std::vector<std::pair<T, T>> coordinates) {
    std::sort(coordinates.begin(), coordinates.end(), [](auto lhs, auto rhs) {
        return lhs.first < rhs.first;
    });
    std::sort(coordinates.begin(), coordinates.end(), [](auto lhs, auto rhs) {
        return lhs.second > rhs.second;
    });
    this->coord = std::move(coordinates);
}


template <class T>
auto operator<<(std::ostream& out, const Figure<T>& figure) -> std::ostream& {
    for (const auto& [x, y]: figure.coord) {
        out << "(" << x << ", " << y << ")  ";
    }
    return out;
}


template <class T, size_t index = 0>
auto print(const T& tuple) -> typename std::enable_if<index >= std::tuple_size<T>::value, void>::type {
}


template <class T, size_t index = 0>
auto print(const T& tuple) -> typename std::enable_if<index < std::tuple_size<T>::value, void>::type {
    auto figure = std::get<index>(tuple);
    std::cout << figure << std::endl;
    print<T, index + 1>(tuple);
}


template <class T, size_t index = 0>
auto square(const T& tuple) -> typename std::enable_if<index >= std::tuple_size<T>::value, double>::type {
    return 0;
}


template <class T, size_t index = 0>
auto square(const T& tuple) -> typename std::enable_if<index < std::tuple_size<T>::value, double>::type {
    auto figure = std::get<index>(tuple);
    return figure.square + square<T, index + 1>(tuple);
}


#endif /* Figure_hpp */
