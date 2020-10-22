//
//  Rectangle.hpp
//  lab3
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 16.10.2020.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp


#include <algorithm>
#include <utility>
#include <vector>


#include "Figure.hpp"


class Rectangle: public Figure {
public:
    explicit Rectangle(std::vector<std::pair<double, double>> coordinates);

    auto geometricCenter() -> std::pair<double, double> override;
    auto square() -> double override;
};


Rectangle::Rectangle(std::vector<std::pair<double, double>> coordinates): Figure(std::move(coordinates)) {
    if (!(coord_[0].first == coord_[2].first && coord_[1].first == coord_[3].first &&
          coord_[0].second == coord_[1].second && coord_[2].second == coord_[3].second)
    ) {
        throw std::logic_error("Invalid rectangle");
    }
}


auto Rectangle::geometricCenter() -> std::pair<double, double> {
    return std::make_pair(
            coord_[0].first + (coord_[1].first - coord_[0].first) / 2,
            coord_[2].second + (coord_[0].second - coord_[2].second) / 2
    );
}


auto Rectangle::square() -> double {
    return std::abs(coord_[1].first - coord_[0].first) * std::abs(coord_[2].second - coord_[0].second);
}


#endif /* Rectangle_hpp */
