//
//  Figure.hpp
//  lab7
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 10.11.2020.
//

#ifndef Figure_hpp
#define Figure_hpp


#include <iostream>
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
auto operator>>(std::ifstream& in, Figure<T>& figure) -> std::ifstream& {
    auto size = figure.coord.size();
    in.read((char *)&size, sizeof(size));
    in.read((char *)&figure.square, sizeof(figure.square));

    for (size_t i = 0; i < size; i++) {
        std::pair<T, T> p;

        in.read((char *)&p.first, sizeof(p.first));
        in.read((char *)&p.second, sizeof(p.second));

        figure.coord.push_back(p);
    }

    return in;
}


template <class T>
auto operator<<(std::ofstream& out, const Figure<T>& figure) -> std::ofstream& {
    auto size = figure.coord.size();
    out.write((const char *)&size, sizeof(size));
    out.write((char *)&figure.square, sizeof(figure.square));

    for (const auto& [x, y]: figure.coord) {
        out.write((const char *)&x, sizeof(x));
        out.write((const char *)&y, sizeof(y));
    }

    return out;
}


#endif /* Figure_hpp */
