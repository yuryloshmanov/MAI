//
//  Rectangle.hpp
//  lab4
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 20.10.2020.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp


#include <algorithm>
#include <utility>
#include <vector>


#include "Figure.hpp"


template <class T>
class Rectangle: public Figure<T> {
public:
    explicit Rectangle(std::vector<std::pair<T, T>> coordinates);
};


template <class T>
Rectangle<T>::Rectangle(std::vector<std::pair<T, T>> coordinates): Figure<T>(std::move(coordinates)) {
    auto& coord = this->coord;
    auto& square = this->square;
    
    if (!(coord[0].first == coord[2].first && coord[1].first == coord[3].first &&
          coord[0].second == coord[1].second && coord[2].second == coord[3].second)
    ) {
        throw std::logic_error("Invalid rectangle");
    }
    
    square = std::abs(coord[1].first - coord[0].first) * std::abs(coord[2].second - coord[0].second);
}


#endif /* Rectangle_hpp */
