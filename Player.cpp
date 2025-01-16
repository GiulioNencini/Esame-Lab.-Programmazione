//
// Created by Giulio Nencini on 16/01/2025.
//

#include "Player.h"

void Player::extract(int e) {

    int w=bag.getWhite();
    int b=bag.getBlack();
    bag.extractionVector.clear();

    bag.extractionVector.insert(bag.extractionVector.end(), w, 1);//per w volte inserisce 1
    bag.extractionVector.insert(bag.extractionVector.end(), b, 0);

    std::random_device s;
    std::mt19937 g(s());
    std::shuffle(bag.extractionVector.begin(), bag.extractionVector.end(),g);//mescolamento del sacchetto

    for (int i = 0; i < e; ++i) {
        if (bag.extractionVector.empty()) {
            std::cerr << "Non ci sono abbastanza token per estrarre.\n"<<endl;
            break;
        }

        int x = getRandomPos(bag.extractionVector.size());
        int temp = bag.extractionVector[x];
        bag.extractionVector.erase(bag.extractionVector.begin() + x);

        if (temp == 1) {//tener traccia degli estratti è utile per funzioni future
            bag.setWhite(bag.getWhite() - 1);
            bag.setWhiteExtracted(bag.getWhiteExtracted() + 1);
        } else {
            bag.setBlack(bag.getBlack() - 1);
            bag.setBlackExtracted(bag.getBlackExtracted() + 1);
        }
    }

    cout<<"Estratti: \n"<<bag.getWhiteExtracted()<<" bianchi\n"<<bag.getBlackExtracted()<<" neri\n"<<endl;
}