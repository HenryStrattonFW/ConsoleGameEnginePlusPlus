cmake_minimum_required(VERSION 3.23)
project(ConsoleGameEnginePlusPlus)

set(CMAKE_CXX_STANDARD 20)

add_executable(ConsoleGameEnginePlusPlus main.cpp src/core/GameConsole.cpp include/core/GameConsole.h src/core/Canvas.cpp include/core/Canvas.h include/core/Colours.h src/core/Input.cpp include/core/Input.h include/core/GameCartridge.h src/debug/TestCartridge.cpp include/debug/TestCartridge.h src/core/GameCartridge.cpp src/core/Utils.cpp include/core/Utils.h src/debug/FileLogger.cpp include/debug/FileLogger.h include/debug/Logger.h src/debug/Debug.cpp include/debug/Debug.h)
