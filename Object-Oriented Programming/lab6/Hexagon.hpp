//
//  Hexagon.hpp
//  lab6
//  Группа М8О-206Б-19
//  Вариант 15
//  Created by Юрий Лошманов on 21.11.2020.
//

#ifndef LAB6_HEXAGON_HPP
#define LAB6_HEXAGON_HPP


#include <iostream>
#include <utility>
#include <cmath>


template <class T>
class Hexagon {
    std::pair<T, T> center_;
    T radius_;

public:
    Hexagon() = default;
    explicit Hexagon(std::pair<T, T> center, T radius);
    auto square() -> T;

    friend auto operator>>(std::istream& is, Hexagon<T>& hex) -> std::istream& {
        is >> hex.center_.first >> hex.center_.second >> hex.radius_;
        return is;
    }
    friend auto operator<<(std::ostream& os, Hexagon<T>& hex) -> std::ostream& {
        os << "(" << hex.center_.first << ", " << hex.center_.second << ") " << hex.radius_;
        return os;
    }
};



template<class T>
Hexagon<T>::Hexagon(std::pair<T, T> center, T radius): center_(center), radius_(radius) {
    if (radius < 0) {
        throw std::domain_error("Invalid size");
    }
}


template<class T>
auto Hexagon<T>::square() -> T {
    return radius_ * radius_ * ((3 * sqrt(3)) / 2);
}


#endif //LAB6_HEXAGON_HPP
