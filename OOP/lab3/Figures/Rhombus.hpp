//
//  Rhombus.hpp
//  lab3
//
//  Created by Юрий Лошманов on 16.10.2020.
//


#ifndef Rhombus_hpp
#define Rhombus_hpp


#include <algorithm>
#include <utility>
#include <vector>


class Rhombus: public Figure {
    std::vector<std::pair<double, double>> coordinates;
    
public:
    Rhombus(std::vector<std::pair<double, double>> coordinates);
    
    auto geometriсСenter() -> std::pair<double, double> override;
    auto square() -> double override;
};


Rhombus::Rhombus(std::vector<std::pair<double, double>> coordinates) {
    std::sort(coordinates.begin(), coordinates.end(), [](auto lhs, auto rhs) {
        return lhs.first < rhs.first;
    });
    std::sort(coordinates.begin(), coordinates.end(), [](auto lhs, auto rhs) {
        return lhs.second > rhs.second;
    });

    if (!(
          sqrt(pow(coordinates[1].first - coordinates[0].first, 2) + pow(coordinates[1].second - coordinates[0].second, 2)) ==
          sqrt(pow(coordinates[2].first - coordinates[0].first, 2) + pow(coordinates[2].second - coordinates[0].second, 2)) &&
          sqrt(pow(coordinates[3].first - coordinates[1].first, 2) + pow(coordinates[3].second - coordinates[1].second, 2)) ==
          sqrt(pow(coordinates[3].first - coordinates[2].first, 2) + pow(coordinates[3].second - coordinates[2].second, 2))
    )) {
        throw std::logic_error("Invalid rhombus");
    }
    this->coordinates = coordinates;
}


auto Rhombus::geometriсСenter() -> std::pair<double, double> {
    return std::make_pair(coordinates[0].first + (coordinates[3].first - coordinates[0].first) / 2, coordinates[0].second + (coordinates[3].second - coordinates[0].second) / 2);
}


auto Rhombus::square() -> double {
    return (sqrt(pow(coordinates[3].first - coordinates[0].first, 2) + pow(coordinates[3].second - coordinates[0].second, 2)) *
    sqrt(pow(coordinates[1].first - coordinates[2].first, 2) + pow(coordinates[1].second - coordinates[2].second, 2))) / 2;
}




#endif /* Rhombus_hpp */
