//
//  main.cpp
//  lab1
//  Variant 15
//  Created by Юрий Лошманов on 04.09.2020.
//  Copyright © 2020 Юрий Лошманов. All rights reserved.
//

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


auto TransNumber::getRealPart() const -> double {
    return a;
}

auto TransNumber::getTransRealPart() const -> double {
    return b.data;
}

auto TransNumber::getConstant() const -> std::string {
    return b.constant;
}

auto TransNumber::setRealPart() -> double& {
    return a;
}

auto TransNumber::setTransRealPart() -> double& {
    return b.data;
}

auto TransNumber::setConstant() -> std::string& {
    return b.constant;
}

auto TransNumber::operator==(const TransNumber& rhs) const -> bool {
    return a == rhs.a && b.data == rhs.b.data && b.constant == rhs.b.constant;
}

auto TransNumber::operator!=(const TransNumber& rhs) const -> bool {
    return !(*this == rhs);
}

auto TransNumber::operator+(const TransNumber& rhs) const -> TransNumber {
    if (b.constant != rhs.b.constant) {
        throw std::logic_error("Константы должны быть идентичны");
    }
    
    return {a + rhs.a, b.data + rhs.b.data, b.constant};
}

auto TransNumber::operator-(const TransNumber& rhs) const -> TransNumber {
    if (b.constant != rhs.b.constant) {
        throw std::logic_error("Константы должны быть идентичны");
    }
    
    return {a - rhs.a, b.data - rhs.b.data, b.constant};
}

auto TransNumber::operator*(const TransNumber& rhs) const -> TransNumber {
    if (b.constant != rhs.b.constant) {
        throw std::logic_error("Константы должны быть идентичны");
    }
    
    return {a * rhs.a, b.data * rhs.b.data, b.constant};
}

auto TransNumber::operator/(const TransNumber& rhs) const -> TransNumber {
    if (b.constant != rhs.b.constant) {
        throw std::logic_error("Константы должны быть идентичны");
    }
    
    return {a / rhs.a, b.data / rhs.b.data, b.constant};
}

auto operator>>(std::istream& in, TransNumber& n) -> std::istream& {
    in >> n.setRealPart() >> n.setTransRealPart();
    in.ignore(1);
    in >> n.setConstant();
    return in;
}

auto operator<<(std::ostream& out, const TransNumber& n) -> std::ostream& {
    out << "(" << n.getRealPart() << ", " << n.getTransRealPart() << " * " << n.getConstant() << ")";
    return out;
}



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
