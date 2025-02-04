#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H

#include <algorithm>
#include <memory>
#include "NumberAnswerFunctions.h"

struct Bag{
    unsigned int nWhite=0;
    unsigned int nBlack=0;
    unsigned int nUnknown=0;
    unsigned int blackExtracted=0;
    unsigned int whiteExtracted=0;
    vector<unsigned int> extractionVector;
};

class Player{
protected:
    Bag bag;
public:
    Player()=default;
    virtual ~Player()=default;

    virtual void extract(unsigned int e);

    void resetBag();

    void printExtracted() const;

    virtual void setBag( unsigned int numW, unsigned int numB) = 0;

    void setWhite(const unsigned int nw){
        bag.nWhite=nw;
    };

    void setBlack(const unsigned int nb){
        bag.nBlack=nb;
    };

    void setUnknown(const unsigned int nu){
        bag.nUnknown=nu;
    };

    void setWhiteExtracted(const unsigned int nwe){
        bag.whiteExtracted=nwe;
    };

    void setBlackExtracted(const unsigned int nbe){
        bag.blackExtracted=nbe;
    };


    int getSizeExVec() const{
        return bag.extractionVector.size();
    }

    unsigned int getWhiteFromBag() const{
        return bag.nWhite;
    }

    unsigned int getBlackFromBag() const{
        return bag.nBlack;
    }

    unsigned int getUnknownFromBag() const{
        return bag.nUnknown;
    }

    unsigned int getWhiteExtractedFromBag() const{
        return bag.whiteExtracted;
    }

    unsigned int getBlackExtractedFromBag() const{
        return bag.blackExtracted;
    }
};

#endif //SISTEMA_DI_GIOCO_NOT_THE_END_PLAYER_H
