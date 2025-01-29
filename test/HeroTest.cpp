//
// Created by Giulio Nencini on 28/01/2025.
//
#include <gtest/gtest.h>
#include "Hero.h"

class HeroTest : public ::testing::Test {
protected:
    Hero *h = new Hero("eroe", "giulio", "risk", 1);
    Master m;
    void SetUp() override {
    }

    void TearDown() override {
        delete h;
    }
};

TEST_F(HeroTest, Constructor){
    EXPECT_EQ("eroe", h->getNameCharacter());
    EXPECT_EQ("giulio", h->getNamePlayer());
    EXPECT_EQ("risk", h->getRisk());
    EXPECT_EQ(1, h->getNumberPlayer());
}

TEST_F(HeroTest, TestSetHeroCharacteristics) {//la rimozione e aggiunzione è testata in MainFunctionsTest
    string archetype = "Guerriero";
    h->setArchetype(archetype);
    string q1="Forza", q2="Agilità";
    h->insertQuality(q1);
    h->insertQuality(q2);
    string a1="Schivata",a2="Colpo Poderoso";
    h->insertAbility(a1);
    h->insertAbility(a2);

    EXPECT_EQ("Guerriero", h->getArchetype());
    ASSERT_EQ(h->getNumQualities(), 2);
    ASSERT_EQ(h->getNumAbilities(), 2);
    EXPECT_TRUE(h->isThereThisQuality(q1));
    EXPECT_TRUE(h->isThereThisQuality(q2));
    EXPECT_TRUE(h->isThereThisAbility(a1));
    EXPECT_TRUE(h->isThereThisAbility(a2));
}

TEST_F(HeroTest, TestAddingAndDeletingItem){//Sia normale che consumable. Dovrebbero verificare, anche se "a pezzi" anche la funzione insertItem, dalle main function
    string n="item";
    unique_ptr<AbItem> item = make_unique<Item>(n);
    int initSize=h->getItemSize();
    h->addItem(std::move(item));
    EXPECT_EQ(h->getItemSize(), initSize+1);//controlla che sia effettivamente inserito, quindi che la dimensione del vettore item sia incrementata di 1
    EXPECT_TRUE(h->isThereSearchedItem(n));
    EXPECT_FALSE(h->itemIsEmpty());

    h->destroyAllItem();
    EXPECT_EQ(h->getItemSize(),0);
    EXPECT_TRUE(h->itemIsEmpty());

    /*string nc="consumable";
    int amount=3;
    unique_ptr<AbItem> consItem = make_unique<ConsumableItem>(nc, 4);
    initSize=h->getItemSize();
    h->addItem(std::move(consItem));
    EXPECT_TRUE(h->isThereThisConsumableItem((string&)"consumable", amount));//verifica che fosse già presente (perché effettivamente inserito alla riga 56), quindi che la dimensione del vettore rimanga uguale
    EXPECT_EQ(initSize, h->getItemSize());*/
}

TEST_F(HeroTest, TestSetBag){//Il normale setBag è già testato. Qui si testa quello specifico dell'eroe, particolare, quando confusione è attivo. Se non lo è funziona come quello del master
    h->setConfusion(false);
    h->setBag(6, 8);
    EXPECT_EQ(h->getWhiteFromBag(),6);
    EXPECT_EQ(h->getBlackFromBag(),8);

    h->setConfusion(true);
    h->setBag(6, 8);
    EXPECT_EQ(h->getUnknownToken(), 6);

}

TEST_F(HeroTest, TestSetDanger) {
    int danger = 6;//come nel codice
    bool isDangerous = false;
    string yes="y", no="n";
    Hero::setDanger(danger, isDangerous, yes);//NOTA IMPORTANTE: Per questa piccola modifica apportata qui (ricevimento in ingresso dalla risposta) e a causa del problema momentaneo che sto avendo con l'eseguibile non posso ricompilare, quindi qui non posso testare
    EXPECT_TRUE(isDangerous);
    EXPECT_LT(danger, 6);
    EXPECT_LT(1, danger);
    danger = 6;
    Hero::setDanger(danger, isDangerous, no);
    EXPECT_FALSE(isDangerous);
    EXPECT_EQ(danger, 6);
}

TEST_F(HeroTest, TestGoOffScene){
    int danger = 4;
    h->goOffScene(danger, 3);
    EXPECT_FALSE(h->isOutScene());
    h->goOffScene(danger, 5);//si è superato il pericolo
    EXPECT_TRUE(h->isOutScene());

}

TEST_F(HeroTest, TestBlackPartition){//testato nel caso del fuori scena
    int exBlack=5;
    h->setBlackExtracted(exBlack);
    h->setOutScene(true);
    h->blackTokenPartition(m, h->isOutScene());
    EXPECT_EQ(m.getUsableBlack(), exBlack);

    /*h->setOutScene(false);//problema per via dell'interazione con l'utente
    h->setBlackExtracted(exBlack);
    h->blackTokenPartition(m, h->isOutScene());
    int preBlackTokenMaster=m.getUsableBlack();
    EXPECT_LE(m.getUsableBlack(), preBlackTokenMaster+exBlack-3);//al massimo 2 neri non andranno al master
    EXPECT_EQ(h->getBlackExtractedFromBag(), 0);*/
}