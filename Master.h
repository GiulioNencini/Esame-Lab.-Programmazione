//
// Created by Giulio Nencini on 16/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_MASTER_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_MASTER_H

#include "Player.h"

class Master : public Player{
    int usableBlack=0;

public:
    Master()=default;
    ~Master() override =default;

    //il master per l'estrazione utilizza la funzione della classe player

    void setBag(int numW, int numB) override;

    void useBlack(int n);

    void addBlack();

    void addMultipleBlack(int value);

    void reset(){
        bag.reset();
    }

    int getUsableBlack() const{
        return usableBlack;
    }
};


#endif //SISTEMA_DI_GIOCO_NOT_THE_END_MASTER_H