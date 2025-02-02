//
// Created by Giulio Nencini on 16/01/2025.
//

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
    unsigned int numberPlayer;
    bool adrenaline = false;
    bool confusion = false;
    bool outScene = false;
    string archetype;
    set<string> qualities;
    set<string> abilities;
    vector<unique_ptr<NormItem>> item;

public:
    explicit Hero(string nameCharacter, string namePlayer, string myRisk, unsigned int numberPlayer);
    ~Hero() override{
        cout<<"L'eroe "<<this->nameCharacter<<" ha lasciato il party"<<endl;
    };

    void setHeroCharacteristics(const string & arc, const set<string> &sQ, const set<string> &sA);

    void openItem() const;

    void addItem(unique_ptr<NormItem> newItem);

    void destroyAllItem();

    bool isThereSearchedItem(const string &used);

    //static void useItem(unique_ptr<Hero> &it);
    void useItem();

    bool itemIsEmpty();

    bool isThereThisConsumableItem(const string &inputItem, unsigned int amount);

    void sortItem();

    void setBag(unsigned int numW, unsigned int numB) override;//settaggio della difficoltà, viene fatta a parte prima di qualsiasi altra estrazione/controllo

    void extract(unsigned int exVal, unsigned int danger, const bool &isDangerous);//sovraccaricato

    void goOffScene(unsigned int danger, unsigned int eb);

    void risk(unsigned int remain);

    void blackTokenPartition(Master &theMaster, bool isOutScene);

    void returnBack(unsigned int numW, unsigned int numB, unsigned int numEx, Master &theMaster);

    void printIdentity() const;

    const string &getNameCharacter() const{
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
        numberPlayer=num;
    }

    unsigned int getNumberPlayer() const{
        return numberPlayer;
    }

    //get e set dei tratti
    const string &getArchetype() const{
        return archetype;
    }

    void setArchetype(string &a){
        archetype=std::move(a);
    }

    void addQuality(const string &newQuality){
        qualities.insert(newQuality);
    }

    void removeQuality(string &deletedQuality){
        qualities.erase(deletedQuality);
    }

    void printQualities() const{//fixme problema per cui taglia le prime lettere
        int i=0;
        for(const auto &it : qualities){
            if(++i<getNumQualities())
                cout<<it<<", ";
            else
                cout<<it<<endl;
        }
    }

    void addAbility(const string &newAbility){
        abilities.insert(newAbility);
    }

    void removeAbility(string &deletedAbility){
        abilities.erase(deletedAbility);
    }

    void printAbilities() const{
        int i=0;
        for(const auto &it : abilities){
            if(++i<getNumAbilities())
                cout<<it<<", ";
            else
                cout<<it<<endl;
        }
    }

    int getNumQualities() const{
        return qualities.size();
    }

    int getNumAbilities() const{
        return abilities.size();
    }

    //utili solo e soltanto nello unit testing
    const string& getNamePlayer() const{
        return namePlayer;
    }

    void insertQuality(const string &quality){
        qualities.insert(quality);
    }

    void insertAbility(const string &ability){
        abilities.insert(ability);
    }

    bool isThereThisQuality(const string &q){
        auto it = qualities.find(q);
        if(it != qualities.end())
            return true;
        else return false;
    }
    bool isThereThisAbility(const string &a){
        auto it = abilities.find(a);
        if(it != abilities.end())
            return true;
        else return false;
    }

    int getItemSize(){
        return item.size();
    }
};


#endif //SISTEMA_DI_GIOCO_NOT_THE_END_HERO_H
