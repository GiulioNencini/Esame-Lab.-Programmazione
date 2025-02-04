cmake_minimum_required(VERSION 3.5)

set(CXX_STANDARD 14)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set(TEST_SOURCE_FILES
        mainRunTest.cpp
        ItemTest.cpp
        MasterTest.cpp
        HeroTest.cpp
)
add_executable(mainRunTest ${TEST_SOURCE_FILES})
target_link_libraries(mainRunTest gtest gtest_main core)