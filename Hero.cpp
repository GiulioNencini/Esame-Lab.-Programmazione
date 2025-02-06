#include "Hero.h"

Hero::Hero(string nameCharacter, string namePlayer, string myRisk, int numberPlayer)  : nameCharacter(std::move(nameCharacter)), namePlayer(std::move(namePlayer)), myRisk(std::move(myRisk)), numberPlayer(numberPlayer) {
    cout<<"L'eroe "<<this->nameCharacter<<" si e' unito al party"<<endl;
}

//GESTIONE CARATTERISTICHE EROI

void Hero::deleteAllAbilities() {
    abilities.clear();
}

void Hero::deleteAllQualities() {
    qualities.clear();
}

void Hero::insertAbility(const string &ability) {
    abilities.insert(ability);
}

void Hero::insertQuality(const string &quality) {
    qualities.insert(quality);
}

bool Hero::isThereThisAbility(const string &a) {
    auto it = abilities.find(a);
    if (it != abilities.end())
        return true;
    else return false;
}

bool Hero::isThereThisQuality(const string &q) {
    auto it = qualities.find(q);
    if (it != qualities.end())
        return true;
    else return false;
}

void Hero::printAbilities() const {
    int i = 0;
    for (const auto &it: abilities) {
        if (++i < getNumAbilities())
            cout << it << ", ";
        else
            cout << it << endl;
    }
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

void Hero::printQualities() const {
    int i = 0;
    for (const auto &it: qualities) {
        if (++i < getNumQualities())
            cout << it << ", ";
        else
            cout << it << endl;
    }
}

void Hero::removeAbility(const std::string &deletedAbility) {
    abilities.erase(deletedAbility);
}

void Hero::removeQuality(const string &deletedQuality) {
    qualities.erase(deletedQuality);
}


//METODI PER ITEM

void Hero::accumulateThisConsumableItem(const string &inputItem, int const amount) {
    ConsumableItem *tempCItem;
    for (auto const &it: item) {
        if ((tempCItem = dynamic_cast<ConsumableItem *>(it.get())) && (tempCItem->getName() == inputItem)) {
            try {
                overflowPrevention(tempCItem->getAmount(), amount);
                it->setAmount(it->getAmount() + amount);
            } catch (std::exception &e) {
                cerr << e.what() << endl;
                tempCItem->setAmount(
                        std::numeric_limits<int>::max());//la variabile verrebbe quindi riempita fino all'orlo
            }
        }
    }
}

void Hero::addItem(unique_ptr<NormItem> newItem){
    item.push_back(std::move(newItem));
}

void Hero::deleteItemFromThisPosition(const int pos) {
    if (pos < item.size() && pos > 0)
        item.erase(item.begin() + pos);
    else
        throw runtime_error("ATTENZIONE: accesso ad una zona indesiderata");
}

void Hero::destroyAllItem(){
    item.clear();
}

unique_ptr<NormItem> const &Hero::getItemFromThisPosition(int const pos) const {
    if (pos < item.size() && pos > 0)
        return item[pos];
    else
        throw runtime_error("ATTENZIONE: accesso ad una zona indesiderata");
}

bool Hero::isThereSearchedItem(const string &used) {//utile nello unit testing
    for(const auto &it : item){
        if(it->getName()==used){
            return true;
        }
    }
    return false;
}

bool Hero::itemIsEmpty(){
    if(item.empty())
        return true;
    else
        return false;
}

void Hero::openItem() const {
    for (auto const &it: item) {
        it->printInfo();
    }
}

void Hero::sortItem() {
    std::sort(item.begin(), item.end());
}



//OPERAZIONI E MECCANICHE PER LE ESTRAZIONI

void Hero::blackTokenPartition(Master &theMaster,
                               const string &choice) {//La funzione che dopo l'estrazione rende possibile lo smaltimento dei token neri estratti
    //choice determina dove mettere i token neri
    if (choice == "m")
        theMaster.addUsableBlack(getBlackExtractedFromBag());

    else if (choice == "a" && getBlackExtractedFromBag() >= 1) {
        adrenaline = true;
        theMaster.addUsableBlack(getBlackExtractedFromBag() - 1);
    } else if (choice == "c" && getBlackExtractedFromBag() >= 1) {
        confusion = true;
        theMaster.addUsableBlack(getBlackExtractedFromBag() - 1);
    } else if (choice == "ac" && getBlackExtractedFromBag() >= 2) {
        adrenaline = true;
        confusion = true;
        theMaster.addUsableBlack(getBlackExtractedFromBag() - 2);
    }
}

void Hero::extract(int const exVal, int const danger, const bool &isDangerous) {
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

void Hero::goOffScene( const int danger,  const int eb) {
    if (danger < 0 || eb < 0)
        throw runtime_error("Valori inattesi in goOffScene");
    if(eb>=danger)
        setOutScene(true);
}

void Hero::returnBack(const int numW, const int numB,
                      const int numEx) {//NOTA: neanche qui è necessaria l'eccezione relativa alla confusione per extract
    setBag(numW, numB);//Settaggio del sacchetto con conseguente estrazione per provare a tornare in scena. Non sono presenti tutti i normali controlli per l'eroe
    Player::extract(numEx);
    printExtracted();

    if(getWhiteExtractedFromBag()){//questo perché basta un solo bianco per tornare in scena
        setOutScene(false);
        setAdrenaline(false);
        setConfusion(false);
    }
}

void Hero::risk(const int remain) {
    Player::extract(remain);
    printExtracted();
}

void Hero::setBag(const int numW, const int numB) {

    if (numW < 0 || numB < 0)
        throw runtime_error("Valori inattesi in setBag");

    if (!confusion) {//differentemente a quello del master, il settaggio del sacchetto di un eroe può essere condizionato dell'attributo confusion
        setWhite(numW);
        setBlack(numB);
    } else {
        int nW = 0, nB = 0;
        setUnknown(numW);
        for (int i = 0; i < getUnknownFromBag(); i++) {
            int x = getRandomWB();//Tanti random quanti sono gli sconosciuti. Questa funzione genera 0 e 1
            if (x)
                nW++;
            else
                nB++;
        }

        setWhite(nW);
        setBlack(numB + nB);
    }
}
