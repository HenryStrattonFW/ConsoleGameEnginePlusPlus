cmake_minimum_required(VERSION 3.23)
project(ConsoleGameEnginePlusPlus)

set(CMAKE_CXX_STANDARD 20)

add_executable(ConsoleGameEnginePlusPlus main.cpp src/ConsoleGame.cpp include/ConsoleGame.h src/Canvas.cpp include/Canvas.h include/Colours.h src/Input.cpp include/Input.h)
