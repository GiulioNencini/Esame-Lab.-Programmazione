//
// Created by Giulio Nencini on 16/01/2025.
//

#ifndef SISTEMA_DI_GIOCO_NOT_THE_END_MAINFUNCTIONS_H
#define SISTEMA_DI_GIOCO_NOT_THE_END_MAINFUNCTIONS_H

#include "Hero.h"




//FUNZIONI ITEM
void insertItem(string &answer/*fixme rendere costante?*/, unique_ptr<Hero> &it, unsigned int &amount, bool &err, bool isAddingItemDuringGame=false) {//Questa è la funzione che genera gli oggetti. Già distinguendoli come consumabili o meno
    if(!isAddingItemDuringGame){
        cout << "Ha oggetti nell'inventario? y/n" << endl;
        yesOrNot(answer);
    }
    else
        answer="y";

    if (answer == "y") {
        string inputItem;
        unique_ptr<NormItem> item;
        do {
            cout << "E' un consumabile? y/n" << endl;
            yesOrNot(answer);

            if (answer == "n") {
                cout << "Inserire il nome dell'oggetto" << endl;
                cin.ignore();
                getline(cin, inputItem);
                item = make_unique<NormItem>(inputItem);
                it->addItem(std::move(item));

            }

            else {
                cout << "Inserire il nome dell'oggetto" << endl;
                cin.ignore();
                getline(cin, inputItem);
                cout << "Inserire la quantita' di " << inputItem << endl;
                do {
                    insertNumber(amount, err);
                } while (amount <= 0);

                if(!it->isThereThisConsumableItem(inputItem, amount)){//verifica se è già presente, se non lo è lo crea, altrimenti aggiorna solo la quantità
                    item = make_unique<ConsumableItem>(inputItem, amount);
                    it->addItem(std::move(item));
                }
            }

            it->sortItem();

            if(!isAddingItemDuringGame){//la distinzione qui invece è una pura questione di senso del testo
                cout << "Ne ha altri? y/n" << endl;
                yesOrNot(answer);
            }
            else{
                cout << "Vuoi aggiungerne altri? y/n" << endl;
                yesOrNot(answer);
            }
        } while (answer == "y");
    }
}//NOTA: è necessario per la creazione e il caricamento fare questa piccola distinzione di funzioni per via della gestione del ciclo for iniziale

void setInitialItem(vector<unique_ptr<Hero>> &playerVector) {
    for (auto &it: playerVector) {
        string answer;
        unsigned int amount=0;
        bool err=false;
        insertItem(answer, it, amount, err);
    }
}

void setInitialItemAddedCharacter(vector<unique_ptr<Hero>> &playerVector, unsigned int const lastPlayer){//Questa invece è la funzione specifica per quando si aggiunge un personaggio nel bel mezzo della sessione
    unsigned int amount;
    string answer;
    bool err;
    for (auto &it: playerVector) {
        if(it->getNumberPlayer()==lastPlayer){
            answer="";
            amount=0;
            err=false;
            insertItem(answer, it, amount, err);
        }
    }
}


//GESTIONE DEI PERSONAGGI
void setCharacterIdentity(unsigned int const i, vector<unique_ptr<Hero>> &playerVector, bool initialSetting=true){//funzione usata all'inizio per dare identità agli eroi, vedi funzione setPartyIdentity

    cout<<"Creazione del personaggio "<<i<<endl;//C'era un problema per cui dal secondo personaggio in poi saltava la richiesta del nome del giocatore, risolto con cin.ignore(), ma bisogna premer invio quando si imposta per la prima volta, che sia il primo giocatore o che sia la funzione di aggiunta di un personaggio. !initialSetting serve per far comparire la scritta quando si aggiunge un personaggio
    if(i==1 || !initialSetting)
        cout<<"(Premere invio)"<<endl;
    cin.ignore();
    string nameCharacter, namePlayer, risk;
    cout<<"Come si chiama il giocatore?"<<endl;
    getline(cin,namePlayer);
    cout<<"Come si chiama il personaggio?"<<endl;
    getline(cin,nameCharacter);
    cout<<"Per cosa sei disposto a rischiare "<<nameCharacter<<"?"<<endl;
    getline(cin,risk);

    auto player = make_unique<Hero>(nameCharacter, namePlayer, risk, i);

    string answer;
    string arc;
    set<string> sQ;
    set<string> sA;
    do{
        cout << player->getNameCharacter() << ", qual e' il tuo archetipo?" << endl;
        cin.ignore();
        getline(cin, arc);

        unsigned int num = 0;
        do{
            cout << "Quante sono le tue qualita'? Max 6" << endl;
            bool e;
            insertNumber(num, e);
        } while (num<1 || num>6);

        cout << "Quali sono?" << endl;
        for (int j = 0; j < num; j++) {//fixme sia qui che sotto c'è un problema per cui il primo carattere, a partire dal secondo elemento del set, non viene considerato
            cout<<"Qualita' numero "<<j+1<<": ";
            cin.ignore();//fixme il problema forse sta qui?
            getline(cin, answer);
            sQ.insert(answer);
        }

        num=0;
        do{
            cout << "Quante sono le tue abilita'? Max 12" << endl;
            bool e;
            insertNumber(num, e);
        }while(num<1 || num>12);

        cout << "Quali sono?" << endl;
        for (int j = 0; j < num; j++) {
            cout<<"abilita' numero "<<j+1<<": ";
            cin.ignore();
            getline(cin, answer);
            sA.insert(answer);
        }

        cout<<"ARCHETIPO: "<<arc<<endl;
        cout<<"QUALITA':"<<endl;
        for(auto const &it1:sQ)
            cout<<it1<<endl;
        cout<<"ABILITA'':"<<endl;
        for(auto const &it2:sA)
            cout<<it2<<endl;

        cout<<"Confermi le tue scelte? y/n"<<endl;
        yesOrNot(answer);

        if(answer=="n") {
            sQ.clear();
            sA.clear();
        }
    }while (answer!="y");

    player->setHeroCharacteristics(arc, sQ, sA);

    playerVector.push_back(std::move(player));
    cout<<"\n\n\n"<<endl;
}

void printPartyIdentity(const vector<unique_ptr<Hero>> &playerVector){
    cout<<"\nIL NOSTRO PARTY:\n"<<endl;
    for(const auto &it : playerVector){
        it->printIdentity();
        cout<<"\nL'inventario di "<<it->getNameCharacter()<<endl;
        it->openItem();
        cout<<"\n\n"<<endl;
    }
}

void setPartyIdentity(vector<unique_ptr<Hero>> &playerVector, unsigned int &numPlayer, const bool loading){

    do {
        cout << "Inserire il numero dei giocatori, massimo 5" << endl;
        bool e;
        insertNumber(numPlayer, e);

    }while (numPlayer < 1 || numPlayer>5);
    cin.ignore();

    for(int i=1;i<=numPlayer;i++){
        setCharacterIdentity(i, playerVector);
    }

    if(!loading){
        setInitialItem(playerVector);
        printPartyIdentity(playerVector);
    }
}


void getFinalPartyIdentity(const vector<unique_ptr<Hero>> &playerVector){
    for(const auto &it : playerVector){
        it->printIdentity();
        if(it->isOutScene())
            cout<<"E' fuori scena"<<endl;
        if(it->isAdrenaline())
            cout<<"E' in adrenalina"<<endl;
        if(it->isConfusion())
            cout<<"E' in confusione"<<endl;
        it->openItem();
        cout<<"\nL'inventario di "<<it->getNameCharacter()<<endl;
        cout<<"\n\n"<<endl;
    }
}

void modifyCharacter(vector<unique_ptr<Hero>> &playerVector, unsigned int const numPlayer){

    unsigned int num=0;
    do {
        cout << "Quale personaggio vuoi modificare?" << endl;
        bool e;
        insertNumber(num, e);
    }while(num<1 || num>numPlayer);

    for(auto &it : playerVector){//ricerca del personaggio da modificare mediante il suo numero
        if(it->getNumberPlayer()==num){
            string answer;
            cout<<"Vuoi reimpostare le generalita'? y/n"<<endl;
            yesOrNot(answer);
            if(answer=="y"){
                cin.ignore();
                it->printIdentity();
                string newCred;
                cout<<"Reinserire il nome del giocatore:"<<" ";
                getline(cin,newCred);
                it->setNamePlayer(newCred);
                cout<<"\nReinserire il nome del personaggio:"<<" ";
                getline(cin,newCred);
                it->setNameCharacter(newCred);
                cout<<"\nPer cosa sei disposto a rischiare "<<it->getNameCharacter()<<"?"<<endl;
                getline(cin,newCred);
                it->setRisk(newCred);
                answer="";
            }

            unsigned int amount=0;
            bool err=false;

            cout<<"Vuoi modificare i tratti? ATTENZIONE:Saranno completamente cancellati e dovranno essere riscritti da capo. y/n"<<endl;
            yesOrNot(answer);

            if(answer=="y"){
                string localAnswer;
                string arc;
                set<string> sQ;
                set<string> sA;
                do{
                    cout << it->getNameCharacter() << ", qual e' il tuo archetipo?" << endl;
                    cin.ignore();
                    getline(cin, arc);
                    unsigned int value = 0;
                    do{
                        cout << "Quante sono le tue qualita'? Max 6" << endl;
                        bool e;
                        insertNumber(value, e);
                    } while (value<1 || value>6);

                    cout << "Quali sono?" << endl;
                    for (int j = 0; j < value; j++) {//fixme sia qui che sotto c'è un problema per cui il primo carattere, a partire dal secondo elemento del set, non viene considerato
                        cout<<"Qualita' numero "<<j+1<<": ";
                        cin.ignore();//fixme il problema forse sta qui?
                        getline(cin, localAnswer);
                        sQ.insert(localAnswer);
                    }

                    value=0;
                    do{
                        cout << "Quante sono le tue abilita'? Max 12" << endl;
                        bool e;
                        insertNumber(value, e);
                    }while(value<1 || value>12);

                    cout << "Quali sono?" << endl;
                    for (int j = 0; j < value; j++) {
                        cout<<"abilita' numero "<<j+1<<": ";
                        cin.ignore();
                        getline(cin, localAnswer);
                        sA.insert(localAnswer);
                    }

                    cout<<"ARCHETIPO: "<<it->getArchetype()<<endl;

                    cout<<"QUALITA':"<<endl;
                    it->printQualities();

                    cout<<"ABILITA':"<<endl;
                    it->printAbilities();

                    cout<<"Confermi le tue scelte? y/n"<<endl;
                    yesOrNot(localAnswer);

                    if(localAnswer=="n") {
                        sQ.clear();
                        sA.clear();
                    }
                }while (localAnswer!="y");

                it->setHeroCharacteristics(arc, sQ, sA);
            }

            answer="";
            it->openItem();
            cout<<"Vuoi modificare l'inventario? ATTENZIONE:Sara' completamente cancellato e dovra' essere rifatto da capo. y/n"<<endl;
            yesOrNot(answer);

            if(answer=="y"){
                it->destroyAllItem();//capire se è possibile incapsulare
                answer="";
                insertItem(answer, it, amount, err);
            }
        }
        printPartyIdentity(playerVector);
    }
}

void removingCharacteristic(unique_ptr<Hero> &playerModified, string &answer, bool &stopped){

    if(answer=="q"){
        cout<<"QUALITA' ATTUALI:"<<endl;
        playerModified->printQualities();
        cout<<"Quale qualita' vuoi rimuovere?"<<endl;
        cin.ignore();
        getline(cin,answer);
        playerModified->removeQuality(answer);
    }
    else if(answer=="a"){
        cout<<"ABILITA' ATTUALI:"<<endl;
        playerModified->printAbilities();
        cout<<"Quale abilita' vuoi rimuovere??"<<endl;
        cin.ignore();
        getline(cin,answer);
        playerModified->removeAbility(answer);
    }
    else{
        stopped=true;
        cout<<"Operazione annullata"<<endl;
    }
}

void addingCharacteristic(unique_ptr<Hero> &playerModified, string &answer, bool stopped= false){
    if(!stopped){//utile quando si annulla l'operazione di modifica
        bool numControl;
        do{
            if(playerModified->getNumQualities()==6 && playerModified->getNumAbilities()==12){
                cout<<"Hai gia' il massimo numero possibile di tratti, impossibile averne altri"<<endl;
                break;
            }

            numControl=false;

            if((answer=="q" && playerModified->getNumQualities()<6) || (answer=="a" && playerModified->getNumAbilities()<12))//controllo per non sforare il numero massimo di abilità e qualità
                numControl=true;
            if(answer=="q" && !numControl)
                cout<<"Hai gia' il massimo numero possibile di qualita'"<<endl;
            if(answer=="a" && !numControl)
                cout<<"Hai gia' il massimo numero possibile di abilita'"<<endl;

        }while(!numControl && answer!="cancel");

        if(answer=="q"){
            cout<<"QUALITA' ATTUALI:"<<endl;
            playerModified->printQualities();
            cout<<"Qual e' la tua nuova qualita'?"<<endl;
            cin.ignore();
            getline(cin,answer);
            playerModified->addQuality(answer);
        }
        else if(answer=="a"){
            cout<<"ABILITA' ATTUALI:"<<endl;
            playerModified->printAbilities();
            cout<<"Qual e' la tua nuova abilita'?"<<endl;
            cin.ignore();
            getline(cin,answer);
            playerModified->addAbility(answer);
        }
        else
            cout<<"Operazione annullata"<<endl;
    }
}



void game(Master &theMaster, vector<unique_ptr<Hero>> &playerVector, unsigned int &numPlayer){//gioco effettivo
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl;
    cout<<"L'AVVENTURA HA INIZIO!"<<endl;

    string command;
    do{
        do {
            command="";
            cout << "\n\n\nScegliere un comando:" << endl;
            cout<<"- h/m per far giocare gli eroi/il master"<<endl;
            cout<<"- modify/add/remove per modificare/aggiungere/rimuovere un personaggio"<<endl;
            cout<<"- endgame per terminare la sessione di gioco"<<endl;
            cin >> command;
        }while(command!="m" && command!="h" && command!="modify" && command!="endgame" && command!="add" && command!="remove");

        if(command=="h"){//GIOCANO GLI EROI
            unsigned int playingCharacter;
            do {
                cout << "A quale giocatore tocca?  " << endl;//rivedere la scritta

                for(const auto &it : playerVector){
                    cout<<"("<<it->getNumberPlayer()<<") "<<it->getNameCharacter()<<endl;
                }
                bool e;
                insertNumber(playingCharacter, e);
            }while(playingCharacter<1 && playingCharacter>numPlayer);

            for(auto &it : playerVector){
                if(playingCharacter==it->getNumberPlayer()){ //il giocatore è stato selezionato, adesso può eseguire le sue azioni

                    cout<<"\n\nTurno di "<<it->getNameCharacter()<<endl;
                    cout<<"Disposto a tutto per: "<<it->getRisk()<<endl;

                    //SE NON è FUORI SCENA
                    if(!it->isOutScene()){

                        if(it->isAdrenaline())//informazioni sul suo status adrenalina e confusione
                            cout<<"ATTENZIONE: Adrenalina e' attiva"<<endl;
                        if(it->isConfusion())
                            cout<<"ATTENZIONE: Confusione e' attiva"<<endl;

                        string action;
                        do {
                            cout<< "Scegli un'azione: superare una prova(t), aprire l'inventario(o), modificare un tratto(c), attendere(w)"<< endl;//NOTA: attendere non fa fare niente al personaggio, è un modo per uscire dal turno senza fare nulla di particolare
                            cin >> action;
                        }while(action!="t" && action!="o" && action!="c" && action!="w");


                        if(action=="t"){
                            unsigned int w = 0, b = 0;
                            bool e;
                            cout << "Inserire i token per l'estrazione" << endl;
                            cout << "Bianchi:"<<endl;
                            insertNumber(w, e);

                            cout << "\nNeri:"<<endl;
                            insertNumber(b, e);
                            it->setBag(w, b);

                            bool isDangerous=false;
                            unsigned int danger=6;//impossibile da raggiungere
                            string answer;
                            cout << "E' pericoloso? y/n"<<endl;//Impostazione dell'eventuale pericolo. EX FUNZION SETDANGER
                            yesOrNot(answer);
                            if(answer=="y"){
                                isDangerous=true;
                                do {
                                    cout << "Quanto e' pericoloso?"<<endl;
                                    bool err;
                                    insertNumber(danger, err);
                                }while(danger>5 || danger<1);//Meccanica del pericolo
                            }
                            else
                                isDangerous=false;

                            unsigned int exVal=0;
                            if(!it->isAdrenaline())
                                exVal = howExtract();

                            it->extract(exVal, danger, isDangerous);

                            if (!it->isOutScene()) {//se non è andato fuori scena può decidere di rischiare
                                cout << "Vuoi rischiare? y/n" << endl;
                                yesOrNot(answer);
                                if(answer=="y"){
                                    if(!it->isAdrenaline()){//se adrenalina non era attivo gli rimarranno (5 - numeroTokenGiàEstratti) da estrarre
                                        it->risk(5 - exVal);//Rischio, il valore è pari ai token rimanenti. Vedi la terza funzione dopo questa
                                        if (isDangerous)
                                            it->goOffScene(danger, it->getBlackExtractedFromBag());//verifica del fuori-scena post rischio
                                    }
                                    else{
                                        it->risk(1);//se adrenalina era attivo gli rimarrà un solo token estraibile
                                        if (isDangerous)
                                            it->goOffScene(danger, it->getBlackExtractedFromBag());
                                    }
                                }
                            }

                            it->setAdrenaline(false);
                            it->setConfusion(false);//dopo l'estrazione tornano automaticamente a falso


                            //NOTA: è necessario tenere separati i due if perché con l'azione di rischio il giocatore potrebbe andare fuori scena
                            if(!it->isOutScene()) {//spartizione neri, nel caso non vada fuori scena.

                                if (it->getBlackExtractedFromBag() != 0) {
                                    cout << "Hai " << it->getBlackExtractedFromBag() << " token neri da smaltire" << endl;
                                    it->blackTokenPartition(theMaster,false);//Vedi la quarta funzione dopo questa. Il flag si riferisce all'essere o meno andato fuori scena
                                    cout << "Spartizione completata" << endl;
                                }
                            }
                            else{
                                it->blackTokenPartition(theMaster, true);
                                cout<<it->getNameCharacter()<<" e' uscito di scena! I suoi token neri andranno tutti al master."<<endl;
                            }


                            it->resetBag();//una volta completata la spartizione dei neri il sacchetto può essere resettato
                        }

                        else if(action=="o"){
                            string answer;
                            unsigned int amount=0;
                            bool err=false;

                            if(it->itemIsEmpty()){//se è vuoto non si possono usare oggetti
                                cout<<"NON HAI OGGETTI NELL'INVENTARIO"<<endl;
                                cout<<"vuoi inserirne? y/n"<<endl;
                                yesOrNot(answer);
                                if(answer=="y")
                                    insertItem(answer, it, amount, err, true);//l'utilizzo di true qui fa sì che venga saltata la domanda iniziale della funzione
                            }

                            if(!it->itemIsEmpty()){//il non metterci l'else fa sì chsi attivi anche dopo ave inserito oggetti nell'eventuale passaggio precedente
                                do{
                                    cout<<"Vuoi usare(u) o aggiungere un oggetto(a). close per chiudere lo zaino"<<endl;
                                    cin>>answer;
                                }while(answer != "u" && answer != "a" && answer!="close");
                            }


                            if(answer=="u"){
                                it->useItem();
                            }

                            else if(answer=="a"){
                                string newObj;
                                amount=0;
                                err=false;
                                insertItem(newObj, it, amount, err, true);
                            }
                        }

                        else if(action=="c"){
                            string answer;
                            bool stopped=false;
                            do{
                                cout<<"Scrivere new/remove/modify per aggiungere/togliere/togliere e reinserire un tratto. Scrivi cancel per annullare"<<endl;
                                cin>>answer;
                            }while(answer!="new" && answer!="remove" && answer!="modify" && answer!="cancel");

                            if(answer=="new"){
                                cout<<"Vuoi aggiungere una qualita' o un'abilita'? q/a      Scrivere cancel per annullare"<<endl;
                                cout<<"ATTENZIONE: ricorda che non puoi avere piu' di 6 qualita' e 12 abilita' (attualmente hai "<<it->getNumQualities()<<" qualita' e "<<it->getNumAbilities()<<" abilita')"<<endl;
                                do{
                                    cin>>answer;
                                } while (answer!="q" && answer!="a" && answer!="cancel");
                                addingCharacteristic(it, answer);
                            }

                            else if(answer=="remove"){
                                cout<<"Vuoi rimuovere una qualita' o un'abilita'? q/a   Scrivere cancel per annullare"<<endl;
                                do{
                                    cin>>answer;
                                }while(answer!="q" && answer!="a" && answer!="cancel");
                                removingCharacteristic(it, answer, stopped);
                            }


                            else if(answer=="modify"){
                                cout<<"Per modificare un tratto prima scegli quale cancellare e poi, subito dopo, quale aggiungere"<<endl;
                                cout<<"Vuoi rimuovere una qualita' o un'abilita'? q/a   Scrivere cancel per annullare"<<endl;
                                do{
                                    cin>>answer;
                                }while(answer!="q" && answer!="a" && answer!="cancel");
                                removingCharacteristic(it, answer, stopped);
                                cout<<"Vuoi aggiungere una qualita' o un'abilita'? q/a      Scrivere cancel per annullare"<<endl;
                                cout<<"ATTENZIONE: ricorda che non puoi avere piu' di 6 qualita' e 12 abilita' (attualmente hai "<<it->getNumQualities()<<" qualita' e "<<it->getNumAbilities()<<" abilita')"<<endl;
                                do{
                                    cin>>answer;
                                } while (answer!="q" && answer!="a" && answer!="cancel");
                                addingCharacteristic(it, answer, stopped);
                            }
                            else
                                cout<<"Operazione annullata"<<endl;
                        }

                        else if(action=="w")
                            cout<<it->getNameCharacter()<<" attende"<<endl;

                    }

                    else{//se è fuori scena
                        cout<<it->getNameCharacter()<<" e' fuori scena!"<<endl;
                        string answer;
                        cout<<it->getNameCharacter()<<" puo' essere immediatamente soccorso? y/n"<<endl;
                        yesOrNot(answer);

                        if(answer=="y"){
                            it->setOutScene(false);
                            cout<<it->getNameCharacter()<<" e' tornato in scena!"<<endl;
                        }

                        else{

                            unsigned int w=0,b=0;
                            bool e;
                            cout<<"Inserire token per la prova del ritorno in scena"<<endl;
                            cout << "Bianchi:"<<endl;
                            insertNumber(w, e);

                            cout << "\nNeri:"<<endl;
                            insertNumber(b, e);

                            unsigned int ext=howExtract();
                            it->returnBack(w, b, ext, theMaster);//setBag sta dentro returnBack
                            if(it->isOutScene())
                                cout<<it->getNameCharacter()<<" non e' riuscito a tornare in scena!"<<endl;
                            else
                                cout<<it->getNameCharacter()<<" e' tornato in scena!"<<endl;
                        }
                    }//tentare di ritornare in scena
                }
            }
        }

        else if(command=="m"){

            string action,exitAnswer;
            do{
                cout<<"Attualmente il master ha in suo possesso "<<theMaster.getUsableBlack()<<" token neri"<<endl;
                if(theMaster.getUsableBlack()){
                    do{
                        cout<<"Complichiamo un po' le cose (t), facciamo un'estrazione (e). Scrivi cancel per annullare"<<endl;
                        cin>>action;
                    }while(action!="t" && action!="e" && action!="cancel");
                }
                else{
                    do{
                        cout<<"Facciamo un'estrazione (e). Scrivi cancel per annullare"<<endl;
                        cin>>action;
                    }while(action!="e" && action!="cancel");
                }



                if(action=="t"){
                    if(theMaster.getUsableBlack()){
                        unsigned int used;
                        do{
                            cout<<"Quanti token utilizzare..."<<endl;
                            bool e;
                            insertNumber(used, e);

                        }while(used>theMaster.getUsableBlack());
                        theMaster.useBlack(used);
                        cout << "Al master sono rimasti " << theMaster.getUsableBlack() << " token neri" << endl;
                    }
                }
                else if(action=="e"){
                    unsigned int w=0,b=0;
                    cout<<"Bianchi:"<<endl;
                    bool e;
                    insertNumber(w,e);

                    cout<<"Neri:"<<endl;
                    insertNumber(b,e);

                    theMaster.setBag(w,b);
                    theMaster.extract(howExtract());
                    theMaster.resetBag();
                }
                else
                    cout<<"Il master ha deciso di non fare nulla"<<endl;

                if(action!="cancel"){
                    cout<<"Il master vuole fare qualcos'altro? y/n"<<endl;
                    yesOrNot(exitAnswer);
                }
                else
                    break;


            }while(exitAnswer=="y");
        }

        else if(command=="modify"){
            modifyCharacter(playerVector, numPlayer);
        }
        else if(command=="add"){//segue l'effettiva creazione di un personaggio
            if(numPlayer<5){
                cin.ignore();
                setCharacterIdentity(numPlayer+1, playerVector, false);//il false è utile per risolvere il problema segnato alla definizione della funzione
                numPlayer++;
                setInitialItemAddedCharacter(playerVector, numPlayer);
                printPartyIdentity(playerVector);
            }
            else
                cout<<"Il party ha gia' il massimo numero di giocatori"<<endl;

        }

        else if(command=="remove"){
            string confirm;
            unsigned int leaving=0;
            printPartyIdentity(playerVector);
                do{
                    cout<<"Quale personaggio lascia il party? (Inserire il suo numero)"<<endl;
                    bool e;
                    insertNumber(leaving, e);
                }while(leaving<1 || leaving>numPlayer);

                cout<<"Confermi di voler definitivamente eliminare il personaggio "<<leaving<< " dal party? y/n"<<endl;
                yesOrNot(confirm);

                if(confirm=="y") {
                    for (auto &it: playerVector) {//ricerca dell'uscente
                        if (leaving == it->getNumberPlayer())
                            cout << it->getNameCharacter() << "\n ha lasciato il party\n" << endl;
                    }

                    playerVector.erase(playerVector.begin() + leaving - 1);//aggiornamento del vettore
                    numPlayer--;

                    int x = 1;//riassegnazione dei numeri dei giocatori
                    for (auto &it: playerVector) {
                        it->setNumberPlayer(x++);
                    }
                    printPartyIdentity(playerVector);
                }
                else
                    cout<<"Operazione annullata"<<endl;
        }
    }while(command!="endgame");

    cout<<"Sessione terminata, ecco il resoconto finale:"<<endl;
    cout<<"Se la vostra storia continua, potete prendere nota del resoconto per reinserire i dati nella funzione di ripristino della lobby \n\n"<<endl;
    getFinalPartyIdentity(playerVector);
}

#endif //SISTEMA_DI_GIOCO_NOT_THE_END_MAINFUNCTIONS_H