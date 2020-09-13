//
//  TransNumber.cpp
//  lab1
//  Variant 15
//  Created by Юрий Лошманов on 04.09.2020.
//  Copyright © 2020 Юрий Лошманов. All rights reserved.
//

#include "TransNumber.hpp"

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
    if (rhs.a == 0 || rhs.b.data == 0) {
        throw std::logic_error("Деление на ноль недопустимо");
    }
    return {a / rhs.a, b.data / rhs.b.data, b.constant};
}

auto operator>>(std::istream& in, TransNumber& n) -> std::istream& {
    bool flag = true;
    flag = flag && (in >> n.setRealPart()) && (in >> n.setTransRealPart());
    in.ignore(1);
    flag = flag && (in >> n.setConstant());
    if (!flag) {
        throw std::domain_error("Ошибка в ходе парсинга чисел");
    }
    return in;
}

auto operator<<(std::ostream& out, const TransNumber& n) -> std::ostream& {
    out << "(" << n.getRealPart() << ", " << n.getTransRealPart() << " * " << n.getConstant() << ")";
    return out;
}
