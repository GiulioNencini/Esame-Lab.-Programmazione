//
// Created by Giulio Nencini on 16/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_HERO_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_HERO_H


#include "Player.h"
#include "Master.h"
#include <set>

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
    multiset<string> item;//fixme item

public:
    explicit Hero(string nameCharacter, string namePlayer, string myRisk,unsigned int numberPlayer);
    ~Hero()=default;

    void setHeroCharacteristics();

    void openItem() const{//fixme item
        cout<<"\nL'inventario di "<<nameCharacter<<endl;
        for(auto const &it : item){
            cout<<it<<endl;
        }
    };

    void addItem(string &newItem){//fixme item
        item.insert(newItem);
        cout<<"Il nuovo oggetto "<<newItem<<" e' stato inserito nell'inventario"<<endl;
    }

    void removeItem(string &deleteItem){//fixme item
        item.erase(deleteItem);
        cout<<"L'oggetto "<<deleteItem<<" e' stato rimosso dall'inventario"<<endl;
        openItem();
    }

    void destroyItem(){//fixme item
        item.clear();
    }

    auto getEndItem() const{//fixme item
        return item.end();
    }

    auto getFindItem(string &used){//fixme item
        return item.find(used);
    }

    bool itemIsEmpty(){//fixme item
        if(item.empty())
            return true;
        else
            return false;
    }

    void setBag(int numW, int numB) override;//settaggio della difficoltà, viene fatta a parte prima di qualsiasi altra estrazione/controllo

    void extract(Master &theMaster);//sovraccaricato

    void static setDanger(int &danger, bool &isDangerous);

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
            if(++i<it.size()+1)
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
            if(++i<it.size()+1)
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
};


#endif //SISTEMA_DI_GIOCO_NOT_THE_END_HERO_H
