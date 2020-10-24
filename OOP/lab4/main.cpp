//
//  main.cpp
//  lab4
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 20.10.2020.
//


#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>


#include "Figures/Figure.hpp"
#include "Figures/Rectangle.hpp"
#include "Figures/Trapezoid.hpp"
#include "Figures/Rhombus.hpp"


template <class T, size_t index = 0>
auto print(const T& tuple) -> typename std::enable_if<index >= std::tuple_size<T>::value, void>::type {
}


template <class T, size_t index = 0>
auto print(const T& tuple) -> typename std::enable_if<index < std::tuple_size<T>::value, void>::type {
    auto figure = std::get<index>(tuple);
    std::cout << figure << std::endl;
    print<T, index + 1>(tuple);
}


template <class T, size_t index = 0>
auto square(const T& tuple) -> typename std::enable_if<index >= std::tuple_size<T>::value, double>::type {
    return 0;
}


template <class T, size_t index = 0>
auto square(const T& tuple) -> typename std::enable_if<index < std::tuple_size<T>::value, double>::type {
    auto figure = std::get<index>(tuple);
    return figure.square + square<T, index + 1>(tuple);
}


auto main() -> int {
    std::vector<std::pair<double, double>>
    v1 = {{2, 2}, {2, 4}, {6, 2}, {6, 4}},
    v2 = {{0, 0}, {2, 4}, {6, 4}, {8, 0}},
    v3 = {{-1, 1}, {2, 2}, {-2, -2}, {1, -1}};
    
    auto rect = Rectangle(v1);
    auto trapez = Trapezoid(v2);
    auto rhomb = Rhombus(v3);
    
    auto tuple = std::make_tuple(rect, trapez, rhomb);
    
    for (std::string line; std::getline(std::cin, line);) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if (command == "square") {
            std::cout << square(tuple) << std::endl;
        } else if (command == "print") {
            print(tuple);
        } else {
            std::cerr << "Invalid command" << std::endl;
        }
    }
    return 0;
}
