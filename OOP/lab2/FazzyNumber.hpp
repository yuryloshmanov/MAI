//
//  FazzyNumber.hpp
//  lab2
//  Группа М8О-206Б-19
//  Вариант 4
//  Created by Юрий Лошманов on 18.09.2020.
//  Copyright © 2020 Юрий Лошманов. All rights reserved.
//

#ifndef FazzyNumber_hpp
#define FazzyNumber_hpp


template <class T>
class FazzyNumber {
    T x, el, er;

public:
    FazzyNumber();
    FazzyNumber(T x, T el, T er);

    auto operator+(const FazzyNumber& rhs)  const -> FazzyNumber;
    auto operator-(const FazzyNumber& rhs)  const -> FazzyNumber;
    auto operator-()                        const -> FazzyNumber;
    auto operator*(const FazzyNumber& rhs)  const -> FazzyNumber;
    auto operator/(const FazzyNumber& rhs)  const -> FazzyNumber;

    auto operator<(const FazzyNumber& rhs)  const -> bool;
    auto operator>(const FazzyNumber& rhs)  const -> bool;
    auto operator==(const FazzyNumber& rhs) const -> bool;
    auto operator!=(const FazzyNumber& rhs) const -> bool;
};


template <class T>
FazzyNumber<T>::FazzyNumber(): x(T()), el(T()), er(T()) {}


template <class T>
FazzyNumber<T>::FazzyNumber(T x, T el, T er): x(x), el(el), er(er) {}


template <class T>
auto FazzyNumber<T>::operator+(const FazzyNumber& rhs) const -> FazzyNumber {
    return FazzyNumber<T>(x + rhs.x - el - rhs.el, x + rhs.x, x + rhs.x + er + rhs.er);
}


template <class T>
auto FazzyNumber<T>::operator-(const FazzyNumber& rhs) const -> FazzyNumber {
    return FazzyNumber<T>(x - rhs.x - el - rhs.el, x - rhs.x, x - rhs.x + er + rhs.er);
}


template <class T>
auto FazzyNumber<T>::operator-() const -> FazzyNumber {
    return FazzyNumber<T>(1 / (x + er), 1 / x, 1 / (x - el));
}


template <class T>
auto FazzyNumber<T>::operator*(const FazzyNumber& rhs) const -> FazzyNumber {
    return FazzyNumber<T>(
            x * rhs.x - rhs.x * el - x * rhs.el + el * rhs.el,
            x * rhs.x,
            x * rhs.x + rhs.x * el + el * rhs.el
           );
}

template <class T>
auto FazzyNumber<T>::operator/(const FazzyNumber& rhs) const -> FazzyNumber {
    return FazzyNumber<T>((x - el) / (rhs.x + rhs.er), x / rhs.x, (x + er) / (rhs.x - rhs.el));
}


template <class T>
auto FazzyNumber<T>::operator<(const FazzyNumber& rhs) const -> bool {
    return x < rhs.x;
}


template <class T>
auto FazzyNumber<T>::operator>(const FazzyNumber& rhs) const -> bool {
    return x > rhs.x;
}


template <class T>
auto FazzyNumber<T>::operator==(const FazzyNumber& rhs) const -> bool {
    return x == rhs.x;
}


template <class T>
auto FazzyNumber<T>::operator!=(const FazzyNumber& rhs) const -> bool {
    return x != rhs.x;
}


#endif /* FazzyNumber_hpp */
