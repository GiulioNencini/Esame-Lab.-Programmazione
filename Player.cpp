#include "Player.h"

void Player::extract(int e) {

    if (e < 0)
        throw runtime_error("Valore inatteso in extract");

    int w=getWhiteFromBag();
    int b=getBlackFromBag();
    bag.extractionVector.clear();

    bag.extractionVector.insert(bag.extractionVector.end(), w, 1);//per w volte inserisce 1
    bag.extractionVector.insert(bag.extractionVector.end(), b, 0);

    vectorZeroOne(bag.extractionVector);//controlla mediante eccezione che ci siano tutti 0 e 1

    std::random_device s;
    std::mt19937 g(s());
    std::shuffle(bag.extractionVector.begin(), bag.extractionVector.end(),g);//mescolamento del sacchetto

    for (int i = 0; i < e; ++i) {
        if (bag.extractionVector.empty())//cerr << "Estrazione terminata: non ci sono abbastanza token per estrarre.\n"<<endl;
            break;

        int x = getRandom(bag.extractionVector.size());
        int temp = bag.extractionVector[x];
        bag.extractionVector.erase(bag.extractionVector.begin() + x);

        if (temp == 1) {//tener traccia degli estratti è utile per funzioni future
            setWhite(getWhiteFromBag() - 1);
            setWhiteExtracted(getWhiteExtractedFromBag() + 1);
        } else {
            setBlack(getBlackFromBag() - 1);
            setBlackExtracted(getBlackExtractedFromBag() + 1);
        }
    }
    if(!bag.extractionVector.empty())
        vectorZeroOne(bag.extractionVector);
}

void Player::printExtracted() const{
    cout<<"Estratti: \n"<<getWhiteExtractedFromBag()<<" bianchi\n"<<getBlackExtractedFromBag()<<" neri\n"<<endl;
}

bool Player::bagIsEmpty() const{
    if (bag.extractionVector.empty())
        return true;
    else
        return false;
}

void Player::resetBag(){
    bag.nWhite=0;
    bag.nBlack=0;
    bag.nUnknown=0;
    bag.whiteExtracted=0;
    bag.blackExtracted=0;
    bag.extractionVector.clear();
}