//
// Created by Giulio Nencini on 16/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_HERO_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_HERO_H


#include "Player.h"
#include "Master.h"
#include "ConsumableItem.h"
#include "Item.h"
#include <set>

class AbItem;


class Hero : public Player {
    string namePlayer;
    string nameCharacter;
    string myRisk;
    unsigned int numberPlayer;
    bool adrenaline = false;
    bool confusion = false;
    bool outScene = false;
    string archetype;//ce n'è uno solo
    set<string> qualities;
    set<string> abilities;
    vector<unique_ptr<AbItem>> item;

public:
    explicit Hero(string nameCharacter, string namePlayer, string myRisk, unsigned int numberPlayer);
    ~Hero() override{
        cout<<"L'eroe "<<this->nameCharacter<<" ha lasciato il party"<<endl;
    };

    void setHeroCharacteristics();

    void openItem() const;

    void addItem(unique_ptr<AbItem> newItem);

    void destroyAllItem();

    bool isThereSearchedItem(string &used);

    static void useItem(unique_ptr<Hero> &it);

    bool itemIsEmpty();

    bool isThereThisConsumableItem(string &inputItem, unsigned int amount);

    void sortItem();

    void setBag(int numW, int numB) override;//settaggio della difficoltà, viene fatta a parte prima di qualsiasi altra estrazione/controllo

    void extract(Master &theMaster);//sovraccaricato

    void static setDanger(int &danger, bool &isDangerous, string &answer);

    void goOffScene(int danger, int eb);

    void risk(int remain);

    void blackTokenPartition(Master &theMaster, bool isOutScene);

    void returnBack(int numW, int numB, int numEx, Master &theMaster);

    void getIdentity() const;

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
        if(adrenaline)
            cout<<nameCharacter<<" e' in adrenalina"<<endl;
        else
            cout<<nameCharacter<<" si e' calmato"<<endl;
    }

    bool isConfusion() const {
        return confusion;
    }

    void setConfusion(bool c) {
        confusion = c;
        if(confusion)
            cout<<nameCharacter<<" e' confuso"<<endl;
        else
            cout<<nameCharacter<<" si e' riconcentrato"<<endl;
    }

    bool isOutScene() const {
        return outScene;
    }

    void setOutScene(bool o) {
        outScene = o;
        if(!outScene)
            cout<<nameCharacter<<" e' tornato in scena!"<<endl;
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

    void getQualities() const{//fixme problema pe cui taglia le prime lettere
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

    void getAbilities() const{
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

    void insertQuality(string &quality){
        qualities.insert(quality);
    }

    void insertAbility(string &ability){
        abilities.insert(ability);
    }

    bool isThereThisQuality(string &q){
        auto it = qualities.find(q);
        if(it != qualities.end())
            return true;
        else return false;
    }
    bool isThereThisAbility(string &a){
        auto it = abilities.find(a);
        if(it != abilities.end())
            return true;
        else return false;
    }

    int getItemSize(){
        return item.size();
    }

    int getUnknownToken(){
        return bag.getUnknown();
    }

    void setBlackExtracted(int n){
        bag.setBlackExtracted(n);
    }
};


#endif //SISTEMA_DI_GIOCO_NOT_THE_END_HERO_H
