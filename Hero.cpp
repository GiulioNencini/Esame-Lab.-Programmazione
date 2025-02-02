//
// Created by Giulio Nencini on 16/01/2025.
//
#include "Hero.h"

Hero::Hero(string nameCharacter, string namePlayer, string myRisk, unsigned int numberPlayer)  : nameCharacter(std::move(nameCharacter)), namePlayer(std::move(namePlayer)), myRisk(std::move(myRisk)), numberPlayer(numberPlayer) {
    cout<<"L'eroe "<<this->nameCharacter<<" si e' unito al party"<<endl;
}

//GESTIONE CARATTERISTICHE EROI
void Hero::setHeroCharacteristics(const string & arc, const set<string> &sQ, const set<string> &sA) {//Tutte le domande sono state messe in mainFunction. Qui si tratta solo di reinserirle. Più semplice eseguire o ut
    qualities.clear();
    abilities.clear();//sono necessari perché questa funzione può essere chiamata anche all'inizio per rieseguire la configurazione degli eroi

    string s=arc;
    setArchetype(s);
    qualities=sQ;
    abilities=sA;
}

void Hero::printIdentity() const {
    cout<<"("<<numberPlayer<<") "<<nameCharacter<<"        Impersonato da "<<namePlayer<<endl;
    cout<<"Disposto a tutto per: "<<myRisk<<endl;
    cout<<"ARCHETIPO: "<<getArchetype()<<endl;
    cout<<"QUALITA':"<<endl;
    printQualities();
    cout<<"ABILITA':"<<endl;
    printAbilities();
}


//METODI PER ITEM
void Hero::openItem() const {
    for(auto const &it : item){
        it->printInfo();
    }
}

void Hero::addItem(unique_ptr<NormItem> newItem){
    item.push_back(std::move(newItem));
    openItem();
}

void Hero::destroyAllItem(){
    item.clear();
}

bool Hero::isThereSearchedItem(const string &used) {//utile nello unit testing
    for(const auto &it : item){
        if(it->getName()==used){
            return true;
        }
    }
    return false;
}

void Hero::useItem() {
    string used;
    bool exitFlag = false;

    do {
        openItem();
        cin.ignore();
        cout << "Quale oggetto vuoi usare? Scrivi close per chiudere lo zaino" << endl;
        getline(cin, used);

        if (used != "close") {
            // Usa un ciclo tradizionale con indice per evitare problemi di invalidazione
            for (int i = 0; i < item.size(); ++i) {
                auto &iteItem = item[i]; // Riferimento all'elemento corrente

                if (iteItem->getName() == used) {
                    // Controllo per NormItem

                    //iteItem->usingThis() //todo-> deve restituire una stringa o un numero

                    if (!iteItem->isConsumable()) {
                        cout << "OGGETTO SELEZIONATO: ";
                        iteItem->printInfo();
                        cout << endl;

                        string again;
                        cout << iteItem->getName() << " puo' essere ancora usato? y/n" << endl;
                        yesOrNot(again);

                        if (again == "n") {
                            cout << iteItem->getName() << " e' stato rimosso dall'inventario" << endl;
                            item.erase(item.begin() + i); // Rimuovi l'oggetto
                            --i; // Decrementa l'indice per evitare problemi di invalidazione
                        }
                        exitFlag = true;
                        break; // Esci dal ciclo dopo aver trovato e gestito l'oggetto
                    }
                        // Controllo per ConsumableItem
                    else if (iteItem->isConsumable()) {
                        cout << "OGGETTO SELEZIONATO: ";
                        iteItem->printInfo();
                        cout << endl;

                        unsigned int numUsed = 0;
                        bool e = false;
                        do {
                            cout << "Quanti " << iteItem->getName() << " vuoi usare?" << endl;
                            insertNumber(numUsed, e);
                        } while (numUsed > iteItem->getAmount());

                        iteItem->setAmount(iteItem->getAmount() - numUsed);

                        if (iteItem->getAmount() == 0) {
                            cout << iteItem->getName() << " e' stato rimosso dall'inventario" << endl;
                            item.erase(item.begin() + i); // Rimuovi se la quantità residua è zero
                            --i; // Decrementa l'indice per evitare problemi di invalidazione
                        } else {
                            cout << "Ti sono rimasti " << iteItem->getAmount() << " " << iteItem->getName() << endl;
                        }

                        exitFlag = true;
                        break; // Esci dal ciclo dopo aver trovato e gestito l'oggetto
                    }
                }
            }
        }
    } while (!exitFlag);
}//fixme output, anche questa inappropriata?. Idem, passare tutte le risposte


bool Hero::isThereThisConsumableItem(const string &inputItem, unsigned int amount){
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
void Hero::setBag(unsigned const int numW, unsigned const int numB) {
    if(!confusion){//differentemente a quello del master, il settaggio del sacchetto di un eroe può essere condizionato dell'attributo confusion
        setWhite(numW);
        setBlack(numB);
    }
    else{
        unsigned int nW=0, nB=0;
        setUnknown(numW);
        for(int i=0;i<getUnknownFromBag();i++){
            int x = getRandomWB();//Tanti random quanti sono gli sconosciuti. Questa funzione genera 0 e 1
            if(x)
                nW++;
            else
                nB++;
        }

        setWhite(nW);
        setBlack(numB+nB);
    }
}

void Hero::extract(unsigned int const exVal, unsigned int const danger, const bool &isDangerous) {
    //Meccanica dell'adrenalina
    if (!adrenaline) {
        Player::extract(exVal);//differentemente al master, l'eroe deve passare tutti questi altri controlli quando estrae
        if (isDangerous)
            goOffScene(danger, getBlackExtractedFromBag());//Verifica del fuori-scena. Vedi la seconda funzione dopo questa

    }
    else {//se c'è adrenalina deve estrarre 4 token
        Player::extract(4);
        if (isDangerous)
            goOffScene(danger, getBlackExtractedFromBag());
    }
}

void Hero::risk(unsigned const int remain) {
        Player::extract(remain);
}

void Hero::goOffScene(unsigned const int danger, unsigned const int eb) {
    if(eb>=danger)
        setOutScene(true);
}
/*else{
int x= getRandom(3);
if(x==1)
    cout<<getNameCharacter()<<" ha scampato il pericolo..."<<endl;
else if(x==2)
    cout<<getNameCharacter()<<" ha avuto fortuna..."<<endl;
else if(x==3)
    cout<<"Ti e' andata bene "<<getNameCharacter()<<endl;
}*/


void Hero::blackTokenPartition(Master &theMaster, bool isOutScene) {//fixme output
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
                theMaster.addUsableBlack(getBlackExtractedFromBag());
                cout<<"Il master ha ricevuto "<<getBlackExtractedFromBag()<<" token"<<endl;
                setBlackExtracted(0);
                exitFlag=true;//così salta direttamente alla fine del processo e bag.getBlackExtracted() = 0
            }

            if(!exitFlag){
                if (answer == "m"){
                    theMaster.addUsableBlack(1);
                    cout<<"Il master ha ricevuto un token"<<endl;
                }//assegnazione del token nero

                else if (answer == "a")
                    adrenaline = true;
                else if (answer == "c")
                    confusion = true;

                setBlackExtracted(getBlackExtractedFromBag() - 1);
                cout << "Ti restano " << getBlackExtractedFromBag() << " token neri da smaltire" << endl;
            }

        } while (getBlackExtractedFromBag() != 0);
    }

    else{
        theMaster.addUsableBlack(getBlackExtractedFromBag());
        cout<<"Il master ha ricevuto "<<getBlackExtractedFromBag()<<" token"<<endl;
    }//se l'eroe è andato fuori scena tutti i token neri vanno automaticamente al master

}

void Hero::returnBack(unsigned const int numW,  const unsigned int numB,  const unsigned int numEx, Master &theMaster) {

    setBag(numW, numB);//Settaggio del sacchetto con conseguente estrazione per provare a tornare in scena. Non sono presenti tutti i normali controlli per l'eroe
    Player::extract(numEx);

    if(getWhiteExtractedFromBag()){//questo perché basta un solo bianco per tornare in scena
        setOutScene(false);
        setAdrenaline(false);
        setConfusion(false);
    }

    blackTokenPartition(theMaster, true);//che riesca o no a tornare in scena i token neri estratti vanno comunque al master, tutti.

    resetBag();
}