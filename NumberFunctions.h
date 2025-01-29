//
// Created by Giulio Nencini on 16/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_NUMBERFUNCTIONS_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_NUMBERFUNCTIONS_H

#include <iostream>
#include <random>
#include <limits>
#include <vector>
using namespace std;

void verifyNumber(bool &error);

template <typename T>

void insertNumber(T &value, bool &error){//Per l'inserimento di un numero è questa che viene chiamata. Così risparmia la riscrittura continua del ciclo in essa contenuto. Basta solo dichiarare un flag fuori dalla funzione
    do{
        cin>>value;
        verifyNumber(error);
        if(!error && value<0){
            cerr<<"Il numero dev'essere positivo"<<endl;
            error=true;
        }
    }while(error);//fin quando il flag error non è dichiarato negativo da verifyNumber, sarà richiesto nuovamente di inserire un numero
}

int getRandomWB();

int getRandom(int maxValue);

int howExtract() ;


#endif //SISTEMA_DI_GIOCO_NOT_THE_END_NUMBERFUNCTIONS_H
