#include "Hero.h"

Hero::Hero(string nameCharacter, string namePlayer, string myRisk, unsigned int numberPlayer)  : nameCharacter(std::move(nameCharacter)), namePlayer(std::move(namePlayer)), myRisk(std::move(myRisk)), numberPlayer(numberPlayer) {
    cout<<"L'eroe "<<this->nameCharacter<<" si e' unito al party"<<endl;
}

//GESTIONE CARATTERISTICHE EROI

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

void Hero::accumulateThisConsumableItem(const string &inputItem, unsigned int const amount){
    ConsumableItem* tempCItem;
    for(auto const &it: item){
        if( (tempCItem = dynamic_cast<ConsumableItem*>(it.get())) && (tempCItem->getName()==inputItem)){
            tempCItem->setAmount(tempCItem->getAmount()+amount);
        }
    }
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
        printExtracted();
        if (isDangerous)
            goOffScene(danger, getBlackExtractedFromBag());//Verifica del fuori-scena. Vedi la seconda funzione dopo questa

    }
    else {//se c'è adrenalina deve estrarre 4 token
        Player::extract(4);
        printExtracted();
        if (isDangerous)
            goOffScene(danger, getBlackExtractedFromBag());
    }
}

void Hero::risk(unsigned const int remain) {
        Player::extract(remain);
        printExtracted();
}

void Hero::goOffScene(unsigned const int danger, unsigned const int eb) {
    if(eb>=danger)
        setOutScene(true);
}

void Hero::blackTokenPartition(Master &theMaster, const string &choice) {//La funzione che dopo l'estrazione rende possibile lo smaltimento dei token neri estratti
        //choice determina dove mettere i token neri
        if (choice == "m")
            theMaster.addUsableBlack(getBlackExtractedFromBag());

        else if (choice == "a"){
            adrenaline = true;
            theMaster.addUsableBlack(getBlackExtractedFromBag()-1);
        }

        else if (choice == "c"){
            confusion = true;
            theMaster.addUsableBlack(getBlackExtractedFromBag()-1);
        }

        else if(choice =="ac"){
            adrenaline=true;
            confusion=true;
            theMaster.addUsableBlack(getBlackExtractedFromBag()-2);
        }
}

void Hero::returnBack(unsigned const int numW,  const unsigned int numB,  const unsigned int numEx) {

    setBag(numW, numB);//Settaggio del sacchetto con conseguente estrazione per provare a tornare in scena. Non sono presenti tutti i normali controlli per l'eroe
    Player::extract(numEx);
    printExtracted();

    if(getWhiteExtractedFromBag()){//questo perché basta un solo bianco per tornare in scena
        setOutScene(false);
        setAdrenaline(false);
        setConfusion(false);
    }
}