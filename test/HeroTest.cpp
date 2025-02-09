#include <gtest/gtest.h>
#include "../Hero.h"

class HeroTest : public ::testing::Test {
protected:
    Hero *myHero = new Hero("eroe", "giulio", "risk", 1);
    Master m;
    void SetUp() override {
        myHero->setBag(6, 8);
    }

    void TearDown() override {
        delete myHero;
    }
};

TEST_F(HeroTest, TestConstructor){
    EXPECT_EQ("eroe", myHero->getNameCharacter());
    EXPECT_EQ("giulio", myHero->getNamePlayer());
    EXPECT_EQ("risk", myHero->getRisk());
    EXPECT_EQ(1, myHero->getNumberPlayer());
}

TEST_F(HeroTest, TestGetter) {
    EXPECT_EQ("eroe", myHero->getNameCharacter());
    EXPECT_EQ("giulio", myHero->getNamePlayer());
    EXPECT_EQ("risk", myHero->getRisk());
    EXPECT_FALSE(myHero->isAdrenaline());//di default sono falsi
    EXPECT_FALSE(myHero->isConfusion());
    EXPECT_FALSE(myHero->isOutScene());
    EXPECT_EQ(myHero->getNumberPlayer(), 1);
    //i getter per item e le caratteristiche sono testati negli altri relativi blocchi
}

TEST_F(HeroTest, TestSetter){
    string nP = "NamePlayer", nC="NameCharacter", r="Risk";
    myHero->setNamePlayer(nP);
    myHero->setNameCharacter(nC);
    myHero->setRisk(r);
    myHero->setNumberPlayer(4);
    myHero->setConfusion(true);
    myHero->setAdrenaline(true);
    myHero->setOutScene(true);
    EXPECT_EQ("NamePlayer", myHero->getNamePlayer());
    EXPECT_EQ("NameCharacter", myHero->getNameCharacter());
    EXPECT_EQ("Risk", myHero->getRisk());
    EXPECT_EQ(4, myHero->getNumberPlayer());
    EXPECT_TRUE(myHero->isConfusion());
    EXPECT_TRUE(myHero->isAdrenaline());
    EXPECT_TRUE(myHero->isOutScene());
}

TEST_F(HeroTest, TestSetBag){//Il normale setBag è già testato. Qui si testa quello specifico dell'eroe, particolare, quando confusione è attivo. Se non lo è funziona come quello del master
    EXPECT_FALSE(myHero->isConfusion());//di default è falso
    EXPECT_EQ(myHero->getWhiteFromBag(), 6);
    EXPECT_EQ(myHero->getBlackFromBag(), 8);
    EXPECT_EQ(myHero->getUnknownFromBag(), 0);

    myHero->setConfusion(true);
    myHero->setBag(9, 8);
    EXPECT_GE(myHero->getWhiteFromBag(), 0);
    EXPECT_LE(myHero->getWhiteFromBag(), 9);
    EXPECT_EQ(myHero->getUnknownFromBag(), 9);
    EXPECT_GE(myHero->getBlackFromBag(), 8);
    EXPECT_LE(myHero->getBlackFromBag(), 17);
    //NOTA: Sul numero esatto dei bianchi e neri non predire nulla, è completamente aleatorio. Perché entrambi i valori potrebbero variare come no

}

TEST_F(HeroTest, TestResetBag) {//Qui si testa la questione dei token sconosciuti. Il normale settaggio è già testato in MaterTest
    myHero->setConfusion(true);
    myHero->setBag(500, 1);//È assai probabile che non siano tutti neri. Mettendo confusione testo anche il reset del contatore dei token sconosciuti
    myHero->resetBag();
    EXPECT_EQ(myHero->getWhiteFromBag(), 0);
    EXPECT_EQ(myHero->getBlackFromBag(), 0);
    EXPECT_EQ(myHero->getUnknownFromBag(), 0);
    EXPECT_EQ(myHero->getWhiteExtractedFromBag(), 0);
    EXPECT_EQ(myHero->getBlackExtractedFromBag(), 0);
    EXPECT_EQ(myHero->getSizeExVec(), 0);
}

TEST_F(HeroTest, TestRemoveAndAddHeroCharacteristics) {
    //inserimento
    string archetype = "Guerriero";
    myHero->setArchetype(archetype);
    string q1="Forza", q2="Agilità";
    myHero->insertQuality(q1);
    myHero->insertQuality(q2);
    string a1="Schivata",a2="Finta";
    myHero->insertAbility(a1);
    myHero->insertAbility(a2);

    EXPECT_EQ("Guerriero", myHero->getArchetype());
    ASSERT_EQ(myHero->getNumQualities(), 2);
    ASSERT_EQ(myHero->getNumAbilities(), 2);
    EXPECT_TRUE(myHero->isThereThisQuality(q1));
    EXPECT_TRUE(myHero->isThereThisQuality(q2));
    EXPECT_TRUE(myHero->isThereThisAbility(a1));
    EXPECT_TRUE(myHero->isThereThisAbility(a2));

    //Rimozione
    int initNumQ = myHero->getNumQualities();
    int initNumAb = myHero->getNumAbilities();

    string removingQ="Forza";
    string otherQuality="Agilità";
    string removingA="Schivata";
    string otherAbility="Finta";
    myHero->removeQuality(removingQ);
    EXPECT_EQ(myHero->getNumQualities(), initNumQ - 1);
    EXPECT_TRUE(myHero->isThereThisQuality(otherQuality));
    EXPECT_FALSE(myHero->isThereThisQuality(removingQ));
    myHero->removeAbility(removingA);
    EXPECT_EQ(myHero->getNumAbilities(), initNumAb - 1);
    EXPECT_TRUE(myHero->isThereThisAbility(otherAbility));
    EXPECT_FALSE(myHero->isThereThisAbility(removingA));
}

TEST_F(HeroTest, TestGetAndDeleteFromThisPosition) {//ne ho inseriti due e due per mischiare i tipi (va bene?)
    string a = "a", b = "b", c = "c", d = "d";
    unique_ptr<NormItem> aItem = make_unique<ConsumableItem>(a, 5);
    unique_ptr<NormItem> bItem = make_unique<NormItem>(b);
    unique_ptr<NormItem> cItem = make_unique<ConsumableItem>(c, 6);
    unique_ptr<NormItem> dItem = make_unique<NormItem>(d);
    myHero->addItem(std::move(aItem));
    myHero->addItem(std::move(bItem));
    myHero->addItem(std::move(cItem));
    myHero->addItem(std::move(dItem));
    myHero->openItem();
    int targetPosition = 2;
    unique_ptr<NormItem> const &ref = myHero->getItemFromThisPosition(
            targetPosition);//contando l'ordine di inserimento, l'elemento in pos 2 dovrebbe essere c
    EXPECT_EQ(ref->getName(), "c");
    myHero->deleteItemFromThisPosition(++targetPosition);//dovrebbe essere d per lo stesso ragionamento
    EXPECT_EQ(myHero->getItemSize(), 3);
    EXPECT_FALSE(myHero->isThereSearchedItem("d"));
}

TEST_F(HeroTest, TestAddingAndDeletingItem){//Sia normale che consumable. Dovrebbero verificare, anche se "a pezzi" anche la funzione insertItem, dalle main function
    //Qui si verifica il normale
    int initSize=myHero->getItemSize();
    EXPECT_EQ(initSize, 0);
    string name="item";
    unique_ptr<NormItem> item = make_unique<NormItem>(name);
    EXPECT_EQ("item", item->getName());
    EXPECT_FALSE(myHero->isThereSearchedItem(item->getName()));
    myHero->addItem(std::move(item));
    EXPECT_EQ(myHero->getItemSize(), initSize + 1);//controlla che sia effettivamente inserito, quindi che la dimensione del vettore item sia incrementata di 1
    EXPECT_TRUE(myHero->isThereSearchedItem("item"));
    EXPECT_FALSE(myHero->itemIsEmpty());

    //Qui si verifica il consumabile
    string nc="consumable";
    int amount=3;
    unique_ptr<NormItem> consItem = make_unique<ConsumableItem>(nc, 4);
    EXPECT_EQ("consumable", consItem->getName());
    EXPECT_EQ(4, consItem->getAmount());
    myHero->addItem(std::move(consItem));
    initSize=myHero->getItemSize();//adesso vale 2
    myHero->accumulateThisConsumableItem("consumable", amount);
    EXPECT_EQ(initSize, myHero->getItemSize());//per far vedere che non aggiunge ulteriori oggetti
    unique_ptr<NormItem> const &insCons = myHero->getItemFromThisPosition(1);
    EXPECT_EQ(insCons->getAmount(), 7);
    myHero->accumulateThisConsumableItem("consumable", std::numeric_limits<int>::max());//Qui lancia un'eccezione
    EXPECT_EQ(insCons->getAmount(), std::numeric_limits<int>::max());
    myHero->accumulateThisConsumableItem("consumableNotReal",
                                         5);//Se passo un oggetto che non esiste non accade nulla. Anche se nel programma ci sono controlli preliminari che impediscono questa cosa
    EXPECT_EQ(initSize, myHero->getItemSize());

    myHero->destroyAllItem();
    EXPECT_EQ(myHero->getItemSize(), 0);
    EXPECT_TRUE(myHero->itemIsEmpty());
}

TEST_F(HeroTest, TestGoOffScene){
    int danger = 4;
    myHero->goOffScene(danger, 3);
    EXPECT_FALSE(myHero->isOutScene());
    myHero->goOffScene(danger, 5);//si è superato il pericolo
    EXPECT_TRUE(myHero->isOutScene());
}

TEST_F(HeroTest, TestExtractAndRisk){
    EXPECT_FALSE(myHero->isAdrenaline());
    myHero->setBag(6, 7);
    myHero->extract(2, 6, false);//estraggo 2, senza pericolo
    EXPECT_EQ(myHero->getWhiteExtractedFromBag()+myHero->getBlackExtractedFromBag(), 2);
    int remain = 5-myHero->getWhiteExtractedFromBag()-myHero->getBlackExtractedFromBag();//I token rimanenti per l'estrazione del rischio
    myHero->risk(remain);
    EXPECT_EQ(myHero->getWhiteExtractedFromBag()+myHero->getBlackExtractedFromBag(), 5);

    myHero->resetBag();

    myHero->setAdrenaline(true);
    myHero->setBag(6, 7);
    myHero->extract(2, 6, false);
    EXPECT_EQ(myHero->getWhiteExtractedFromBag()+myHero->getBlackExtractedFromBag(), 4);//Con adrenalina si estrae comunque 4
    remain = 5-myHero->getWhiteExtractedFromBag()-myHero->getBlackExtractedFromBag();//I token rimanenti per l'estrazione del rischio
    myHero->risk(remain);
    EXPECT_EQ(myHero->getWhiteExtractedFromBag()+myHero->getBlackExtractedFromBag(), 5);
}

TEST_F(HeroTest, TestBlackTokenPartition){//si tratta di ripetere 4 volte la procedura, ogni volta con un input diverso
    string choice;

    //choice m
    EXPECT_EQ(m.getUsableBlack(), 0);
    myHero->setBag(0, 4);
    EXPECT_FALSE(myHero->isConfusion());
    EXPECT_FALSE(myHero->isAdrenaline());
    myHero->extract(4, 6, false);//un'estrazione senza pericolo e senza adrenalina o confusione
    choice="m";//comando per darli tutti al master
    myHero->blackTokenPartition(m, choice);
    EXPECT_EQ(m.getUsableBlack(),4);

    myHero->resetBag();
    //Le condizioni saranno le stesse, eccetto per il fatto che il master adesso ha 4 token

    //choice a
    myHero->setBag(0, 4);
    EXPECT_FALSE(myHero->isConfusion());
    EXPECT_FALSE(myHero->isAdrenaline());
    myHero->extract(4, 6, false);
    choice="a";//comando per darli tutti al master
    myHero->blackTokenPartition(m, choice);
    EXPECT_TRUE(myHero->isAdrenaline());
    EXPECT_EQ(m.getUsableBlack(),4+3);

    myHero->resetBag();
    myHero->setAdrenaline(false);

    //choice c
    myHero->setBag(0, 4);
    EXPECT_FALSE(myHero->isConfusion());
    EXPECT_FALSE(myHero->isAdrenaline());
    myHero->extract(4, 6, false);
    choice="c";//comando per darli tutti al master
    myHero->blackTokenPartition(m, choice);
    EXPECT_TRUE(myHero->isConfusion());
    EXPECT_EQ(m.getUsableBlack(),4+3+3);

    myHero->resetBag();
    myHero->setConfusion(false);

    //choice ac
    myHero->setBag(0, 4);
    EXPECT_FALSE(myHero->isConfusion());
    EXPECT_FALSE(myHero->isAdrenaline());
    myHero->extract(4, 6, false);
    choice="ac";//comando per darli tutti al master
    myHero->blackTokenPartition(m, choice);
    EXPECT_TRUE(myHero->isConfusion());
    EXPECT_TRUE(myHero->isAdrenaline());
    EXPECT_EQ(m.getUsableBlack(),4+3+3+2);
}

TEST_F(HeroTest,
       TestReturnBack) {//Per verificare il ritorno o meno farò due estrazioni distinte: una sicuramente di successo, l'altra di sicuro fallimento. extract() è già stata testata
    myHero->setOutScene(true);
    myHero->returnBack(1, 1, 2);//1 bianco, 1 nero, 2 estratti: impossibile fallire
    EXPECT_FALSE(myHero->isAdrenaline());
    EXPECT_FALSE(myHero->isConfusion());
    EXPECT_FALSE(myHero->isOutScene());

    myHero->resetBag();

    myHero->setOutScene(true);
    myHero->returnBack(0, 3, 2);//nessun bianco: fallimento assicurato
    EXPECT_TRUE(myHero->isOutScene());

    myHero->resetBag();
}

//eccezioni

TEST_F(HeroTest, SetNumberPlayer_InvalidValue) {
    ASSERT_THROW(myHero->setNumberPlayer(-1), std::runtime_error);
    ASSERT_THROW(myHero->setNumberPlayer(0), std::runtime_error);
}

TEST_F(HeroTest, DeleteItemFromThisPosition_InvalidPosition) {
    ASSERT_THROW(myHero->deleteItemFromThisPosition(1), std::runtime_error);
    unique_ptr<NormItem> newItem = make_unique<NormItem>("item");
    myHero->addItem(std::move(newItem));
    ASSERT_THROW(myHero->deleteItemFromThisPosition(5), std::runtime_error);
}

TEST_F(HeroTest, GetItemFromThisPosition_InvalidPosition) {
    EXPECT_EQ(myHero->getItemSize(), 0);
    ASSERT_THROW(myHero->getItemFromThisPosition(1), std::runtime_error);
    unique_ptr<NormItem> newItem = make_unique<NormItem>("item");
    myHero->addItem(std::move(newItem));
    ASSERT_THROW(myHero->getItemFromThisPosition(5), std::runtime_error);
}

TEST_F(HeroTest, GoOffScene_InvalidValues) {
    ASSERT_THROW(myHero->goOffScene(-1, 1), std::runtime_error);
    ASSERT_THROW(myHero->goOffScene(1, -1), std::runtime_error);
}

TEST_F(HeroTest, SetBag_InvalidValues) {
    ASSERT_THROW(myHero->setBag(-1, 1), std::runtime_error);
    ASSERT_THROW(myHero->setBag(1, -1), std::runtime_error);
}