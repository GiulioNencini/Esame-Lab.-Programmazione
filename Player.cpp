#include "Player.h"

void Player::extract(unsigned const int e) {

    unsigned int w=getWhiteFromBag();
    unsigned int b=getBlackFromBag();
    bag.extractionVector.clear();

    bag.extractionVector.insert(bag.extractionVector.end(), w, 1);//per w volte inserisce 1
    bag.extractionVector.insert(bag.extractionVector.end(), b, 0);

    std::random_device s;
    std::mt19937 g(s());
    std::shuffle(bag.extractionVector.begin(), bag.extractionVector.end(),g);//mescolamento del sacchetto

    for (int i = 0; i < e; ++i) {
        if (bag.extractionVector.empty()) {
            std::cerr << "Estrazione terminata: non ci sono abbastanza token per estrarre.\n"<<endl;
            break;
        }

        unsigned int x = getRandom(bag.extractionVector.size());
        unsigned int temp = bag.extractionVector[x];
        bag.extractionVector.erase(bag.extractionVector.begin() + x);

        if (temp == 1) {//tener traccia degli estratti è utile per funzioni future
            setWhite(getWhiteFromBag() - 1);
            setWhiteExtracted(getWhiteExtractedFromBag() + 1);
        } else {
            setBlack(getBlackFromBag() - 1);
            setBlackExtracted(getBlackExtractedFromBag() + 1);
        }
    }
    //printExtracted();
}

void Player::printExtracted() const{
    cout<<"Estratti: \n"<<getWhiteExtractedFromBag()<<" bianchi\n"<<getBlackExtractedFromBag()<<" neri\n"<<endl;
}

void Player::resetBag(){
    bag.nWhite=0;
    bag.nBlack=0;
    bag.nUnknown=0;
    bag.whiteExtracted=0;
    bag.blackExtracted=0;
    bag.extractionVector.clear();
}