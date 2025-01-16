//
// Created by Giulio Nencini on 16/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_BAG_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_BAG_H

#include <iostream>
#include <vector>
using namespace std;

class Bag{
    int nWhite=0;
    int nBlack=0;
    int nUnknown=0;
    int blackExtracted=0;
    int whiteExtracted=0;
public:
    vector<int> extractionVector;

    Bag()=default;
    ~Bag()=default;

    void reset();

    void setBlackExtracted(int value){
        blackExtracted=value;
    }

    int getBlackExtracted() const{
        return blackExtracted;
    }

    void setWhiteExtracted(int value){
        whiteExtracted=value;
    }

    int getWhiteExtracted() const{
        return whiteExtracted;
    }

    void setWhite(int nw){
        nWhite=nw;
    }

    void setBlack(int nb){
        nBlack=nb;
    }

    void setUnknown(int nu){
        nUnknown=nu;
    }

    int getWhite() const {
        return nWhite;
    }

    int getBlack() const {
        return nBlack;
    }

    int getUnknown() const {
        return nUnknown;
    }

};



#endif //SISTEMA_DI_GIOCO_NOT_THE_END_BAG_H
