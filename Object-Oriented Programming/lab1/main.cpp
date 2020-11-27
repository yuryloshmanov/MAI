//
//  main.cpp
//  lab1
//  Variant 15
//  Created by Юрий Лошманов on 04.09.2020.
//  Copyright © 2020 Юрий Лошманов. All rights reserved.
//

#include <iostream>

#include "TransNumber.hpp"

auto main() -> int {
    std::cout << "Введите первое число, операцию, второе число\n" <<
    "Пример: 2 5 C * 5 22 C\n" <<
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
            TransNumber n1;
            TransNumber n2;
            char operation;
            ss >> n1 >> std::ws >> operation >> std::ws >> n2;
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
