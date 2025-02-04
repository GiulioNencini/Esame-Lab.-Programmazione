//
// Created by Giulio Nencini on 28/01/2025.
//
#include "../ConsumableItem.h"
#include <gtest/gtest.h>

TEST(NormItem, NormItem){
    string name="oggetto";
    unique_ptr<NormItem> i = make_unique<NormItem>(name);//costruttore
    EXPECT_EQ("oggetto", i->getName());

    EXPECT_FALSE(i->isConsumable());
    EXPECT_EQ(i->getAmount(),1);
}

TEST(ConsumableItem, ConsumableItem){
    string name="consumabile";
    unique_ptr<ConsumableItem> c = make_unique<ConsumableItem>(name, 3);
    EXPECT_EQ(c->getAmount(),3);
    EXPECT_EQ("consumabile", c->getName());

    c->setAmount(76);
    EXPECT_EQ(c->getAmount(), 76);

    EXPECT_TRUE(c->isConsumable());
}
