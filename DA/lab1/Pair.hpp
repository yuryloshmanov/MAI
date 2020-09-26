#ifndef Pair_hpp
#define Pair_hpp


template <class T, class U>
struct Pair {
    T first;
    U second;

    Pair();
    Pair(const T& first, const U& second);

    auto operator<(const Pair<T, U>& rhs) const -> bool;
};


template <class T, class U>
Pair<T, U>::Pair(): first(), second() {}


template <class T, class U>
Pair<T, U>::Pair(const T& first, const U& second): first(first), second(second) {}


template <class T, class U>
auto Pair<T, U>::operator<(const Pair<T, U>& rhs) const -> bool {
    return first < rhs.first;
}


#endif /* Pair_hpp */
