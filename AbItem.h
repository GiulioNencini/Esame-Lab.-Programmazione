//
// Created by Giulio Nencini on 22/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_ABITEM_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_ABITEM_H

#include <iostream>
using namespace std;

class AbItem{

protected:
    string name;
public:
    explicit AbItem(string &name) : name(name){};
    virtual ~AbItem()=default;

    virtual const string &getName() const{
        return name;
    };

    virtual void getInfo() const =0;

    /*virtual unsigned int getAmount() const =0;

    virtual void setAmount(unsigned int a)=0;*/

};

#endif //SISTEMA_DI_GIOCO_NOT_THE_END_ABITEM_H