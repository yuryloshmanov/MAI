#include <iostream>

#include "Pair.hpp"
#include "Vector.hpp"
#include "sort.hpp"


template <class T, class U>
auto printVector(const Vector<Pair<T, U>>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i].first << " " << v[i].second << std::endl;
    }
}


auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    Vector<Pair<uint16_t, uint64_t>> v;
    for (Pair<uint16_t, uint64_t> p{}; std::cin >> p.first >> p.second;) {
        v.pushBack(p);
    }
    sort::countingSort(v, 65535);
    printVector(v);
    return 0;
}
