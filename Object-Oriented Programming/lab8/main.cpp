//
//  main.cpp
//  lab8
//  Группа М8О-206Б-19
//  Вариант 11
//  Created by Юрий Лошманов on 21.11.2020.
//

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <mutex>
#include <thread>
#include <sstream>
#include <fstream>


#include "Figures/Figure.hpp"
#include "FigureFactory.hpp"
#include "Server.hpp"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "invalid parameters" << std::endl;
        exit(1);
    }

    int64_t buffSize = std::atoi(argv[1]);
    if (buffSize <= 0) {
        std::cerr << "invalid buffer size" << std::endl;
        exit(2);
    }

    int buffIndex = 0;
    std::ofstream of;

    Server<Figure<double>>::get().register_subscriber([&](const Figure<double> &val) {
        std::cout << val << std::endl;
    });

    Server<Figure<double>>::get().register_subscriber([&](const Figure<double> &val) {
        of <<  val << std::endl;
    });

    FigureFactory<double> ff;
    std::queue<Figure<double>> q;

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
                Figure<double> fig = *ff.getFigure(figureType, coord);
                q.push(fig);
                if (q.size() == buffSize) {
                    std::string buffName = "output_" + std::to_string(buffIndex) + ".txt";
                    of.open(buffName, std::ios::out);

                    std::thread th([]() {
                        Server<Figure<double>>::get().run();
                    });

                    for (int i = 0; i < buffSize; ++i) {
                        auto val = q.front();
                        q.pop();
                        Server<Figure<double>>::get().publish(val);
                    }
                    
                    Server<Figure<double>>::get().stop();
                    th.join();
                    q = std::queue<Figure<double>>();
                    of.close();

                    buffIndex++;
                }
            }
        } else {
            std::cerr << "invalid command" << std::endl;
        }
    }
    return 0;
}
