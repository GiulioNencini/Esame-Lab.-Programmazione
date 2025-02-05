#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_NUMBERANSWERFUNCTIONS_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_NUMBERANSWERFUNCTIONS_H

#include "ExeptionsFile.h"
#include <random>
#include <limits>
#include <vector>
using namespace std;

void verifyNumber(int value);

void insertPositiveIntNumber(int &value);

void insertPositiveIntNumberInInterval(int &value, int min, int max);

void decrementNotOverZero(int actualQuantity, int &decrementQuantity);

void addNotOverLimit(int actualQuantity, int addingQuantity);

int howExtract();

void vectorZeroOne(const vector<int> &v);

int getRandomWB();

int getRandom(int maxValue);

void yesOrNot(string &answer);


#endif //SISTEMA_DI_GIOCO_NOT_THE_END_NUMBERANSWERFUNCTIONS_H
