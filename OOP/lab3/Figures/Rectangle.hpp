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
    std::vector<std::pair<double, double>> coordinates;

public:
    explicit Rectangle(std::vector<std::pair<double, double>> coordinates);

    auto geometricCenter() -> std::pair<double, double> override;
    auto square() -> double override;
};


Rectangle::Rectangle(std::vector<std::pair<double, double>> coordinates) {
    std::sort(coordinates.begin(), coordinates.end(), [](auto lhs, auto rhs) {
        return lhs.first < rhs.first;
    });
    std::sort(coordinates.begin(), coordinates.end(), [](auto lhs, auto rhs) {
        return lhs.second > rhs.second;
    });

    if (
        !(coordinates[0].first == coordinates[2].first && coordinates[1].first == coordinates[3].first &&
        coordinates[0].second == coordinates[1].second && coordinates[2].second == coordinates[3].second)
    ) {
        throw std::logic_error("Invalid rectangle");
    }

    this->coordinates = coordinates;
}


auto Rectangle::geometricCenter() -> std::pair<double, double> {
    return std::make_pair(
        coordinates[0].first + (coordinates[1].first - coordinates[0].first) / 2,
        coordinates[2].second + (coordinates[0].second - coordinates[2].second) / 2
    );
}


auto Rectangle::square() -> double {
    return std::abs(coordinates[1].first - coordinates[0].first) *
    std::abs(coordinates[2].second - coordinates[0].second);
}


#endif /* Rectangle_hpp */
