cmake_minimum_required(VERSION 3.5)

set(CXX_STANDARD 14)

add_subdirectory(./lib/googletest)# Questo fa sì che CMake processi il CMakeLists.txt presente nella cartella "googletest"

set(gtest_SOURCE_DIR, ./lib/googletest/)# Variabile che punta alla directory sorgente di Googletest.

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})#Aggiunge le directory include di Googletest al percorso di ricerca degli header. Questo fa sì che il compilatore possa trovare gli header file di gtest quando compila i test.

set(TEST_SOURCE_FILES
        mainRunTest.cpp
        ItemTest.cpp
        MasterTest.cpp
        HeroTest.cpp
        ExceptionsByNumberFunctionsTest.cpp
)

add_executable(mainRunTest ${TEST_SOURCE_FILES})

target_link_libraries(mainRunTest gtest gtest_main core)# Collega le librerie gtest, gtest_main e core all'eseguibile "mainRunTest". In particolare, core è la libreria del mio programma