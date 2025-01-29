//
// Created by Giulio Nencini on 28/01/2025.
//
#include <gtest/gtest.h>
#include "MainFunctions.h"
class MainFunctionTest : public ::testing::Test {
protected:
unique_ptr<Hero> h = make_unique<Hero>("nome", "eroe", "rischio", 1);
    void SetUp() override {
        string archetype = "Guerriero";
        h->setArchetype(archetype);
        string q1="Forza", q2="Agilità";
        h->insertQuality(q1);
        h->insertQuality(q2);
        string a1="Schivata",a2="Finta";
        h->insertAbility(a1);
        h->insertAbility(a2);
    }
};
TEST_F(MainFunctionTest, removingAddingCharacteristic){
    int initNumQ=h->getNumQualities();
    int initNumAb=h->getNumAbilities();

    string removingQ="Forza";
    string copyRemovingQ="Forza";
    string otherQuality="Agilità";
    string removingA="Schivata";
    string copyRemovingA="Schivata";
    string otherAbility="Finta";
    h->removeQuality(removingQ);
    EXPECT_EQ(h->getNumQualities(), initNumQ-1);
    EXPECT_TRUE(h->isThereThisQuality(otherQuality));
    EXPECT_FALSE(h->isThereThisQuality(copyRemovingQ));
    h->removeAbility(removingA);
    EXPECT_EQ(h->getNumAbilities(), initNumAb-1);
    EXPECT_TRUE(h->isThereThisAbility(otherAbility));
    EXPECT_FALSE(h->isThereThisAbility(copyRemovingA));

    string addingQ="Destrezza";
    string copyAddingQ="Destrezza";
    string addingA="Scatto";
    string copyAddingA="Scatto";

    h->addQuality(addingQ);
    EXPECT_EQ(h->getNumQualities(),initNumQ);
    EXPECT_TRUE(h->isThereThisQuality(copyAddingQ));
    h->addAbility(addingA);
    EXPECT_EQ(h->getNumAbilities(),initNumAb);
    EXPECT_TRUE(h->isThereThisAbility(copyAddingA));

}