//
// Created by Giulio Nencini on 28/01/2025.
//
#include <gtest/gtest.h>
#include "NumberFunctions.h"

TEST(NumberFunctionsTest, insertNumber){//c'è interazione con l'utente nel codice commentato
    /*bool e;
    int x=4;
    insertNumber(x, e);
    EXPECT_EQ(x, 4);
    EXPECT_FALSE(e);

    int ex=howExtract();
    EXPECT_LT(ex,5);//perché è strettamente minore
    EXPECT_LT(0,ex);*/

    int max=7,exr= getRandom(max);
    EXPECT_LT(exr,max);

    int wb=getRandomWB();
    EXPECT_LT(wb,2);//estrae o 0 o 1


}