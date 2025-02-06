#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H

#include <algorithm>
#include <memory>
#include "NumberAnswerFunctions.h"

struct Bag{
    int nWhite=0;
    int nBlack=0;
    int nUnknown=0;
    int blackExtracted=0;
    int whiteExtracted=0;
    vector<int> extractionVector;
};

class Player{
protected:
    Bag bag;
public:
    Player()=default;
    virtual ~Player()=default;

    virtual void extract(int e);

    void resetBag();

    void printExtracted() const;

    bool bagIsEmpty() const;

    virtual void setBag(int numW, int numB) = 0;

    void setWhite(const int nw){
        if (nw >= 0)
            bag.nWhite = nw;
        else
            throw runtime_error("Valore inatteso in setWhite");
    };

    void setBlack(const int nb){
        if (nb >= 0)
            bag.nBlack = nb;
        else
            throw runtime_error("Valore inatteso in setBlack");
    };

    void setUnknown(const int nu){
        if (nu >= 0)
            bag.nUnknown = nu;
        else
            throw runtime_error("Valore inatteso in setUnknown");
    };

    void setWhiteExtracted(const int nwe){
        if (nwe >= 0)
            bag.whiteExtracted = nwe;
        else
            throw runtime_error("Valore inatteso in setWhiteExtracted");
    };

    void setBlackExtracted(const int nbe){
        if (nbe >= 0)
            bag.blackExtracted = nbe;
        else
            throw runtime_error("Valore inatteso in setBlackExtracted");
    };


    int getSizeExVec() const{
        return bag.extractionVector.size();
    }

    int getWhiteFromBag() const{
        return bag.nWhite;
    }

    int getBlackFromBag() const{
        return bag.nBlack;
    }

    int getUnknownFromBag() const{
        return bag.nUnknown;
    }

    int getWhiteExtractedFromBag() const{
        return bag.whiteExtracted;
    }

    int getBlackExtractedFromBag() const{
        return bag.blackExtracted;
    }
};

#endif //SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H
