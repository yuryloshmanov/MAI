//
//  main.cpp
//  lab3
//
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


int main() {
    std::vector<std::unique_ptr<Figure>> v;
    
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if (command == "push") {
            std::vector<std::pair<double, double>> values;
            double x, y;
            while (ss >> x >> y) {
                values.push_back(std::make_pair(x, y));
            }
            if (values.size() == 4) {
                try {
                    v.push_back(std::make_unique<Rectangle>(Rectangle(values)));
                } catch (std::logic_error&) {
                    try {
                        v.push_back(std::make_unique<Rhombus>(Rhombus(values)));
                    } catch (std::logic_error&) {
                        
                    }
                }
            } else if (values.size() == 5) {
                
            } else {
                std::cerr << "invalid figure" << std::endl;
            }
        } else if (command == "del") {
            size_t index;
            ss >> index;
            v.erase(v.begin() + index);
        } else if (command == "square") {
            double sum = 0;
            for (auto& fig: v) {
                sum += fig->square();
            }
            std::cout << sum << std::endl;
        } else if (command == "center") {
            for (auto& fig: v) {
                auto center = fig->geometriсСenter();
                std::cout << "(" << center.first << ", " << center.second << ")" << std::endl;
            }
        } else {
            std::cerr << "invalid command" << std::endl;
        }
    }
    return 0;
}

//
//  push 2 2 2 4 6 2 6 4
//  push 1 1 -1 -1 1 -1 -1 1
//