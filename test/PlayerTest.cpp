//
// Created by Giulio Nencini on 28/01/2025.
//
#include <gtest/gtest.h>
#include "Master.h"

class PlayerTest : public ::testing::Test {
protected:
    Master m;//master usa questo metodo per estrarre
    void SetUp() override {
        m.setBag(5, 6);//già testato in bagTest
    }
};

TEST_F(PlayerTest, deleteExtractedToken){

    int preSize = 11;//il totale dei token
    cout<<preSize<<endl;
    m.extract(3);
    EXPECT_EQ(preSize-3, m.getSizeExVec());
    EXPECT_EQ(5-m.getWhiteExtractedFromBag(), m.getWhiteFromBag());
    EXPECT_EQ(6-m.getBlackExtractedFromBag(), m.getBlackFromBag());

}