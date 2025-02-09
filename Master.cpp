#include "Master.h"

void Master::setBag(int numW, int numB) {
    setWhite(numW);
    setBlack(numB);
}

void Master::useBlack(int n) {
    if(usableBlack>=n)
        usableBlack -= n;
}

void Master::addUsableBlack(int value) {
    try {
        overflowPrevention(usableBlack, value);
        usableBlack+=value;
    } catch (std::exception &e) {
        cerr << e.what() << endl;
        usableBlack = std::numeric_limits<int>::max();
    }
}