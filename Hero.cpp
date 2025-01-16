//
// Created by Giulio Nencini on 16/01/2025.
//
#include "Hero.h"

Hero::Hero(std::string nameCharacter, std::string namePlayer, std::string myRisk, unsigned int numberPlayer)  : nameCharacter(std::move(nameCharacter)), namePlayer(std::move(namePlayer)), myRisk(std::move(myRisk)), numberPlayer(numberPlayer) {
    cout<<"L'eroe "<<this->nameCharacter<<" si e' unito al party"<<endl;
}


void Hero::getIdentity() const {
    cout<<"Personaggio "<<numberPlayer<<"         Impersonato da "<<namePlayer<<endl;
    cout<<nameCharacter<<endl;
    cout<<"Disposto a tutto per: "<<myRisk<<endl;
}

void Hero::setBag(int numW, int numB) {
    if(!confusion){//differentemente a quello del master, il settaggio del sacchetto di un eroe può essere condizionato dell'attributo confusion
        bag.setWhite(numW);
        bag.setBlack(numB);
        cout<<"Ci sono "<<bag.getWhite()<<" token bianchi e " <<bag.getBlack()<<" token neri"<<endl;
    }
    else{
        int nW=0, nB=0;
        bag.setUnknown(numW);
        for(int i=0;i<bag.getUnknown();i++){
            int x = getRandomWB();
            if(x)
                nW++;
            else
                nB++;
        }

        bag.setWhite(nW);
        bag.setBlack(numB+nB);
        cout<<"Ci sono "<<numB<<" token neri e " <<bag.getUnknown()<<" token sconosciuti"<<endl;
    }
}

void Hero::extract(Master &theMaster) {

    bool isDangerous=false;
    int danger=6;//impossibile da raggiungere
    setDanger(danger,isDangerous);//vedi funzione sotto


    if(!adrenaline){ //Meccanica dell'adrenalina
        cout<<"Adrenalina non e' attivo"<<endl;
        if(isDangerous) {
            cout << "Il pericolo e' " << danger << endl;
        }
        int exVal=howExtract();
        Player::extract(exVal);//differentemente al master, l'eroe deve passare tutti questi altri controlli quando estrae
        if(isDangerous)
            goOffScene(danger, bag.getBlackExtracted());//verifica del fuori-scena. Vedi la seconda funzione dopo questa
        if(!outScene) {
            risk(5 - exVal);//rischio, il valore è pari ai token rimanenti. Vedi la terza funzione dopo questa
            if(isDangerous)
                goOffScene(danger,bag.getBlackExtracted());//verifica del fuori-scena post rischio
        }
    }
    else{//se c'è adrenalina
        cout<<"Adrenalina e' attivo"<<endl;
        if(isDangerous) {
            cout << "Il pericolo e' " << danger << endl;
        }
        Player::extract(4);
        if(isDangerous)
            goOffScene(danger,bag.getBlackExtracted());
        if(!outScene) {
            risk(1);
            if(isDangerous)
                goOffScene(danger,bag.getBlackExtracted());
        }
    }

    adrenaline = false;
    confusion = false;//dopo l'estrazione tornano automaticamente a falso

    if(!outScene) {//spartizione neri, nel caso non vada fuori scena


        if (bag.getBlackExtracted() != 0) {
            cout << "Hai " << bag.getBlackExtracted() << " token neri da smaltire" << endl;
            blackTokenPartition(theMaster,false);//Vedi la quarta funzione dopo questa. Il flag si riferisce all'essere o meno andato fuori scena
            cout << "Spartizione completata" << endl;
        }
    }
    else
        blackTokenPartition(theMaster,true);
    bag.reset();//una volta completata la spartizione dei neri il sacchetto può essere resettato
}

void Hero::setDanger(int &danger, bool &isDangerous) {
    string answer;
    do {
        cout << "E' pericoloso? y/n"<<endl;
        cin >> answer;
    } while (answer!="y" && answer!="n");
    if(answer=="y"){
        isDangerous=true;
        do {
            cout << "Quanto e' pericoloso?"<<endl;
            bool e;
            insertNumber(danger, e);
        }while(danger>5 || danger<1);//Meccanica del pericolo
    }
    else
        isDangerous=false;
}

void Hero::goOffScene(int danger, int eb) {
    if(eb>=danger) {
        setOutScene(true);
        cout<<getNameCharacter()<<" e' uscito di scena! I suoi token neri andranno tutti al master..."<<endl;
    }
    else{
        int x= getRandom(3);
        if(x==1)
            cout<<getNameCharacter()<<" ha scampato il pericolo..."<<endl;
        else if(x==2)
            cout<<getNameCharacter()<<" ha avuto fortuna..."<<endl;
        else if(x==3)
            cout<<"Ti e' andata bene "<<getNameCharacter()<<endl;
    }
}

void Hero::risk(int remain) {
    string answer;
    do {
        cout << "Vuoi rischiare? y/n" << endl;
        cin >> answer;
    } while (answer!="y" && answer!="n");
    if(answer=="y")
        Player::extract(remain);
}

void Hero::blackTokenPartition(Master &theMaster, bool isOutScene) {
    if(!isOutScene) {
        string answer;//scegliere a chi dare il token
        bool exitFlag=false;
        do {

            if (!adrenaline && !confusion) {
                do {
                    cout << "Scegli tra: adrenalina (a), confusione(c) o master(m)" << endl;
                    cin >> answer;
                } while (answer != "a" && answer != "c" && answer != "m");
            } else if (!adrenaline) {
                do {
                    cout << "Scegli tra: adrenalina(a) o master(m)" << endl;
                    cin >> answer;
                } while (answer != "a" && answer != "m");
            } else if (!confusion) {
                do {
                    cout << "Scegli tra: confusione(c) o master(m)" << endl;
                    cin >> answer;
                } while (answer != "c" && answer != "m");
            } else{//per evitare di ripetere più volte il singolo processo di cedimento di un token nero al master
                cout<<"Adrenalina e confusione sono gia' attivi, i restanti token neri estratti andranno al master"<<endl;
                answer="";
                theMaster.addMultipleBlack(bag.getBlackExtracted());
                bag.setBlackExtracted(0);
                exitFlag=true;//così salta direttamente alla fine del processo e bag.getBlackExtracted() = 0
            }

            if(!exitFlag){
                if (answer == "m")//assegnazione del token nero
                    theMaster.addBlack();
                else if (answer == "a")
                    adrenaline = true;
                else if (answer == "c")
                    confusion = true;

                bag.setBlackExtracted(bag.getBlackExtracted() - 1);
                cout << "Ti restano " << bag.getBlackExtracted() << " token neri da smaltire" << endl;
            }

        } while (bag.getBlackExtracted() != 0);
    }

    else//se l'eroe è andato fuori scena tutti i token neri vanno automaticamente al master
        theMaster.addMultipleBlack(bag.getBlackExtracted());
}

void Hero::returnBack(int numW, int numB, int numEx, Master &theMaster) {

    setBag(numW, numB);//settaggio del sacchetto con conseguente estrazione per provare a tornare in scena. Non sono presenti tutti i normali controlli per l'eroe
    Player::extract(numEx);
    if(bag.getWhiteExtracted()){//questo perché basta un solo bianco per tornare in scena
        setOutScene(false);
        setAdrenaline(false);
        setConfusion(false);
    }

    else
        cout<<nameCharacter<<" non e' riuscito a tornare in scena!"<<endl;

    blackTokenPartition(theMaster, true);//che riesca o no a tornare in scena i token neri estratti vanno comunque al master, tutti.

    bag.reset();
}