//
//  FuzzyNumber.hpp
//  lab2
//  Группа М8О-206Б-19
//  Вариант 4
//  Created by Юрий Лошманов on 18.09.2020.
//  Copyright © 2020 Юрий Лошманов. All rights reserved.
//

#ifndef FuzzyNumber_hpp
#define FuzzyNumber_hpp

#include <iostream>
#include <iomanip>
#include <sstream>

template <class T>
class FuzzyNumber {
    T x, el, er;

public:
    FuzzyNumber();
    FuzzyNumber(T x, T el, T er);

    auto operator+(const FuzzyNumber& rhs)  const -> FuzzyNumber;
    auto operator-(const FuzzyNumber& rhs)  const -> FuzzyNumber;
    auto operator-()                        const -> FuzzyNumber;
    auto operator*(const FuzzyNumber& rhs)  const -> FuzzyNumber;
    auto operator/(const FuzzyNumber& rhs)  const -> FuzzyNumber;

    auto operator<(const FuzzyNumber& rhs)  const -> bool;
    auto operator>(const FuzzyNumber& rhs)  const -> bool;
    auto operator==(const FuzzyNumber& rhs) const -> bool;
    auto operator!=(const FuzzyNumber& rhs) const -> bool;

    friend auto operator>>(std::istream& in, FuzzyNumber& fz) -> std::istream&;
    friend auto operator<<(std::ostream& out, FuzzyNumber& fz) -> std::ostream&;
};

auto operator""_fz(const char* str, size_t) -> FuzzyNumber<double>;


template <class T>
FuzzyNumber<T>::FuzzyNumber(): x(T()), el(T()), er(T()) {}


template <class T>
FuzzyNumber<T>::FuzzyNumber(T x, T el, T er): x(x), el(el), er(er) {}


template <class T>
auto FuzzyNumber<T>::operator+(const FuzzyNumber& rhs) const -> FuzzyNumber {
    return FuzzyNumber<T>(x + rhs.x - el - rhs.el, x + rhs.x, x + rhs.x + er + rhs.er);
}


template <class T>
auto FuzzyNumber<T>::operator-(const FuzzyNumber& rhs) const -> FuzzyNumber {
    return FuzzyNumber<T>(x - rhs.x - el - rhs.el, x - rhs.x, x - rhs.x + er + rhs.er);
}


template <class T>
auto FuzzyNumber<T>::operator-() const -> FuzzyNumber {
    return FuzzyNumber<T>(1 / (x + er), 1 / x, 1 / (x - el));
}


template <class T>
auto FuzzyNumber<T>::operator*(const FuzzyNumber& rhs) const -> FuzzyNumber {
    return FuzzyNumber<T>(
            x * rhs.x - rhs.x * el - x * rhs.el + el * rhs.el,
            x * rhs.x,
            x * rhs.x + rhs.x * el + el * rhs.el
           );
}

template <class T>
auto FuzzyNumber<T>::operator/(const FuzzyNumber& rhs) const -> FuzzyNumber {
    return FuzzyNumber<T>((x - el) / (rhs.x + rhs.er), x / rhs.x, (x + er) / (rhs.x - rhs.el));
}


template <class T>
auto FuzzyNumber<T>::operator<(const FuzzyNumber& rhs) const -> bool {
    return x < rhs.x;
}


template <class T>
auto FuzzyNumber<T>::operator>(const FuzzyNumber& rhs) const -> bool {
    return x > rhs.x;
}


template <class T>
auto FuzzyNumber<T>::operator==(const FuzzyNumber& rhs) const -> bool {
    return x == rhs.x;
}


template <class T>
auto FuzzyNumber<T>::operator!=(const FuzzyNumber& rhs) const -> bool {
    return x != rhs.x;
}


template<class T>
auto operator>>(std::istream& in, FuzzyNumber<T>& fz) -> std::istream& {
    in >> fz.x;
    if (in.peek() == ',') {
        in.ignore(1);
    }
    in >> std::ws >> fz.el;
    if (in.peek() == ',') {
        in.ignore(1);
    }
    in >> std::ws >> fz.er;
}


template <class T>
auto operator<<(std::ostream& out, FuzzyNumber<T>& fz) -> std::ostream& {
    out << fz.x << ", " << fz.el << ", " << fz.er;
    return out;
}


auto operator""_fz(const char* str, size_t) -> FuzzyNumber<double> {
    std::stringstream ss(str);
    FuzzyNumber<double> fz;
    ss >> fz;
    return fz;
}


#endif /* FuzzyNumber_hpp */
