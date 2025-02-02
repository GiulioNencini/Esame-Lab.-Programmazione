#include "MainFunctions.h"
#include "Master.h"
//todo rivedere classe bag, item(capire quali parti tenere) e metodo statico. Togliere i cout dalle funzioni e e le domande dalle funzioni. Rivedere inoltre le invarianti dei setter e il corretto assegnamento di const
//todo una volta rivista anche l'interfaccia di interazione rivedere lo ut, non prima di aver corretto il codice cmake
int main() {
    string startGame;
    do {
        cout << "Iniziare una nuova partita (n), o riavviarne una (l)" << endl;
        cin >> startGame;
    } while (startGame != "n" && startGame != "l");//PRELIMINARE


    if (startGame == "n") {
        cout << "\nCREAZIONE DELLA LOBBY\n" << endl;

        Master theMaster;
        vector<unique_ptr<Hero>> playerVector;
        unsigned int numPlayer = 0;
        bool loading = false;

        setPartyIdentity(playerVector, numPlayer, loading);

        bool modified;
        do {
            string confirm;
            modified = false;
            cout << "Confermi questa configurazione per gli eroi? y/n" << endl;
            cout << "Se no, ti verra' chiesto quale eroe vuoi modificare" << endl;
            yesOrNot(confirm);

            if (confirm == "n") {
                modifyCharacter(playerVector, numPlayer);
                modified = true;
            }

        } while (modified);

        game(theMaster, playerVector, numPlayer);
    }

    else {
        cout << "\nRIPRISTINO DELLA LOBBY\n" << endl;

        Master theMaster;
        vector<unique_ptr<Hero>> playerVector;
        unsigned int numPlayer = 0;
        bool loading = true;


        setPartyIdentity(playerVector, numPlayer, loading);

        string answer;
        unsigned int amount=0;
        bool err;
        for (auto &it: playerVector) {

            answer="";
            amount=0;

            cout << it->getNameCharacter() << " era uscito di scena? y/n" << endl;
            yesOrNot(answer);

            if (answer == "y") {
                it->setOutScene(true);//se è fuori scena basta settare il fuori scena e l'inventario, altrimenti bisogna settare anche tutto il resto
                insertItem(answer, it, amount, err);
            }


            if (!it->isOutScene()) {
                cout << it->getNameCharacter() << " era in adrenalina? y/n" << endl;
                yesOrNot(answer);

                if (answer == "y"){
                    it->setAdrenaline(true);
                    cout<<it->getNameCharacter()<<" e' in adrenalina"<<endl;
                }
                answer="";

                cout << it->getNameCharacter() << " era in confusione? y/n" << endl;
                yesOrNot(answer);

                if (answer == "y"){
                    it->setConfusion(true);
                    cout<<it->getNameCharacter()<<" e' confuso"<<endl;
                }


                insertItem(answer, it, amount, err);

                cout << "\n\n" << endl;
            }

            printPartyIdentity(playerVector);

            unsigned int usableBlack;//ripristino del master
            bool e;
            cout << "Quanti token aveva il master?" << endl;
            insertNumber(usableBlack, e);
            theMaster.addUsableBlack(usableBlack);
            cout<<"Il master ha ricevuto "<<usableBlack<<" token"<<endl;

            game(theMaster, playerVector, numPlayer);
        }
    }
    return 0;
}