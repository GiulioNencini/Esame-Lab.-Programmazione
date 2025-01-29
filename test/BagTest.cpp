//
// Created by Giulio Nencini on 28/01/2025.
//
#include "gtest/gtest.h"
#include "Bag.h"

class BagTest : public ::testing::Test {
protected:
    Bag bag;

    void SetUp() override {
        bag.setWhite(5);
        bag.setBlack(3);
        bag.setUnknown(2);
    }
};

TEST_F(BagTest, ResetAllValues) {
    bag.reset();
    EXPECT_EQ(bag.getWhite(), 0);
    EXPECT_EQ(bag.getBlack(), 0);
    EXPECT_EQ(bag.getUnknown(), 0);
    EXPECT_EQ(bag.getWhiteExtracted(), 0);
    EXPECT_EQ(bag.getBlackExtracted(), 0);
    EXPECT_EQ(bag.extractionVector.size(), 0);

}