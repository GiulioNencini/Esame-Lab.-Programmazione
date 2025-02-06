//
// Created by Giulio Nencini on 28/01/2025.
//


#include "../Master.h"
#include <gtest/gtest.h>

class MasterTest : public ::testing::Test {
protected:
    Master m;

    void SetUp() override {
        m.setBag(5, 6);
        m.addUsableBlack(5);
    }
};

TEST_F(MasterTest, TestAddAndUseBlackToken) {
    EXPECT_EQ(m.getUsableBlack(), 5);//perché all'inizio ne ho messi 5 e il master parte sempre con 0 token
    m.addUsableBlack(1);
    EXPECT_EQ(m.getUsableBlack(), 6);
    m.useBlack(4);
    EXPECT_EQ(m.getUsableBlack(), 2);
    m.useBlack(3);//non può perché ne sono rimasti solo 2
    EXPECT_EQ(m.getUsableBlack(), 2);
    int lastNum=m.getUsableBlack();
    m.addUsableBlack(10);
    EXPECT_EQ(m.getUsableBlack(), lastNum+10);
    m.addUsableBlack(0);
    EXPECT_EQ(m.getUsableBlack(), lastNum + 10);
}

TEST_F(MasterTest, TestSetBag){
    EXPECT_EQ(m.getWhiteFromBag(),5);
    EXPECT_EQ(m.getBlackFromBag(),6);
    EXPECT_EQ(m.getUnknownFromBag(),0);//solo l'eroe può possedere dei token sconosciuti
}

//NOTA: i metodi testati qui sono quelli sviluppati nella classe astratta Player
TEST_F(MasterTest, TestDeleteExtractedToken){
    int preSize = 11;//il totale dei token
    cout<<preSize<<endl;
    m.extract(3);
    EXPECT_EQ(preSize-3, m.getSizeExVec());//verifica che l'elemento estratto sia stato cancellato dal vettore
    EXPECT_EQ(5-m.getWhiteExtractedFromBag(), m.getWhiteFromBag());//verifica che i bianchi estratti non siano più estraibili
    EXPECT_EQ(6-m.getBlackExtractedFromBag(), m.getBlackFromBag());//verifica che i neri estratti non siano più estraibili
}

TEST_F(MasterTest, TestExtract) {
    m.setBag(6, 7);
    m.extract(3);
    EXPECT_EQ(m.getWhiteExtractedFromBag() + m.getBlackExtractedFromBag(), 3);
    EXPECT_EQ(m.getSizeExVec(), 10);

    m.resetBag();

    //Il messaggio di errore si riferisce al fatto che ci fossero solo 2 token estraibili contro i 3 richiesti
    m.setBag(1, 1);
    m.extract(3);
    EXPECT_EQ(m.getWhiteExtractedFromBag() + m.getBlackExtractedFromBag(), 2);
    EXPECT_EQ(m.getSizeExVec(), 0);

    //m.extract(-5);//per l'eccezione
}

TEST_F(MasterTest, TestBagIsEmpty){
    m.setBag(1,2);
    m.extract(2);
    EXPECT_FALSE(m.bagIsEmpty());
    m.extract(1);
    EXPECT_TRUE(m.bagIsEmpty());
}

TEST_F(MasterTest, TestSetAndResetBag) {
    m.resetBag();
    EXPECT_EQ(m.getWhiteFromBag(), 0);
    EXPECT_EQ(m.getBlackFromBag(), 0);
    EXPECT_EQ(m.getUnknownFromBag(), 0);
    EXPECT_EQ(m.getWhiteExtractedFromBag(), 0);
    EXPECT_EQ(m.getBlackExtractedFromBag(), 0);
    EXPECT_EQ(m.getSizeExVec(), 0);
}