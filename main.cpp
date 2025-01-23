// todo inserire comando cancel per annullare le cose
// TODO capire per libreria grafica -> Boost, qt
// todo fare il metodo y/n, aggiornare insertnumber per inserire solo num +

#include "MainFunctions.h"
#include "Master.h"

int main() {
   /* string s="eofj";
   unique_ptr<AbItem> item = make_unique<ConsumableItem>(s,5);
   item->getInfo();
    return 0;*/

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
            do {
                cout << "Confermi questa configurazione per gli eroi? y/n" << endl;
                cout << "Se no, ti verra' chiesto quale eroe vuoi modificare" << endl;
                cin >> confirm;
            } while (confirm != "y" && confirm != "n");

            if (confirm == "n") {
                modifyCharacter(playerVector, numPlayer);
                modified = true;
            }

        } while (modified);

        game(theMaster, playerVector, numPlayer);
    } else {
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

            do {
                cout << it->getNameCharacter() << " era uscito di scena? y/n" << endl;
                cin >> answer;
            } while (answer != "y" && answer != "n");

            if (answer == "y") {
                it->setOutScene(true);//se è fuori scena basta settare il fuori scena e l'inventario, altrimenti bisogna settare anche tutto il resto
                insertItem(answer, it, amount, err);
            }


            if (!it->isOutScene()) {
                do {
                    cout << it->getNameCharacter() << " era in adrenalina? y/n" << endl;
                    cin >> answer;
                } while (answer != "y" && answer != "n");

                if (answer == "y")
                    it->setAdrenaline(true);

                do {
                    cout << it->getNameCharacter() << " era in confusione? y/n" << endl;
                    cin >> answer;
                } while (answer != "y" && answer != "n");

                if (answer == "y")
                    it->setConfusion(true);

                insertItem(answer, it, amount, err);

                cout << "\n\n" << endl;
            }

            getPartyIdentity(playerVector);

            int usableBlack;//ripristino del master
            bool e;
            cout << "Quanti token aveva il master?" << endl;
            insertNumber(usableBlack, e);
            theMaster.addMultipleBlack(usableBlack);

            game(theMaster, playerVector, numPlayer);

        }//ripristino del gioco

        return 0;
    }
}