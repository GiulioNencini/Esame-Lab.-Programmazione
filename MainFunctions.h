//
// Created by Giulio Nencini on 16/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_MAINFUNCTIONS_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_MAINFUNCTIONS_H

#include <iostream>
#include "Hero.h"



void setInitialItem(vector<Hero> &playerVector) {//fixme item
    for (auto &it: playerVector) {
        string answer;
        do {
            cout << it.getNameCharacter() << "\n\n ha oggetti nell'inventario? y/n" << endl;
            cin >> answer;
        } while (answer != "y" && answer != "n");

        if (answer == "y") {
            string item;
            do {
                cout << "Inserire l'oggetto" << endl;
                cin.ignore();
                getline(cin, item);
                it.addItem(item);
                cout << "Ne ha altri? y/n" << endl;
                cin >> answer;
            } while (answer == "y");
        }
    }
}

void setInitialItemAddedCharacter(vector<Hero> &playerVector, unsigned int lastPlayer){//fixme item
    for (auto &it: playerVector) {
        if(it.getNumberPlayer()==lastPlayer){
            string answer;
            do {
                cout << it.getNameCharacter() << " ha oggetti nell'inventario? y/n" << endl;
                cin >> answer;
            } while (answer != "y" && answer != "n");

            if (answer == "y") {
                string item;
                do {
                    cout << "Inserire l'oggetto" << endl;
                    cin.ignore();
                    getline(cin, item);
                    it.addItem(item);
                    do{
                        cout << "Ne ha altri? y/n" << endl;
                        cin >> answer;
                    }while(answer!="y" && answer!="n");

                } while (answer == "y");
            }
        }
    }
}

void getPartyIdentity(vector<Hero> &playerVector){//fixme item
    cout<<"\nIL NOSTRO PARTY:\n"<<endl;
    for(const auto &it : playerVector){
        it.getIdentity();
        it.openItem();
        cout<<"\n\n"<<endl;
    }
}

void getFinalPartyIdentity(vector<Hero> &playerVector){ //fixme item
    for(const auto &it : playerVector){
        it.getIdentity();
        if(it.isOutScene())
            cout<<"E' fuori scena"<<endl;
        if(it.isAdrenaline())
            cout<<"E' in adrenalina"<<endl;
        if(it.isConfusion())
            cout<<"E' in confusione"<<endl;
        it.openItem();
        cout<<"\n\n"<<endl;
    }
}

void modifyCharacter(vector<Hero> &playerVector, unsigned int numPlayer){

    int num=0;
    do {
        cout << "Quale personaggio vuoi modificare?" << endl;
        bool e;
        insertNumber(num, e);
    }while(num<1 || num>numPlayer);

    for(auto &it : playerVector){//this
        if(it.getNumberPlayer()==num){
            cin.ignore();
            it.getIdentity();
            string newCred;
            cout<<"Reinserire il nome del giocatore:"<<" ";
            getline(cin,newCred);
            it.setNamePlayer(newCred);
            cout<<"\nReinserire il nome del personaggio:"<<" ";
            getline(cin,newCred);
            it.setNameCharacter(newCred);
            cout<<"\nPer cosa sei disposto a rischiare "<<it.getNameCharacter()<<"?"<<endl;
            getline(cin,newCred);
            it.setRisk(newCred);
//fixme item
            string answer;
            do{
                cout<<"Vuoi modificare anche l'inventario? y/n ATTENZIONE:Sara' completamente cancellato e dovra' essere rifatto da capo."<<endl;
                getline(cin,answer);
            }while(answer!="y" && answer!="n");

            if(answer=="y"){
                it.destroyItem();//capire se è possibile incapsulare
                cin.ignore();
                do {
                    cout << it.getNameCharacter() << " ha oggetti nell'inventario? y/n" << endl;
                    cin >> answer;
                } while (answer != "y" && answer != "n");

                if (answer == "y") {
                    string item;
                    do {
                        cout << "Inserire l'oggetto" << endl;
                        cin.ignore();
                        getline(cin, item);
                        it.addItem(item);
                        cout << "Ne ha altri? y/n" << endl;
                        cin >> answer;
                    } while (answer == "y");
                }
            }
        }

        getPartyIdentity(playerVector);
    }
}

void setCharacterIdentity(unsigned int i, vector<Hero> &playerVector){//funzione usata all'inizio per dare identità agli eroi, vedi funzione setPartyIdentity

    cout<<"Creazione del personaggio "<<i<<endl;
    string nameCharacter, namePlayer, risk;
    cout<<"Come si chiama il giocatore?"<<endl;
    getline(cin,namePlayer);
    cout<<"Come si chiama il personaggio?"<<endl;
    getline(cin,nameCharacter);
    cout<<"Per cosa sei disposto a rischiare "<<nameCharacter<<"?"<<endl;
    getline(cin,risk);

    Hero player(nameCharacter,namePlayer,risk,i);
    player.setHeroCharacteristics();
    playerVector.push_back(player);
    cout<<"\n\n\n"<<endl;
}

void setPartyIdentity(Master &theMaster, vector<Hero> &playerVector, unsigned int &numPlayer, bool loading){

    do {
        cout << "Inserire il numero dei giocatori, massimo 5" << endl;
        bool e;
        insertNumber(numPlayer, e);

    }while (numPlayer < 1 || numPlayer>5);
    cin.ignore();

    for(int i=1;i<=numPlayer;i++){
        setCharacterIdentity(i, playerVector);
    }
//fixme item
    if(!loading){
        setInitialItem(playerVector);
        getPartyIdentity(playerVector);
    }
}

void removingCharacteristic(Hero &playerModified){
    string answer;
    do{
        cout<<"Vuoi rimuovere una qualita' o un'abilita'? q/a"<<endl;
        cin>>answer;
    }while(answer!="q" && answer!="a");

    if(answer=="q"){
        cout<<"QUALITA' ATTUALI:"<<endl;
        playerModified.getQualities();
        cout<<"Quale qualita' vuoi rimuovere?"<<endl;
        cin.ignore();
        getline(cin,answer);
        playerModified.removeQuality(answer);
    }
    else if(answer=="a"){
        cout<<"ABILITA' ATTUALI:"<<endl;
        playerModified.getAbilities();
        cout<<"Quale abilita' vuoi rimuovere??"<<endl;
        cin.ignore();
        getline(cin,answer);
        playerModified.removeAbility(answer);
    }
}

void addingCharacteristic(Hero &playerModified){
    string answer;
    bool numControl;
    do{
        if(playerModified.getNumQualities()==6 && playerModified.getNumAbilities()==12){
            cout<<"Hai gia' il massimo numero possibile di tratti, impossibile averne altri"<<endl;
            break;
        }

        numControl=false;
        cout<<"Vuoi aggiungere una qualita' o un'abilita'? q/a"<<endl;
        cout<<"ATTENZIONE: ricorda che non puoi avere piu' di 6 qualita' e 12 abilita' (attualmente hai "<<playerModified.getNumQualities()<<" qualita' e "<<playerModified.getNumAbilities()<<" abilita')";
        cin>>answer;
        if((answer=="q" && playerModified.getNumQualities()<6) || (answer=="a" && playerModified.getNumAbilities()<12))//controllo per non sforare il numero massimo di abilità e qualità
            numControl=true;
        if(answer=="q" && !numControl)
            cout<<"Hai gia' il massimo numero possibile di qualita'"<<endl;
        if(answer=="a" && !numControl)
            cout<<"Hai gia' il massimo numero possibile di abilita'"<<endl;

    }while(!numControl);

    if(answer=="q"){
        cout<<"QUALITA' ATTUALI:"<<endl;
        playerModified.getQualities();
        cout<<"Qual e' la tua nuova qualita'?"<<endl;
        cin.ignore();
        getline(cin,answer);
        playerModified.addQuality(answer);
    }
    else if(answer=="a"){
        cout<<"ABILITA' ATTUALI:"<<endl;
        playerModified.getAbilities();
        cout<<"Qual e' la tua nuova abilita'?"<<endl;
        cin.ignore();
        getline(cin,answer);
        playerModified.addAbility(answer);
    }
}

void game(Master &theMaster, vector<Hero> &playerVector, unsigned int &numPlayer){//gioco effettivo
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl;
    cout<<"L'AVVENTURA HA INIZIO!"<<endl; //void starGame(){};

    string command;
    do{
        do {
            command="";
            cout << "\n\n\nScegliere un comando:" << endl;
            cout<<"h/m per far giocare gli eroi/il master"<<endl;
            cout<<"modify/add/remove per modificare/aggiungere/rimuovere un personaggio"<<endl;
            cout<<"endgame per terminare la sessione di gioco"<<endl;
            cin >> command;
        }while(command!="m" && command!="h" && command!="modify" && command!="endgame" && command!="add" && command!="remove");

        if(command=="h"){//GIOCANO GLI EROI
            int playingCharacter;
            do {
                cout << "A quale giocatore tocca?  " << endl;//rivedere la scritta
                for(const auto &it : playerVector){
                    cout<<"("<<it.getNumberPlayer()<<") "<<it.getNameCharacter()<<endl;
                }
                bool e;
                insertNumber(playingCharacter, e);
            }while(playingCharacter<1 && playingCharacter>numPlayer);

            for(auto &it : playerVector){
                if(playingCharacter==it.getNumberPlayer()){ //il giocatore è stato selezionato, adesso può eseguire le sue azioni

                    cout<<"\n\nTurno di "<<it.getNameCharacter()<<endl;
                    cout<<"Disposto a tutto per: "<<it.getRisk()<<endl;

                    //SE NON è FUORI SCENA
                    if(!it.isOutScene()){

                        if(it.isAdrenaline())//informazioni sul suo status adrenalina e confusione
                            cout<<"Adrenalina e' attiva"<<endl;
                        if(it.isConfusion())
                            cout<<"Confusione e' attiva"<<endl;

                        string action;
                        do {
                            cout<< "Scegli un'azione: superare una prova(t), attendere(w), aprire l'inventario(o), modificare un tratto(c)"<< endl;//NOTA: attendere non fa fare niente al personaggio, è un modo per uscire dal turno senza fare nulla di particolare
                            cin >> action;
                        }while(action!="t" && action!="w" && action!="o" && action!="c");


                        if(action=="t"){
                            int w = 0, b = 0;
                            bool e;
                            cout << "Inserire i token per l'estrazione" << endl;
                            cout << "Bianchi:"<<endl;
                            insertNumber(w, e);

                            cout << "\nNeri:"<<endl;
                            insertNumber(b, e);
                            it.setBag(w, b);
                            it.extract(theMaster);//solite funzione già viste
                        }

                        else if(action=="o"){//fixme item
                            string answer;

                            if(it.itemIsEmpty()){//se è vuoto non si possono usare oggetti
                                do{
                                    cout<<"Aggiungere un oggetto(a)"<<endl;
                                    cin>>answer;
                                }while(answer != "a" && answer!="CANCEL");
                            }
                            else{
                                do{
                                    cout<<"Vuoi usare(u) o aggiungere un oggetto(a)"<<endl;
                                    cin>>answer;
                                }while(answer != "u" && answer != "a" && answer!="CANCEL");
                            }


                            if(answer=="u"){
                                it.openItem();
                                string used;
                                bool found=false;
                                do{
                                    cin.ignore();
                                    cout<<"Quale oggetto vuoi usare?"<<endl;
                                    getline(cin,used);
                                    auto target=it.getFindItem(used);

                                    if(target != it.getEndItem() && used != "CANCEL"){

                                        found=true;
                                        string again;

                                        do{
                                            cout<<"L'oggetto puo' essere ancora usato? y/n"<<endl;
                                            cin>>again;
                                        }while(again != "y" && again != "n");

                                        if(again=="n")//rimozione del consumabile usato
                                            it.removeItem(used);
                                    }
                                }while(!found);
                            }

                            else if(answer=="a"){
                                string newObj;
                                cin.ignore();
                                cout<<"Inserire il nuovo oggetto:"<<endl;
                                getline(cin,newObj);
                                it.addItem(newObj);
                            }
                        }

                        else if(action=="c"){
                            string answer;
                            do{
                                cout<<"Scrivere new/remove/modify per aggiungere/togliere/togliere e riaggiungere un tratto. cancel per annullare"<<endl;
                                cin>>answer;
                            }while(answer!="new" && answer!="remove" && answer!="modify" && answer!="cancel");

                            if(answer=="new")
                                addingCharacteristic(it);

                            else if(answer=="remove")
                                removingCharacteristic(it);

                            else if(answer=="modify"){
                                cout<<"Per modificare un tratto prima scegli quale cancellare e poi, subito dopo, quale aggiungere"<<endl;
                                removingCharacteristic(it);
                                addingCharacteristic(it);
                            }
                        }

                        else if(action=="w")
                            cout<<it.getNameCharacter()<<" attende"<<endl;

                    }

                    else{//se è fuori scena
                        cout<<it.getNameCharacter()<<" e' fuori scena!"<<endl;
                        string answer;
                        do{
                            cout<<it.getNameCharacter()<<" puo' essere immediatamente soccorso? y/n"<<endl;
                            cin>>answer;
                        } while (answer!="y" && answer!="n");
                        if(answer=="y")
                            it.setOutScene(false);
                        else{

                            int w=0,b=0;
                            bool e;
                            cout<<"Inserire token per la prova del ritorno in scena"<<endl;
                            cout << "Bianchi:"<<endl;
                            insertNumber(w, e);

                            cout << "\nNeri:"<<endl;
                            insertNumber(b, e);

                            int ext=howExtract();
                            it.returnBack(w, b, ext, theMaster);//setBag sta dentro returnBack
                        }
                    }//tentare di ritornare in scena
                }
            }
        }

        else if(command=="m"){

            string action,exitAnswer;
            do{
                cout<<"Attualmente ho "<<theMaster.getUsableBlack()<<" token neri"<<endl;
                do{
                    cout<<"Complichiamo un po' le cose (t), facciamo un'estrazione (e)"<<endl;
                    cin>>action;
                }while(action!="t" && action!="e");

                if(action=="t"){
                    if(theMaster.getUsableBlack()){
                        int used;
                        do{
                            cout<<"Quanti token utilizzare..."<<endl;
                            bool e;
                            insertNumber(used, e);

                        }while(used<0 || used>theMaster.getUsableBlack());
                        theMaster.useBlack(used);
                    }
                }
                else{
                    int w=0,b=0;
                    cout<<"Bianchi:"<<endl;
                    bool e;
                    insertNumber(w,e);

                    cout<<"Neri:"<<endl;
                    insertNumber(b,e);

                    theMaster.setBag(w,b);
                    theMaster.extract(howExtract());
                    theMaster.reset();
                }

                do{
                    cout<<"Ho altro da fare? y/n"<<endl;
                    cin>>exitAnswer;
                }while(exitAnswer!="y" && exitAnswer!="n");

            }while(exitAnswer=="y");
        }

        else if(command=="modify"){
            modifyCharacter(playerVector, numPlayer);
        }

        else if(command=="add"){//segue l'effettiva creazione di un personaggio
            if(numPlayer<5){
                cin.ignore();
                setCharacterIdentity(numPlayer+1, playerVector);
                numPlayer++;
                setInitialItemAddedCharacter(playerVector, numPlayer);
                getPartyIdentity(playerVector);
            }
            else
                cout<<"Il party ha gia' il massimo numero di giocatori"<<endl;

        }

        else if(command=="remove"){
            int leaving=0;
            do{
                cout<<"Quale personaggio lascia il party?"<<endl;
                bool e;
                do{
                    cin>>leaving;
                    verifyNumber(e);
                }while(e);
            }while(leaving<1 || leaving>numPlayer);

            for(auto &it : playerVector){//ricerca dell'uscente
                if(leaving==it.getNumberPlayer())
                    cout<<it.getNameCharacter()<<"\n ha lasciato il party\n"<<endl;
            }

            playerVector.erase(playerVector.begin()+leaving-1);//aggiornamento del vettore
            numPlayer--;

            int x=1;//riassegnazione dei numeri dei giocatori
            for(auto &it : playerVector){
                it.setNumberPlayer(x++);
            }
            getPartyIdentity(playerVector);

        }

    }while(command!="endgame");

    cout<<"Sessione terminata, ecco il resoconto finale:"<<endl;
    cout<<"Se la vostra storia continua, potete prendere nota del resoconto per reinserire i dati nella funzione di ripristino della lobby \n\n"<<endl;
    getFinalPartyIdentity(playerVector);
}



#endif //SISTEMA_DI_GIOCO_NOT_THE_END_MAINFUNCTIONS_H