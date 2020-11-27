//
//  main.cpp
//  lab6
//  Группа М8О-206Б-19
//  Вариант 15
//  Created by Юрий Лошманов on 21.11.2020.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>


#include "Allocator.hpp"
#include "List.hpp"
#include "Hexagon.hpp"


auto main() -> int {
    List<Hexagon<int>, Allocator<Hexagon<int>>> l;
    for (std::string line; std::getline(std::cin, line);) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if (command == "push") {
            std::string location;
            Hexagon<int> hex;
            ss >> location >> hex;
            if (location == "back") {
                l.pushBack(std::move(hex));
            } else if (location == "front") {
                l.pushFront(std::move(hex));
            } else {
                try {
                    auto index = std::stoi(location);
                    auto it = l.begin();
                    for (int i = 0; i < index; i++) {
                        it++;
                    }
                    l.insert(it, std::move(hex));
                } catch (std::range_error& err) {
                    std::cerr << err.what() << std::endl;
                }
            }
        } else if (command == "pop") {
            std::string location;
            Hexagon<int> hex;
            ss >> location >> hex;
            if (location == "back") {
                l.popBack();
            } else if (location == "front") {
                l.popFront();
            } else {
                auto index = std::stoi(location);
                auto it = l.begin();
                for (int i = 0; i < index; i++) {
                    it++;
                }
                try {
                    l.erase(it);
                } catch (std::range_error& err) {
                    std::cout << err.what() << std::endl;
                }
            }
        } else if (command == "print") {
            std::for_each(l.begin(), l.end(), [](Hexagon<int> hex){ std::cout << hex << std::endl; });
        } else if (command == "square") {
            int value;
            ss >> value;
            std::cout << std::count_if(l.begin(), l.end(), [value](Hexagon<int> hex) {
                return hex.square() < value;
            }) << std::endl;
        } else {
            std::cerr << "Invalid command" << std::endl;
        }
    }
    return 0;
}
