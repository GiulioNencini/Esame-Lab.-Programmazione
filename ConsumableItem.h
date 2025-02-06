#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_CONSUMABLEITEM_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_CONSUMABLEITEM_H

#include "NormItem.h"

class ConsumableItem : public NormItem{
    int amount;

public:

    ConsumableItem(string &name, int amount);
    ~ConsumableItem() override = default;

    int getAmount() const override{
        return amount;
    }

    void setAmount(int const a) override{
        if (a >= 0)
            amount = a;
        else
            throw runtime_error("Valore inatteso in setAmount");
    }

    void printInfo() const override{
        cout<<getName()<<" x"<<getAmount()<<endl;
    }

    bool isConsumable() const override{
        return true;
    }
};

#endif //SISTEMA_DI_GIOCO_NOT_THE_END_CONSUMABLEITEM_H
