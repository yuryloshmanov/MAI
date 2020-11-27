//
//  TransNumber.hpp
//  lab1
//  Variant 15
//  Created by Юрий Лошманов on 04.09.2020.
//  Copyright © 2020 Юрий Лошманов. All rights reserved.
//

#ifndef TransNumber_hpp
#define TransNumber_hpp

#include <iostream>
#include <sstream>
#include <string>


// Класс трансцендентного числа
class TransNumber {
    // Структура, описывающая трансцендентную часть числа
    struct TransPart {
        double data;
        std::string constant;
    };

    double a;       // Действительная часть числа
    TransPart b;    // Транцендентрая часть числа

public:
    // Конструкторы класса
    TransNumber() {}                                        // Пустой конструктор
    TransNumber(std::string str) {                          // Конструктор со строкой для парсинга
        std::stringstream ss(str);
        auto flag = true;
        flag = flag && (ss >> a && !ss.eof());
        ss.ignore(1);
        flag = flag && (ss >> b.data && !ss.eof());
        ss.ignore(1);
        flag = flag && (ss >> b.constant && ss.eof());
        if (!flag) {
            throw std::domain_error("Неверный формат строки");
        }
    }
    TransNumber(
            double real, double realTransPart, std::string constTransPart
    ): a(real), b({ realTransPart, constTransPart }) {}     // Конструктор с явными параметрами

    auto getRealPart() const -> double;         // Получить действительную часть числа
    auto getTransRealPart() const -> double;    // Получить действительную часть трансцендентной части числа
    auto getConstant() const -> std::string;    // Получить константу трансцендентной части числа

    auto setRealPart() -> double&;              // Установить действительную часть числа
    auto setTransRealPart() -> double&;         // Установить действительную часть трансцендентной части числа
    auto setConstant() -> std::string&;         // Установить константу трансцендентной части числа

    // Операции сравнения
    auto operator==(const TransNumber& rhs) const -> bool;
    auto operator!=(const TransNumber& rhs) const -> bool;

    // Арифметические операции
    auto operator+(const TransNumber& rhs) const -> TransNumber;
    auto operator-(const TransNumber& rhs) const -> TransNumber;
    auto operator*(const TransNumber& rhs) const -> TransNumber;
    auto operator/(const TransNumber& rhs) const -> TransNumber;
};

auto operator>>(std::istream& in, TransNumber& n) -> std::istream&;         // Оператор ввода
auto operator<<(std::ostream& out, const TransNumber& n) -> std::ostream&;  // Оператор вывода

#endif /* TransNumber_hpp */
