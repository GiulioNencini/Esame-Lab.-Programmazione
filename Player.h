//
// Created by Giulio Nencini on 16/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H


#include <iostream>
#include <vector>
#include <algorithm>
#include "NumberFunctions.h"
#include "Bag.h"
using namespace std;


class Player{
protected:
    Bag bag;
public:
    Player()=default;
    ~Player()=default;

    virtual void extract(int e);

    virtual void setBag(int numW,int numB) = 0;
};





#endif //SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H
