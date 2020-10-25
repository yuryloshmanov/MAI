//
//  Rhombus.hpp
//  lab4
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 20.10.2020.
//


#ifndef Rhombus_hpp
#define Rhombus_hpp


#include <algorithm>
#include <utility>
#include <vector>


#include "Figure.hpp"


template <class T>
class Rhombus: public Figure<T> {
public:
    explicit Rhombus(std::vector<std::pair<T, T>> coordinates);
};


template <class T>
Rhombus<T>::Rhombus(std::vector<std::pair<T, T>> coordinates): Figure<T>(std::move(coordinates)) {
    auto& coord = this->coord;
    auto& square = this->square;

    if (!(sqrt(pow(coord[1].first - coord[0].first, 2) + pow(coord[1].second - coord[0].second, 2)) ==
          sqrt(pow(coord[2].first - coord[0].first, 2) + pow(coord[2].second - coord[0].second, 2)) &&
          sqrt(pow(coord[3].first - coord[1].first, 2) + pow(coord[3].second - coord[1].second, 2)) ==
          sqrt(pow(coord[3].first - coord[2].first, 2) + pow(coord[3].second - coord[2].second, 2)))
            ) {
        throw std::logic_error("Invalid rhombus");
    }
    square = (sqrt(pow(coord[3].first - coord[0].first, 2) + pow(coord[3].second - coord[0].second, 2)) *
              sqrt(pow(coord[1].first - coord[2].first, 2) + pow(coord[1].second - coord[2].second, 2))) / 2;
}


#endif /* Rhombus_hpp */
