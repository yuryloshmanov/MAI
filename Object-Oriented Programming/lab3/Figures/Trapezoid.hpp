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
public:
    explicit Trapezoid(std::vector<std::pair<double, double>> coordinates);

    auto geometricCenter() -> std::pair<double, double> override;
    auto square() -> double override;
};


Trapezoid::Trapezoid(std::vector<std::pair<double, double>> coordinates): Figure(std::move(coordinates)) {
    if (!(coord_[0].second == coord_[1].second && coord_[2].second == coord_[3].second)) {
        throw std::logic_error("Invalid trapezoid");
    }
}


auto Trapezoid::geometricCenter() -> std::pair<double, double> {
    auto [xa, ya] = coord_[2];
    auto [xb, yb] = coord_[0];
    auto [xc, yc] = coord_[1];
    auto [xd, yd] = coord_[3];

    auto A = xc - xa;
    auto B = yc - ya;
    auto C = xd - xb;
    auto D = yd - yb;

    auto x = (yb + xa * B / A - xb * D / C - ya) / (B / A - D / C);
    auto y = (xb + ya * A / B - yb * C / D - xa) / (A / B - C / D);

    return std::make_pair(x, y);
}


auto Trapezoid::square() -> double {
    auto a = coord_[1].first - coord_[0].first;
    auto b = coord_[3].first - coord_[2].first;

    auto h = coord_[0].second - coord_[2].second;

    return h * (a + b) / 2;
}


#endif /* Trapezoid_hpp */
