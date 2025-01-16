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

void verifyNumber(bool &error){//funzione per l'inserimento sicuro di un numero in generale, usata nella successiva insertNumber

    if (cin.fail()) // Se l'inserimento fallisce (non è un numero), resetta il flag di errore
    {
        cin.clear();// Ignora tutti i caratteri fino al prossimo newline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');//Ignora tutto l'input rimanente nel buffer senza limiti
        error=true;
        cerr<<"Inserisci un numero"<<endl;
    }
    else
        error=false;
}

template <typename T>

void insertNumber(T &value, bool &error){//è questa che viene chiamata
    do{
        cin>>value;
        verifyNumber(error);
    }while(error);//fin quando il flag error non è dichiarato negativo da verifyNumber, sarà richiesto nuovamente di inserire un numero
}

int getRandomPos(int max){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distribuzione(0, max-1);

    return distribuzione(gen);
}

int getRandomWB(){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distribuzione(0, 1);

    return distribuzione(gen);
}

int getRandom(int maxValue){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distribuzione(0, maxValue-1);

    return distribuzione(gen);
}


int howExtract() {
    int ex;
    do {
        cout << "Quanto vuoi estrarre?" << endl;
        bool e;
        insertNumber(ex, e);
        if (ex < 1 || ex > 4)
            cout << "Valore non valido (dev'essere tra 1 e 4)" << endl;

    } while (ex < 1 || ex > 4);
    return ex;
}


#endif //SISTEMA_DI_GIOCO_NOT_THE_END_NUMBERFUNCTIONS_H
