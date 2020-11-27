//
//  main.cpp
//  lab3
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 16.10.2020.
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


auto main() -> int {
    std::vector<std::unique_ptr<Figure>> v;
    for (std::string line; std::getline(std::cin, line);) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if (command == "push") {
            std::vector<std::pair<double, double>> coord;
            double x, y;
            while (ss >> x >> y) {
                coord.emplace_back(x, y);
            }
            if (coord.size() == 4) {
                try {
                    v.push_back(std::make_unique<Rectangle>(Rectangle(coord)));
                } catch (std::logic_error&) {
                    try {
                        v.push_back(std::make_unique<Rhombus>(Rhombus(coord)));
                    } catch (std::logic_error&) {
                        try {
                            v.push_back(std::make_unique<Trapezoid>(Trapezoid(coord)));
                        } catch (std::logic_error&) {
                            std::cerr << "Invalid figure" << std::endl;
                        }
                    }
                }
            } else {
                std::cerr << "Invalid figure" << std::endl;
            }
        } else if (command == "del") {
            size_t index;
            ss >> index;
            if (index >= 0 && index < v.size()) {
                v.erase(v.begin() + index);
            } else {
                std::cerr << "Invalid index" << std::endl;
            }
        } else if (command == "square") {
            double sum = 0;
            for (const auto& figure: v) {
                sum += figure->square();
            }
            std::cout << sum << std::endl;
        } else if (command == "center") {
            for (const auto& figure: v) {
                auto center = figure->geometricCenter();
                std::cout << "(" << center.first << ", " << center.second << ")" << std::endl;
            }
        } else if (command == "coord") {
            for (const auto& figure: v) {
                std::cout << *figure << std::endl;
            }
        } else {
            std::cerr << "Invalid command" << std::endl;
        }
    }
    return 0;
}
