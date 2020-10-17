//
//  Figure.hpp
//  lab3
//
//  Created by Юрий Лошманов on 16.10.2020.
//

#ifndef Figure_hpp
#define Figure_hpp


#include <utility>


class Figure {
public:
    virtual auto geometriсСenter() -> std::pair<double, double> = 0;
    virtual auto square() -> double = 0;
    virtual ~Figure() {};
};


#endif /* Figure_hpp */

