//
// Created by Giulio Nencini on 28/01/2025.
//
#include "ConsumableItem.h"
#include "Item.h"
#include <gtest/gtest.h>

TEST(ConsumableItem, ConsumableItem){
    string name="consumabile";
    unique_ptr<ConsumableItem> c = make_unique<ConsumableItem>(name, 3);
    ASSERT_EQ(c->getAmount(),3);
    EXPECT_EQ("consumabile", c->getName());
}

TEST(Item, Item){
    string name="oggetto";
    unique_ptr<Item> i = make_unique<Item>(name);
    EXPECT_EQ("oggetto", i->getName());
}