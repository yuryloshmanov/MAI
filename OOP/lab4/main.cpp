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

auto randInt() -> int {
    return rand() % 20 * pow(-1, 1 + rand() % 2);
}

template <class T>
auto randomRectangle() -> Rectangle<T> {
    auto x1 = randInt();
    auto x2 = randInt();
    
    auto y1 = randInt();
    auto y2 = randInt();
    
    return Rectangle<T>({{x1, y1}, {x1, y2}, {x2, y1}, {x2, y2}});
}

template <class T>
auto randomTrapezoid() -> Trapezoid<T> {
    auto x1 = randInt();
    auto x2 = randInt();
    auto x3 = randInt();
    auto x4 = randInt();
    
    auto y1 = randInt();
    auto y2 = randInt();
    
    return Trapezoid<T>({{x1, y1}, {x2, y2}, {x3, y1}, {x4, y2}});
}

template <class T>
auto randomRhombus() -> Rhombus<T> {
    auto x = randInt();
    auto dx = randInt();
    
    auto y = randInt();
    auto dy = randInt();
    
    return Rhombus<T>({{x - dx, y}, {x, y + dy}, {x + dx, y}, {x, y - dy}});
}

auto main() -> int {
    auto tuple = std::make_tuple(
        randomRectangle<double>(), randomTrapezoid<double>(), randomRhombus<double>(),
        randomRectangle<double>(), randomTrapezoid<double>(), randomRhombus<double>()
    );
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
