//NOTA: In seguito a un errore di definizione multipla ho provato a trasferire le definizioni qui

#include "NumberFunctions.h"

void verifyNumber(bool &error) {//funzione per l'inserimento sicuro di un numero positivo, usata nella successiva insertNumber.

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