#include "Master.h"

void Master::setBag( const int numW, const int numB) {
    setWhite(numW);
    setBlack(numB);
}

void Master::useBlack(const int n) {
    if(usableBlack>=n)
        usableBlack -= n;
}

void Master::addUsableBlack(const int value) {
        usableBlack+=value;
}