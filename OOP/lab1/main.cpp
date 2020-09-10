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
    std::cout << "Чтобы выйти, введите exit" << std::endl;
    while (true) {
        std::string line1;
        std::string line2;
        std::cout << "Введите первое число: ";
        std::getline(std::cin, line1);
        if (line1 == "exit") { break; }
        std::cout << "Введите второе число: ";
        std::getline(std::cin, line2);
        if (line2 == "exit") { break; }
        try {
            TransNumber n1(line1);
            TransNumber n2(line2);
            std::cout << "Первое число: " << n1 << std::endl;
            std::cout << "Второе число: " << n2 << std::endl;
            std::cout << "Сложение числел: " << n1 + n2 << std::endl;
            std::cout << "Вычитание второго числа из первого: " << n1 - n2 << std::endl;
            std::cout << "Умножение чисел: " << n1 * n2 << std::endl;
            std::cout << "Деление первого числа на второе: " << n1 / n2 << std::endl;
        } catch (std::logic_error& err) {
            std::cout << err.what() << std::endl;
        }
    }
    return 0;
}
