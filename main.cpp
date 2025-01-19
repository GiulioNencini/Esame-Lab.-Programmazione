// TODO Rifare gli item come oggetti (Con controllo se deve fare un'azione in seguito all'utilizzo), i consumabili hanno la quantità e la funzione che stampa e decrementa il numero. I non invece saranno sempre messi separati. Mettere anche funzione ordinamento
// TODO Registro Missioni, elenco caratteristiche
// TODO capire per libreria grafica -> Boost, qt

#include <iostream>
#include <vector>
#include "MainFunctions.h"
#include "Master.h"
#include "Hero.h"
using namespace std;

int main() {

    string startGame;
    do{
        cout<<"Iniziare una nuova partita (new-game), o riavviarne una (load-game)"<<endl;
        cin>>startGame;
    }while(startGame != "new-game" && startGame != "load-game");//PRELIMINARE


    if(startGame=="new-game"){
        cout<<"\nCREAZIONE DELLA LOBBY\n"<<endl;

        Master theMaster;
        vector<Hero> playerVector;
        unsigned int numPlayer=0;
        bool loading=false;

        setPartyIdentity(theMaster, playerVector, numPlayer, loading);

        bool modified;
        do {
            string confirm;
            modified = false;
            do {
                cout << "Confermi le scelte? y/n" << endl;
                cin >> confirm;
            }while(confirm!="y" && confirm!="n");

            if(confirm=="n") {
                modifyCharacter(playerVector, numPlayer);
                modified=true;
            }

        }while(modified);

        game(theMaster, playerVector, numPlayer);
    }

    else{
        cout<<"\nRIPRISTINO DELLA LOBBY\n"<<endl;

        Master theMaster;
        vector<Hero> playerVector;
        unsigned int numPlayer=0;
        bool loading=true;


        setPartyIdentity(theMaster, playerVector, numPlayer,loading);

        for(auto &it : playerVector){

            string answer;

            do{
                cout<<it.getNameCharacter()<<" era uscito di scena? y/n"<<endl;
                cin>>answer;
            }while(answer!="y" && answer!="n");
            if(answer=="y"){
                it.setOutScene(true);
                do{//fixme item
                    cout<<"Aveva oggetti nell'inventario? y/n"<<endl;
                    cin>>answer;
                }while(answer != "y" && answer!= "n");

                if(answer=="y"){
                    string item;
                    do{
                        cout<<"Inserire l'oggetto"<<endl;
                        cin.ignore();
                        getline(cin, item);
                        it.addItem(item);
                        cout<<"Ne aveva altri? y/n"<<endl;
                        cin>>answer;
                    }while(answer=="y");
                    //it.openItem();
                }
                answer="neutral";
            }


            if(!it.isOutScene()){
                do{
                    cout<<it.getNameCharacter()<<" era in adrenalina? y/n"<<endl;
                    cin>>answer;
                } while (answer!="y" && answer!="n");

                if(answer=="y")
                    it.setAdrenaline(true);
                answer="neutral";

                do{
                    cout<<it.getNameCharacter()<<" era in confusione? y/n"<<endl;
                    cin>>answer;
                } while (answer!="y" && answer!="n");

                if(answer=="y")
                    it.setConfusion(true);

                do{//fixme item
                    cout<<"Aveva oggetti nell'inventario? y/n"<<endl;
                    cin>>answer;
                }while(answer != "y" && answer!= "n");

                if(answer=="y"){
                    string item;
                    do{
                        cout<<"Inserire l'oggetto"<<endl;
                        cin.ignore();
                        getline(cin, item);
                        it.addItem(item);
                        cout<<"Ne aveva altri? y/n"<<endl;
                        cin>>answer;
                    }while(answer=="y");
                    //it.openItem();
                }
            }
            cout<<"\n\n"<<endl;
        }//ripristino dei parametri dei personaggi

        getPartyIdentity(playerVector);

        int ub;//ripristino del master
        bool e;
        cout<<"Quanti token aveva il master?"<<endl;
        insertNumber(ub, e);
        theMaster.addMultipleBlack(ub);

        game(theMaster, playerVector, numPlayer);

    }//ripristino del gioco

    return 0;
}