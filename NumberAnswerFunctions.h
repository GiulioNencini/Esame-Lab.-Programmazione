//
// Created by Giulio Nencini on 16/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_NUMBERANSWERFUNCTIONS_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_NUMBERANSWERFUNCTIONS_H

#include <iostream>
#include <random>
#include <limits>
#include <vector>
using namespace std;

void verifyNumber(bool &error);

void insertNumber(unsigned int &value, bool &error);

unsigned int howExtract();

int getRandomWB();

int getRandom(int maxValue);

void yesOrNot(string &answer);


#endif //SISTEMA_DI_GIOCO_NOT_THE_END_NUMBERANSWERFUNCTIONS_H
