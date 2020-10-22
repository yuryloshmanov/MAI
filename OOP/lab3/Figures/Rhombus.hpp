//
//  Rhombus.hpp
//  lab3
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 16.10.2020.
//


#ifndef Rhombus_hpp
#define Rhombus_hpp


#include <algorithm>
#include <utility>
#include <vector>


#include "Figure.hpp"


class Rhombus: public Figure {
public:
    explicit Rhombus(std::vector<std::pair<double, double>> coordinates);

    auto geometricCenter() -> std::pair<double, double> override;
    auto square() -> double override;
};


Rhombus::Rhombus(std::vector<std::pair<double, double>> coordinates): Figure(std::move(coordinates)) {
    if (!(sqrt(
            pow(coord_[1].first - coord_[0].first, 2) +
            pow(coord_[1].second - coord_[0].second, 2)
            ) == sqrt(
            pow(coord_[2].first - coord_[0].first, 2) +
            pow(coord_[2].second - coord_[0].second, 2)
            ) && sqrt(
            pow(coord_[3].first - coord_[1].first, 2) +
            pow(coord_[3].second - coord_[1].second, 2)
            ) == sqrt(
            pow(coord_[3].first - coord_[2].first, 2) +
            pow(coord_[3].second - coord_[2].second, 2)
            )
    )) {
        throw std::logic_error("Invalid rhombus");
    }
}


auto Rhombus::geometricCenter() -> std::pair<double, double> {
    return std::make_pair(
            coord_[0].first + (coord_[3].first - coord_[0].first) / 2,
            coord_[0].second + (coord_[3].second - coord_[0].second) / 2
    );
}


auto Rhombus::square() -> double {
    return (
                   sqrt(
                           pow(coord_[3].first - coord_[0].first, 2) +
                           pow(coord_[3].second - coord_[0].second, 2)
                   ) * sqrt(
                           pow(coord_[1].first - coord_[2].first, 2) +
                           pow(coord_[1].second - coord_[2].second, 2)
                   )
           ) / 2;
}


#endif /* Rhombus_hpp */
