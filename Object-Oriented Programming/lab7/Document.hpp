//
//  Document.hpp
//  lab7
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 10.11.2020.
//

#ifndef LAB7_DOCUMENT_HPP
#define LAB7_DOCUMENT_HPP


#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <utility>


#include "FigureFactory.hpp"


enum class Operation {
    createFigure,
    deleteFigure,
};


template <class T>
class Document {
    FigureFactory<T> figureFactory;
    std::vector<std::shared_ptr<Figure<T>>> data;
    std::stack<std::pair<Operation, std::shared_ptr<Figure<T>>>> operations;

public:
    auto create() -> void;
    auto importData(std::string&& path) -> void;
    auto exportData(std::string&& path) -> void;
    auto createFigure(FigureType figureType, std::vector<std::pair<double, double>> coord) noexcept -> void;
    auto deleteFigure() -> void;
    auto print() const -> void;
    auto undo() noexcept -> void;
};


template<class T>
auto Document<T>::create() -> void {
    data.clear();
    operations = std::stack<std::pair<Operation, std::shared_ptr<Figure<T>>>>();
}


template<class T>
auto Document<T>::createFigure(FigureType figureType, std::vector<std::pair<double, double>> coord) noexcept -> void {
    try {
        data.push_back(figureFactory.getFigure(figureType, coord));
        operations.push(std::make_pair(Operation::createFigure, nullptr));
    } catch (std::logic_error& error) {
        std::cerr << error.what() << std::endl;
    }
}


template<class T>
auto Document<T>::deleteFigure() -> void {
    if (!data.empty()) {
        operations.push(std::make_pair(Operation::deleteFigure, *data.rbegin()));
        data.pop_back();
    }
}


template<class T>
auto Document<T>::print() const -> void {
    for (const auto& figure: data) {
        std::cout << *figure << std::endl;
    }
}

template<class T>
auto Document<T>::importData(std::string&& path) -> void {
    std::ifstream stream(path, std::ios::in | std::ios::binary);

    if (!stream) {
        throw std::runtime_error("can't open file");
    }

    data.clear();
    operations = std::stack<std::pair<Operation, std::shared_ptr<Figure<T>>>>();

    auto size = data.size();

    stream.read((char *)&size, sizeof size);

    for (size_t i = 0; i < size; i++) {
        Figure<T> figure;
        stream >> figure;
        data.push_back(std::make_shared<Figure<T>>(figure));
    }
}

template<class T>
auto Document<T>::exportData(std::string&& path) -> void {
    std::ofstream stream(path, std::ios::out | std::ios::binary);

    if (stream.bad()) {
        throw std::runtime_error("can't open file");
    }

    auto size = data.size();
    stream.write((const char *)&size, sizeof size);

    for (const auto& figure: data) {
        stream << *figure;
    }
}

template<class T>
auto Document<T>::undo() noexcept -> void {
    if (!operations.empty()) {
        auto op = operations.top();
        if (op.first == Operation::createFigure) {
            data.pop_back();
        } else {
            data.push_back(op.second);
        }
        operations.pop();
    }
}


#endif //LAB7_DOCUMENT_HPP
