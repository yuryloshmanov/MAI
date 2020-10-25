//
//  Trapezoid.hpp
//  lab4
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 20.10.2020.
//

#ifndef Trapezoid_hpp
#define Trapezoid_hpp


#include <algorithm>
#include <utility>
#include <vector>


#include "Figure.hpp"


template <class T>
class Trapezoid: public Figure<T> {
public:
    explicit Trapezoid(std::vector<std::pair<T, T>> coordinates);
};


template <class T>
Trapezoid<T>::Trapezoid(std::vector<std::pair<T, T>> coordinates): Figure<T>(std::move(coordinates)) {
    auto& coord = this->coord;
    auto& square = this->square;
    
    if (!(coord[0].second == coord[1].second && coord[2].second == coord[3].second)) {
        throw std::logic_error("Invalid trapezoid");
    }
    
    auto a = coord[1].first - coord[0].first;
    auto b = coord[3].first - coord[2].first;
    auto h = coord[0].second - coord[2].second;
    square = h * (a + b) / 2;
}


#endif /* Trapezoid_hpp */
