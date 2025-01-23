//
// Created by Giulio Nencini on 21/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_CONSUMABLEITEM_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_CONSUMABLEITEM_H

#include "AbItem.h"

class ConsumableItem : public AbItem{
    unsigned int amount;

public:

    ConsumableItem(string &name, unsigned int amount);
    ~ConsumableItem() override =default;

    unsigned int getAmount() const{
        return amount;
    }

    void setAmount(unsigned int a){
        amount=a;
    }

    /*const string &getName() const override{
        return name;
    };*/

    void getInfo() const override{
        cout<<getName()<<" x"<<getAmount()<<endl;
    }

};

#endif //SISTEMA_DI_GIOCO_NOT_THE_END_CONSUMABLEITEM_H
