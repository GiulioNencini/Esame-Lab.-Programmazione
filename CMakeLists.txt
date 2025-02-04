cmake_minimum_required(VERSION 3.23)#todo chiedere spiegazione codice

project(Sistema_di_gioco_Not_The_End)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

set(SOURCE_FILES
        Player.cpp
        Master.cpp
        Hero.cpp
        NormItem.cpp
        ConsumableItem.cpp
        NumberAnswerFunction.cpp
)

add_library(core ${SOURCE_FILES})

add_executable(Sistema_di_gioco_Not_The_End main.cpp
        NumberAnswerFunctions.h
        MainFunctions.h
        ${SOURCE_FILES}
)

target_link_libraries(Sistema_di_gioco_Not_The_End core)