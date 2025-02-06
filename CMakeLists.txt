cmake_minimum_required(VERSION 3.23)

project(Sistema_di_gioco_Not_The_End)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

set(SOURCE_FILES #variabile contenente la lista dei file sorgente del progetto.
        Player.cpp
        Master.cpp
        Hero.cpp
        NormItem.cpp
        ConsumableItem.cpp
        NumberAnswerFunction.cpp
)

add_library(core ${SOURCE_FILES})# Crea una libreria statica chiamata "core" usando i file sorgente specificati in SOURCE_FILES.

add_executable(Sistema_di_gioco_Not_The_End main.cpp #Crea l'eseguibile "Sistema_di_gioco_Not_The_End" usando main.cpp e gli altri header file.
        NumberAnswerFunctions.h
        MainFunctions.h
        ${SOURCE_FILES}
        ExceptionsFile.h
)

target_link_libraries(Sistema_di_gioco_Not_The_End core)# Collega la libreria "core" all'eseguibile "Sistema_di_gioco_Not_The_End". Questo permette all'eseguibile di utilizzare il codice definito nella libreria "core".