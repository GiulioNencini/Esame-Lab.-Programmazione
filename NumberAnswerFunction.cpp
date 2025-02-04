#include "NumberAnswerFunctions.h"

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

void insertNumber(unsigned int &value, bool &error){//Per l'inserimento di un numero è questa che viene chiamata. Così risparmia la riscrittura continua del ciclo in essa contenuto. Basta solo dichiarare un flag fuori dalla funzione
    do{
        cin>>value;
        verifyNumber(error);
        if(!error && value<0){
            cerr<<"Il numero dev'essere positivo"<<endl;
            error=true;
        }
    }while(error);//fin quando il flag error non è dichiarato negativo da verifyNumber, sarà richiesto nuovamente di inserire un numero
}

unsigned int howExtract() {
    unsigned int ex;
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

int getRandom(const int maxValue){
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distribuzione(0, maxValue-1);

    return distribuzione(gen);
}

void yesOrNot(string &answer){
    do{
        cin>>answer;
    } while (answer!="y" && answer!="n");
}