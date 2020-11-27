#ifndef sort_hpp
#define sort_hpp


#include "Pair.hpp"
#include "Vector.hpp"


namespace sort {


    template <class T, class U>
    auto countingSort(Vector<Pair<T, U>>& v, int upperBound) -> void {
        if (v.size() < 2) {
            return;
        }
        Vector<Pair<T, U>> res(v.size());
        Vector<size_t> table(upperBound + 1);
        for (size_t i = 0; i < v.size(); i++) {
            table[v[i].first]++;
        }
        for (size_t i = 1; i < table.size(); i++) {
            table[i] = table[i] + table[i - 1];
        }
        for (size_t i = v.size() - 1;; i--) {
            size_t j = table[v[i].first] - 1;
            table[v[i].first]--;
            res[j] = v[i];
            if (i == 0) {
                break;
            }
        }
        v = res;
    }


}


#endif /* sort_hpp */
