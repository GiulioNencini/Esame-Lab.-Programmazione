//
// Created by Giulio Nencini on 21/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_ITEM_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_ITEM_H

#include "AbItem.h"

class Item : public AbItem{
public:

    explicit Item(string &name);
    ~Item() override =default;

    void getInfo() const override{
        cout<<getName()<<endl;
    }

};

#endif //SISTEMA_DI_GIOCO_NOT_THE_END_ITEM_H
