#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_CONSUMABLEITEM_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_CONSUMABLEITEM_H

#include "NormItem.h"

class ConsumableItem : public NormItem{
    unsigned int amount;

public:

    ConsumableItem(string &name, unsigned int amount);
    ~ConsumableItem() override = default;

    unsigned int getAmount() const override{
        return amount;
    }

    void setAmount(unsigned int const a) override{
        amount=a;
    }

    void printInfo() const override{
        cout<<getName()<<" x"<<getAmount()<<endl;
    }

    bool isConsumable() const override{
        return true;
    }
};

#endif //SISTEMA_DI_GIOCO_NOT_THE_END_CONSUMABLEITEM_H
