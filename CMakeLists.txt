cmake_minimum_required(VERSION 3.23)


project(Sistema_di_gioco_Not_The_End)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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
        NumberFunctions.cpp
        Item.cpp
        Item.h
        ConsumableItem.cpp
        ConsumableItem.h
        AbItem.h
)

add_executable(RunTest
        Test.cpp
)
target_link_libraries(RunTest gtest_main)
