//
// Created by Giulio Nencini on 16/01/2025.
//

#include "Master.h"

void Master::setBag(int numW, int numB) {
    bag.setWhite(numW);
    bag.setBlack(numB);
}

void Master::useBlack(int n) {
    if(usableBlack>=n) {
        usableBlack -= n;
        cout << "Al master sono rimasti " << usableBlack << " token neri" << endl;
    }
}

void Master::addBlack() {
    usableBlack++;
    cout<<"Il master ha ricevuto un token"<<endl;
}

void Master::addMultipleBlack(int value) {

        usableBlack+=value;
        cout<<"Il master ha ricevuto "<<value<<" token"<<endl;
    }