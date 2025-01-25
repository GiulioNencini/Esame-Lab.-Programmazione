//
// Created by Giulio Nencini on 16/01/2025.
//

#include "Bag.h"

void Bag::reset() {
    nWhite=0;
    nBlack=0;
    nUnknown=0;
    whiteExtracted=0;
    blackExtracted=0;
    extractionVector.clear();
    cout<<"Il sacchetto e' stato resettato"<<endl;
}