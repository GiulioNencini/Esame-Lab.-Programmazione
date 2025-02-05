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
        bag.nWhite=nw;
    };

    void setBlack(const int nb){
        bag.nBlack=nb;
    };

    void setUnknown(const int nu){
        bag.nUnknown=nu;
    };

    void setWhiteExtracted(const int nwe){
        bag.whiteExtracted=nwe;
    };

    void setBlackExtracted(const int nbe){
        bag.blackExtracted=nbe;
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
