cmake_minimum_required(VERSION 3.23)
project(Sistema_di_gioco_Not_The_End)

set(CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(test)

set(SOURCE_FILES
        AbItem.h
        Bag.h
        Bag.cpp
        ConsumableItem.h
        ConsumableItem.cpp
        Hero.h
        Hero.cpp
        Item.h
        Item.cpp
        MainFunctions.h
        Master.h
        Master.cpp
        NumberFunctions.h
        NumberFunctions.cpp
        Player.h
        Player.cpp
)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)