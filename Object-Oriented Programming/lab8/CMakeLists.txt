cmake_minimum_required(VERSION 3.17)
project(lab8)

set(CMAKE_CXX_STANDARD 20)

set(EXEC_NAME oop_exercise_08)
set(EXEC_SOURCES main.cpp Figures FigureFactory.hpp Server.hpp)

add_executable(${EXEC_NAME} ${EXEC_SOURCES})