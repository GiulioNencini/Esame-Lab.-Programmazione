//
// Created by Giulio Nencini on 28/01/2025.
//


#include "Master.h"
#include <gtest/gtest.h>

class MasterTest : public ::testing::Test {
protected:
    Master m;

    void SetUp() override {
        m.addMultipleBlack(5);
    }
};
TEST_F(MasterTest, TestBlackToken){
    EXPECT_EQ(m.getUsableBlack(), 5);//perché all'inizio ne ho messi 5 e il master parte sempre con 0 token
    m.addBlack();
    EXPECT_EQ(m.getUsableBlack(), 6);
    m.useBlack(4);
    EXPECT_EQ(m.getUsableBlack(), 2);
    m.useBlack(3);
    EXPECT_EQ(m.getUsableBlack(), 2);
    int lastNum=m.getUsableBlack();
    m.addMultipleBlack(10);
    EXPECT_EQ(m.getUsableBlack(), lastNum+10);

}