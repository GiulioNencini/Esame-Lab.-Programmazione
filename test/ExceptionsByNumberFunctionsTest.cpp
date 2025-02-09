#include <gtest/gtest.h>
#include "../NumberAnswerFunctions.h"

TEST(NumberAnswerFunctionsTest, VerifyNumberExceptionsTest) {
    ASSERT_THROW(verifyNumber(-1), NegativeNumberException);
}
//Per quanto riguarda l'eccezione invalidInputException: può essere attivata solo se l'utente inserisce a mano un nonNumero oppure un numero troppo grande che non risulti essere negativo.
//Non posso scrivere ASSERT_THROW(verifyNumber("w"), NegativeNumberException);
//ASSERT_THROW(verifyNumber(std::numeric_limits<int>::max()+1), invalidInputException); non passerebbe perché il numero risulterebbe negativo. Quindi questo test "va un po' a casistiche"
TEST(NumberAnswerFunctionsTest, TestInsertPositiveIntNumberInInterval) {
    ASSERT_THROW(insertPositiveIntNumberInInterval(9, 1, 6), OutOfRangeException);
}

TEST(NumberAnswerFunctionsTest, TestDecrementNotOverZero) {
    ASSERT_THROW(decrementNotOverZero(999, 1000), NotEnoughQuantity);
}

TEST(NumberAnswerFunctionsTest, TestOverFlowPrevention) {
    ASSERT_THROW(overflowPrevention(std::numeric_limits<int>::max() - 1000, 1001), OverflowDanger);
}

TEST(NumberAnswerFunctionsTest, TestVectorZeroOne) {
    vector<int> v;
    v.push_back(0);
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);//valore indesiderato
    ASSERT_THROW(vectorZeroOne(v), std::runtime_error);
}