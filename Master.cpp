//
// Created by Giulio Nencini on 16/01/2025.
//

#include "Master.h"

void Master::setBag( const unsigned int numW, const unsigned  int numB) {
    setWhite(numW);
    setBlack(numB);
}

void Master::useBlack(const unsigned int n) {
    if(usableBlack>=n)
        usableBlack -= n;
}

void Master::addUsableBlack(const unsigned int value) {
        usableBlack+=value;
}