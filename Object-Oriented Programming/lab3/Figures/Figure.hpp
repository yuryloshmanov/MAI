//
//  Figure.hpp
//  lab3
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 16.10.2020.
//

#ifndef Figure_hpp
#define Figure_hpp


#include <iostream>
#include <utility>
#include <vector>


class Figure {
protected:
    std::vector<std::pair<double, double>> coord_;

public:
    Figure() = default;
    explicit Figure(std::vector<std::pair<double, double>> coordinates);
    virtual ~Figure() = default;

    virtual auto geometricCenter() -> std::pair<double, double> = 0;
    virtual auto square() -> double = 0;

    friend auto operator<<(std::ostream& out, const Figure& figure) -> std::ostream&;
};


Figure::Figure(std::vector<std::pair<double, double>> coordinates) {
    std::sort(coordinates.begin(), coordinates.end(), [](auto lhs, auto rhs) {
        return lhs.first < rhs.first;
    });
    std::sort(coordinates.begin(), coordinates.end(), [](auto lhs, auto rhs) {
        return lhs.second > rhs.second;
    });
    this->coord_ = std::move(coordinates);
}


auto operator<<(std::ostream& out, const Figure& figure) -> std::ostream& {
    for (const auto& [x, y]: figure.coord_) {
        out << "(" << x << ", " << y << ")  ";
    }
    return out;
}


#endif /* Figure_hpp */
