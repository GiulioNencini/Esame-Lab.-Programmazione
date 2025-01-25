//
// Created by Giulio Nencini on 16/01/2025.
//
#include "Hero.h"

Hero::Hero(string nameCharacter, string namePlayer, string myRisk, unsigned int numberPlayer)  : nameCharacter(std::move(nameCharacter)), namePlayer(std::move(namePlayer)), myRisk(std::move(myRisk)), numberPlayer(numberPlayer) {
    cout<<"L'eroe "<<this->nameCharacter<<" si e' unito al party"<<endl;
}

//GESTIONE CARATTERISTICHE EROI
void Hero::setHeroCharacteristics() {
    string answer;
    qualities.clear();
    abilities.clear();//sono necessari perché questa funzione può essere chiamata anche all'inizio per rieseguire la configurazione degli eroi
    do{
        cout<<"NOTA PER LA CREAZIONE: un personaggio all'inizio ha di norma 3 qualita' e 4 abilita'"<<endl;
        cout << getNameCharacter() << ", qual e' il tuo archetipo?" << endl;
        cin.ignore();
        getline(cin, answer);
        setArchetype(answer);

        int num = 0;
        do{
            cout << "Quante sono le tue qualita'? Max 6" << endl;
            bool e;
            insertNumber(num, e);
        } while (num<1 || num>6);

        cout << "Quali sono?" << endl;
        for (int i = 0; i < num; i++) {//fixme sia qui che sotto c'è un problema per cui il primo carattere, a partire dal secondo elemento del set, non viene considerato
            cout<<"Qualita' numero "<<i+1<<": ";
            cin.ignore();
            getline(cin, answer);
            qualities.insert(answer);
        }
        num=0;
        do{
            cout << "Quante sono le tue abilita'? Max 12" << endl;
            bool e;
            insertNumber(num, e);
        }while(num<1 || num>12);

        cout << "Quali sono?" << endl;
        for (int i = 0; i < num; i++) {
            cout<<"abilita' numero "<<i+1<<": ";
            cin.ignore();
            getline(cin, answer);
            abilities.insert(answer);
        }

        cout<<"ARCHETIPO: "<<getArchetype()<<endl;

        cout<<"QUALITA':"<<endl;
        getQualities();

        cout<<"ABILITA':"<<endl;
        getAbilities();

        cout<<"Confermi le tue scelte? y/n"<<endl;
        yesOrNot(answer);

        if(answer=="n") {
            qualities.clear();
            abilities.clear();
        }
    }while (answer!="y");

}

void Hero::getIdentity() const {
    cout<<"("<<numberPlayer<<") "<<nameCharacter<<"        Impersonato da "<<namePlayer<<endl;
    cout<<"Disposto a tutto per: "<<myRisk<<endl;
    cout<<"ARCHETIPO: "<<getArchetype()<<endl;
    cout<<"QUALITA':"<<endl;
    getQualities();
    cout<<"ABILITA':"<<endl;
    getAbilities();
}


//METODI PER ITEM
void Hero::openItem() const {
    cout<<"\nL'inventario di "<<nameCharacter<<endl;
    for(auto const &it : item){
        it->getInfo();
    }
}

void Hero::addItem(unique_ptr<AbItem> newItem){
    item.push_back(std::move(newItem));
    openItem();
}

void Hero::destroyAllItem(){
    item.clear();
}

bool Hero::isThereSearchedItem(string &used) {
    for(const auto &it : item){
        if(it->getName()==used){
            return true;
        }
    }
    return false;
}

void Hero::useItem(unique_ptr<Hero> &it) {
    string used;
    bool exitFlag = false;

    do {
        it->openItem();
        cin.ignore();
        cout << "Quale oggetto vuoi usare? Scrivi close per chiudere lo zaino" << endl;
        getline(cin, used);

        if (it->isThereSearchedItem(used) && used != "close") {
            // Usa un ciclo tradizionale con indice per evitare problemi di invalidazione
            for (int i = 0; i < it->item.size(); ++i) {
                auto &iteItem = it->item[i]; // Riferimento all'elemento corrente

                if (iteItem->getName() == used) {
                    // NON CONSUMABILI
                    if (auto *tempItem = dynamic_cast<Item *>(iteItem.get())) {
                        unique_ptr<Item> target = make_unique<Item>(*tempItem);
                        cout << "OGGETTO SELEZIONATO: ";
                        target->getInfo();
                        cout << endl;

                        string again;
                        cout << target->getName() << " puo' essere ancora usato? y/n" << endl;
                        yesOrNot(again);

                        if (again == "n") {
                            cout << target->getName() << " e' stato rimosso dall'inventario" << endl;
                            it->item.erase(it->item.begin() + i); // Rimuovi l'oggetto
                            --i;
                        }
                        exitFlag = true;
                        break; // Esci dal ciclo dopo aver trovato e gestito l'oggetto
                    }
                        // CONSUMABILI
                    else if (auto *tempCItem = dynamic_cast<ConsumableItem *>(iteItem.get())) {
                        unique_ptr<ConsumableItem> target = make_unique<ConsumableItem>(*tempCItem);
                        cout << "OGGETTO SELEZIONATO: ";
                        target->getInfo();
                        cout << endl;

                        int numUsed = 0;
                        bool e = false;
                        do {
                            cout << "Quanti " << target->getName() << " vuoi usare?" << endl;
                            insertNumber(numUsed, e);
                        } while (numUsed > target->getAmount());

                        target->setAmount(target->getAmount() - numUsed);

                        if (target->getAmount() == 0) {
                            cout << target->getName() << " e' stato rimosso dall'inventario" << endl;
                            it->item.erase(it->item.begin() + i); // Rimuovi se la quantità residua è zero
                            --i;
                        } else {
                            cout << "Ti sono rimasti " << target->getAmount() << " " << target->getName() << endl;
                            it->item[i] = std::move(target); // Sovrascriviamo l'oggetto in questione
                        }

                        exitFlag = true;
                        break; // Esci dal ciclo dopo aver trovato e gestito l'oggetto
                    }
                }
            }
        }
    } while (!exitFlag);
}

bool Hero::isThereThisConsumableItem(string &inputItem, unsigned int amount){
    ConsumableItem* tempCItem;
    for(auto const &it: item){
        if( (tempCItem = dynamic_cast<ConsumableItem*>(it.get()))&& (tempCItem->getName()==inputItem)){//tempCItem o it
            tempCItem->setAmount(tempCItem->getAmount()+amount);
            return true;
        }
    }
    return false;
}

void Hero::sortItem(){
    std::sort(item.begin(),item.end());
}

bool Hero::itemIsEmpty(){
    if(item.empty())
        return true;
    else
        return false;
}



//OPERAZIONI E MECCANICHE PER LE ESTRAZIONI
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
            goOffScene(danger, bag.getBlackExtracted());//Verifica del fuori-scena. Vedi la seconda funzione dopo questa
        if(!outScene) {
            risk(5 - exVal);//Rischio, il valore è pari ai token rimanenti. Vedi la terza funzione dopo questa
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
    cout << "E' pericoloso? y/n"<<endl;
    yesOrNot(answer);

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
    cout << "Vuoi rischiare? y/n" << endl;
    yesOrNot(answer);
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

    setBag(numW, numB);//Settaggio del sacchetto con conseguente estrazione per provare a tornare in scena. Non sono presenti tutti i normali controlli per l'eroe
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