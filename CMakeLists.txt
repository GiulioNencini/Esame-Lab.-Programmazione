cmake_minimum_required(VERSION 3.23)

project(Sistema_di_gioco_Not_The_End)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sistema_di_gioco_Not_The_End main.cpp
        Bag.cpp
        NumberFunctions.h
        MainFunctions.h
        Player.cpp
        Master.cpp
        Hero.cpp
        NumberFunctions.cpp
        Item.cpp
        ConsumableItem.cpp
)
