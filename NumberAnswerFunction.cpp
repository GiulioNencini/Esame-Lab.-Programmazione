#include "NumberAnswerFunctions.h"

void verifyNumber(int const value) {//funzione per l'inserimento sicuro di un numero positivo, usata nella successiva insertPositiveIntNumber.

    if (cin.fail()) // Se l'inserimento fallisce (non è un numero), resetta il flag di errore
    {
        cin.clear();// Ignora tutti i caratteri fino al prossimo newline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');//Ignora tutto l'input rimanente nel buffer senza limiti
        throw InvalidInputException();
    }
    else if(value < 0)
        throw NegativeNumberException();
}
//fixme numero attaccato a stringa bugga es:1qw
void insertPositiveIntNumber(int &value){//Per l'inserimento di un numero è questa che viene chiamata. Così risparmia la riscrittura continua del ciclo in essa contenuto. Basta solo dichiarare un flag fuori dalla funzione
    bool error;
    do {
        error=false;
        try {
            cin >> value;
            verifyNumber(value);
        }catch (const std::exception &e){
            cerr<<e.what()<<endl;
            error=true;
        }
    }while(error);//fin quando il flag error non è dichiarato negativo da verifyNumber, sarà richiesto nuovamente di inserire un numero
}

void insertPositiveIntNumberInInterval(int &value, int const min, int const max){
    insertPositiveIntNumber(value);
    if(value<min || value>max)
        throw OutOfRangeException();
}

void decrementNotOverZero(int const actualQuantity, int &decrementQuantity){
    insertPositiveIntNumber(decrementQuantity);
    if(decrementQuantity>actualQuantity)
        throw NotEnoughQuantity();
}

void addNotOverLimit(int const actualQuantity, int  const addingQuantity){
    if((std::numeric_limits<int>::max()-actualQuantity)<addingQuantity)
        throw OverflowDanger();
}

int howExtract() {
    int ex;
    bool error;
    do {
        error=false;
            cout << "Quanto vuoi estrarre?" << endl;
            try{
                insertPositiveIntNumberInInterval(ex, 1, 4);
            }
            catch (std::exception &e){
                cerr<<e.what()<<endl;
                error=true;
            }
    } while (error);
    return ex;
}

void vectorZeroOne(const vector<int> &v){
    for (int i : v){
        if (v[i] != 0 && v[i] != 1)
            throw runtime_error("ATTENZIONE: valori inattesi nel vettore estrazione");
    }
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