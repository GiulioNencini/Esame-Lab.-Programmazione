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

    /*for(int i=extractionVector.size()-1;i>=0;i--){
        extractionVector.erase(extractionVector.begin()+i);
    }*/
    cout<<"Il sacchetto e' stato resettato"<<endl;
}