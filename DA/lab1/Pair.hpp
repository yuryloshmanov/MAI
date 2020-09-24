#ifndef Pair_hpp
#define Pair_hpp


template <class T, class U>
struct Pair {
    T first;
    U second;

    Pair();
    Pair(const T& first, const U& second);
};


template <class T, class U>
Pair<T,U>::Pair(): first(), second() {}


template <class T, class U>
Pair<T,U>::Pair(const T& first, const U& second): first(first), second(second) {}


#endif /* Pair_hpp */
