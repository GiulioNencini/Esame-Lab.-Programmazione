cmake_minimum_required(VERSION 3.23)
project(Sistema_di_gioco_Not_The_End)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sistema_di_gioco_Not_The_End main.cpp
        Bag.cpp
        Bag.h
        NumberFunctions.h
        MainFunctions.h
        Player.cpp
        Player.h
        Master.cpp
        Master.h
        Hero.cpp
        Hero.h
        NumberFunctions.cpp)
