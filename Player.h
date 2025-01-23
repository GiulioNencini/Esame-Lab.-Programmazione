//
// Created by Giulio Nencini on 16/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H


#include <algorithm>
#include <memory>
#include "NumberFunctions.h"
#include "Bag.h"


class Player{
protected:
    Bag bag;
public:
    Player()=default;
    virtual ~Player()=default;

    virtual void extract(int e);

    virtual void setBag(int numW,int numB) = 0;
};

#endif //SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H
