#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_NORMITEM_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_NORMITEM_H

#include <iostream>
#include "NumberAnswerFunctions.h"
using namespace std;

class NormItem{
protected:
    string name;
public:

    explicit NormItem(string name);
    virtual ~NormItem() = default;

    virtual const string &getName() const {
        return name;
    };

    virtual void printInfo() const{//NOTA: per gli item normali è "tipo" un getName, è utile soprattutto in ConsumableItem. Nel programma (funzione openItem() in Hero) almeno stamperà solo il nome se è normale, nome e quantità se è consumabile
        cout<<getName()<<endl;
    }

    virtual bool isConsumable() const{
        return false;
    }

    virtual int
    getAmount() const {//NOTA: questi ultimi tre metodi non si usano per questa classe. Sono utili solo in Consumable. Tuttavia non posso farli virtuali perché questa non può essere una classe astratta
        return 1;
    }

    virtual void setAmount(
            int a) {}//Altrimenti nella sezione di utilizzo oggetti (circa riga 630 di mainFunctions) mi dà problemi con il riferimento iteItem.

    virtual void accumulateAmount(
            int amount) {}//come per setAmount, altrimenti non potrei utilizzarlo in accumulateThisConsumableItem()

};

#endif //SISTEMA_DI_GIOCO_NOT_THE_END_NORMITEM_H
