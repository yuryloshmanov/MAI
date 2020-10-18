//
//  Trapezoid.hpp
//  lab3
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 16.10.2020.
//

#ifndef Trapezoid_hpp
#define Trapezoid_hpp


#include <algorithm>
#include <utility>
#include <vector>


#include "Figure.hpp"


class Trapezoid: public Figure {
    std::vector<std::pair<double, double>> coordinates;

public:
    explicit Trapezoid(std::vector<std::pair<double, double>> coordinates);

    auto geometricCenter() -> std::pair<double, double> override;
    auto square() -> double override;
};


Trapezoid::Trapezoid(std::vector<std::pair<double, double>> coordinates) {
    std::sort(coordinates.begin(), coordinates.end(), [](auto lhs, auto rhs) {
        return lhs.first < rhs.first;
    });
    std::sort(coordinates.begin(), coordinates.end(), [](auto lhs, auto rhs) {
        return lhs.second > rhs.second;
    });

    if (!(coordinates[0].second == coordinates[1].second && coordinates[2].second == coordinates[3].second)) {
        throw std::logic_error("Invalid trapezoid");
    }
    this->coordinates = coordinates;
}


auto Trapezoid::geometricCenter() -> std::pair<double, double> {
    auto [xa, ya] = coordinates[2];
    auto [xb, yb] = coordinates[0];
    auto [xc, yc] = coordinates[1];
    auto [xd, yd] = coordinates[3];

    auto A = xc - xa;
    auto B = yc - ya;
    auto C = xd - xb;
    auto D = yd - yb;

    auto x = (yb + xa * B / A - xb * D / C - ya) / (B / A - D / C);
    auto y = (xb + ya * A / B - yb * C / D - xa) / (A / B - C / D);

    return std::make_pair(x, y);
}


auto Trapezoid::square() -> double {
    auto a = coordinates[1].first - coordinates[0].first;
    auto b = coordinates[3].first - coordinates[2].first;

    auto h = coordinates[0].second - coordinates[2].second;

    return h * (a + b) / 2;
}


#endif /* Trapezoid_hpp */
