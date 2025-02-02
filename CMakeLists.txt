cmake_minimum_required(VERSION 3.23)

project(Sistema_di_gioco_Not_The_End)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sistema_di_gioco_Not_The_End main.cpp
        NumberAnswerFunctions.h
        MainFunctions.h
        Player.cpp
        Master.cpp
        Hero.cpp
        NormItem.cpp
        ConsumableItem.cpp
        NumberAnswerFunction.cpp
)
#add_library(${CMAKE_Sistema_di_gioco_Not_The_End}_lib ${SOURCE_FILES})
#target_link_libraries(${CMAKE_Sistema_di_gioco_Not_The_End} ${CMAKE_Sistema_di_gioco_Not_The_End}_lib)