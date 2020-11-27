//
//  main.cpp
//  lab2
//  Группа М8О-206Б-19
//  Вариант 4
//  Created by Юрий Лошманов on 18.09.2020.
//  Copyright © 2020 Юрий Лошманов. All rights reserved.
//

#include <iostream>

#include "FuzzyNumber.hpp"

auto main() -> int {
    std::cout << "Введите первое число, операцию, второе число\n" <<
    "Пример: " <<"1 2 3"_fz << " * " << "3 5 0"_fz << "\n" <<
    "Чтобы выйти, введите exit" << std::endl;
    while (true) {
        try {
            std::string s;
            std::getline(std::cin, s);
            if (std::cin.eof() || s == "exit") {
                break;
            } else if (s.empty()) {
                continue;
            }
            std::stringstream ss(s);
            FuzzyNumber<double> n1;
            FuzzyNumber<double> n2;
            char operation;
            ss >> std::ws;
            if (ss.peek() == '-') {
                ss >> operation >> std::ws >> n2;
                std::cout << -n2;
                continue;
            } else {
                ss >> n1 >> std::ws >> operation >> std::ws >> n2;
            }
            switch (operation) {
                case '+':
                    std::cout << n1 + n2 << std::endl;
                    break;
                case '-':
                    std::cout << n1 - n2 << std::endl;
                    break;
                case '*':
                    std::cout << n1 * n2 << std::endl;
                    break;
                case '/':
                    std::cout << n1 / n2 << std::endl;
                    break;
                default:
                    std::cout << "Неизвестная операция" << std::endl;
                    break;
            }
        } catch (std::logic_error& err) {
            std::cout << err.what() << std::endl;
        }
    }
    return 0;
}
