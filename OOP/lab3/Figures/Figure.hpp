//
//  Figure.hpp
//  lab3
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 16.10.2020.
//

#ifndef Figure_hpp
#define Figure_hpp


#include <utility>


class Figure {
public:
    virtual auto geometricCenter() -> std::pair<double, double> = 0;
    virtual auto square() -> double = 0;
    virtual ~Figure() = default;
};


#endif /* Figure_hpp */

