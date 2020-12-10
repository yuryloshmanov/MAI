#include <iostream>
#include <sstream>
#include <string>


#include "Document.hpp"


int main() {
    Document<double> document;
    for (std::string line; std::getline(std::cin, line);) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if (command == "create") {
            std::string str;
            if (!ss.eof() && (ss >> str)) {
                std::vector<std::pair<double, double>> coord;
                for (double x, y; ss >> x >> y;) {
                    coord.emplace_back(x, y);
                }
                FigureType figureType;
                if (str == "rect") {
                    figureType = FigureType::Rectangle;
                } else if (str == "rhomb") {
                    figureType = FigureType::Rhombus;
                } else if (str == "trapez") {
                    figureType = FigureType::Trapezoid;
                } else {
                    std::cerr << "invalid figure type" << std::endl;
                    continue;
                }
                document.createFigure(figureType, coord);
            } else {
                document.create();
            }
        } else if (command == "import") {
            std::string path;
            ss >> path;

            try {
                document.importData(std::move(path));
            } catch (std::runtime_error& error) {
                std::cerr << error.what() << std::endl;
            }
        } else if (command == "export") {
            std::string path;
            ss >> path;

            try {
                document.exportData(std::move(path));
            } catch (std::runtime_error& error) {
                std::cerr << error.what() << std::endl;
            }
        } else if (command == "delete") {
            document.deleteFigure();
        } else if (command == "print") {
            document.print();
        } else if (command == "undo") {
            document.undo();
        } else {
            std::cerr << "invalid command" << std::endl;
        }
    }
    return 0;
}
