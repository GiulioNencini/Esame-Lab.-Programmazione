#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_HERO_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_HERO_H


#include "Player.h"
#include "Master.h"
#include "ConsumableItem.h"
#include <set>

class Hero : public Player {
    string namePlayer;
    string nameCharacter;
    string myRisk;
    int numberPlayer;
    bool adrenaline = false;
    bool confusion = false;
    bool outScene = false;
    string archetype;
    set<string> qualities;
    set<string> abilities;
    vector<unique_ptr<NormItem>> item;

public:
    explicit Hero(string nameCharacter, string namePlayer, string myRisk, int numberPlayer);
    ~Hero() override{
        cout<<"L'eroe "<<this->nameCharacter<<" ha lasciato il party"<<endl;
    };

    void openItem() const;

    void addItem(unique_ptr<NormItem> newItem);

    void destroyAllItem();

    bool isThereSearchedItem(const string &used);

    bool itemIsEmpty();

    void accumulateThisConsumableItem(const string &inputItem, int amount);

    void sortItem();

    void setBag(int numW, int numB) override;//settaggio della difficoltà, viene fatta a parte prima di qualsiasi altra estrazione/controllo

    void extract(int exVal, int danger, const bool &isDangerous);//sovraccaricato

    void goOffScene(int danger, int eb);

    void risk(int remain);

    void blackTokenPartition(Master &theMaster, const string& choice);

    void returnBack( int numW, int numB, int numEx);

    void printIdentity() const;

    void removeQuality(const string &deletedQuality);

    void removeAbility(const string &deletedAbility);

    void printQualities() const;

    void printAbilities() const;

    void deleteItemFromThisPosition(int pos);

    unique_ptr<NormItem> const &getItemFromThisPosition(int pos) const;

    void insertQuality(const string &quality);

    void deleteAllQualities();

    void deleteAllAbilities();

    void insertAbility(const string &ability);

    bool isThereThisQuality(const string &q);

    bool isThereThisAbility(const string &a);


//getter e setter
    const string &getNamePlayer() const {
        return namePlayer;
    }

    const string &getNameCharacter() const {
        return nameCharacter;
    }

    void setNameCharacter(string &n) {
        nameCharacter = std::move(n);
    }

    void setNamePlayer(string &np){
        namePlayer = std::move(np);
    }

    const string &getRisk() const{
        return myRisk;
    }

    void setRisk(string &r){
        myRisk=std::move(r);
    }

    bool isAdrenaline() const {
        return adrenaline;
    }

    void setAdrenaline(bool a) {
        adrenaline = a;
    }

    bool isConfusion() const {
        return confusion;
    }

    void setConfusion(bool c) {
        confusion = c;
    }

    bool isOutScene() const {
        return outScene;
    }

    void setOutScene(bool o) {
        outScene = o;
    }

    void setNumberPlayer(int num){
        if (num > 0)
            numberPlayer = num;
        else
            throw runtime_error("Valore inatteso in setNumberPlayer");

    }

    int getNumberPlayer() const{
        return numberPlayer;
    }

    const string &getArchetype() const{
        return archetype;
    }

    void setArchetype(string &a){
        archetype=std::move(a);
    }


    int getNumQualities() const{
        return qualities.size();
    }

    int getNumAbilities() const{
        return abilities.size();
    }

    int getItemSize(){
        return item.size();
    }



};


#endif //SISTEMA_DI_GIOCO_NOT_THE_END_HERO_H
