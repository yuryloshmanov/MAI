//
//  FigureFactory.hpp
//  lab7
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 10.11.2020.
//

#ifndef LAB7_FIGURE_FACTORY_HPP
#define LAB7_FIGURE_FACTORY_HPP


#include <string>


#include "Figures/Figure.hpp"
#include "Figures/Rectangle.hpp"
#include "Figures/Rhombus.hpp"
#include "Figures/Trapezoid.hpp"


template <class T>
class FigureFactory {
public:
    auto getFigure(FigureType figureType, std::vector<std::pair<double, double>> coord) -> std::shared_ptr<Figure<T>>;
};


template <class T>
auto FigureFactory<T>::getFigure(FigureType figureType, std::vector<std::pair<double, double>> coord) -> std::shared_ptr<Figure<T>> {
    switch (figureType) {
        case FigureType::Rectangle:
            return std::make_shared<Rectangle<T>>(coord);
        case FigureType::Rhombus:
            return std::make_shared<Rhombus<T>>(coord);
        case FigureType::Trapezoid:
            return std::make_shared<Trapezoid<T>>(coord);
    }
}


#endif //LAB7_FIGURE_FACTORY_HPP
