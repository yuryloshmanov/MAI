//
//  Figure.hpp
//  lab8
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 21.11.2020.
//

#ifndef Figure_hpp
#define Figure_hpp


#include <iostream>
#include <fstream>
#include <utility>
#include <vector>


enum class FigureType {
    Rectangle,
    Rhombus,
    Trapezoid
};


template <class T>
class Figure {
public:
    std::vector<std::pair<T, T>> coord;
    double square{};

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

    out << "square = " << figure.square;

    return out;
}


template <class T>
auto operator<<(std::ofstream& out, const Figure<T>& figure) -> std::ofstream& {
    for (const auto& [x, y]: figure.coord) {
        out << "(" << x << ", " << y << ")  ";
    }

    out << "square = " << figure.square;
    return out;
}


#endif /* Figure_hpp */
