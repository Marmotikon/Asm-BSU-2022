#include "gtest/gtest.h"

extern "C" int32_t AsmBitCount(uint64_t n);
extern "C" int64_t AsmFactorial(int32_t n);
extern "C" bool AsmIsSquare(int64_t x);
extern "C" int32_t AsmRemoveDigits(int32_t x);
extern "C" int64_t AsmFormula(int64_t x, int64_t n);
extern "C" uint64_t AsmBankDeposit(
    uint64_t initial_sum, int32_t percentage, int32_t years);
extern "C" uint16_t AsmEvenDivisors(uint16_t n);
extern "C" uint64_t AsmInfiniteManipulations(uint64_t x);

// ---------------------------------------------------------

TEST(AsmBitCount, AsmBitCount) {
  ASSERT_EQ(AsmBitCount(1), 1);
  ASSERT_EQ(AsmBitCount(5), 2);
  ASSERT_EQ(AsmBitCount(0), 0);
  ASSERT_EQ(AsmBitCount(2), 1);
}

TEST(AsmFactorial, AsmFactorial) {
  ASSERT_EQ(AsmFactorial(1), 2);
  ASSERT_EQ(AsmFactorial(2), 6);
  ASSERT_EQ(AsmFactorial(3), 6);
  ASSERT_EQ(AsmFactorial(0xFFFFFFFF), 6227020800);
}

TEST(AsmIsSquare, AsmIsSquare) {
  ASSERT_TRUE(AsmIsSquare(1));
  ASSERT_TRUE(AsmIsSquare(4));
  ASSERT_TRUE(AsmIsSquare(9));
  ASSERT_TRUE(AsmIsSquare(121));
  ASSERT_TRUE(AsmIsSquare(0xFFFE0001));
  ASSERT_TRUE(AsmIsSquare(0x7FFFFFFE9EA1DC29));
  ASSERT_FALSE(AsmIsSquare(2));
  ASSERT_FALSE(AsmIsSquare(8));
  // bool a = AsmIsSquare(1000);
  ASSERT_FALSE(AsmIsSquare(1000));
  ASSERT_FALSE(AsmIsSquare(0x7FFFFFFE9EA1DC30));
  ASSERT_FALSE(AsmIsSquare(3));
  ASSERT_FALSE(AsmIsSquare(0x7FFFFFFFFFFFFFFF));
}

TEST(AsmRemoveDigits, AsmRemoveDigits) {
  ASSERT_EQ(AsmRemoveDigits(3427811), 3711);
  ASSERT_EQ(AsmRemoveDigits(339911), 339911);
  ASSERT_EQ(AsmRemoveDigits(204288101), 11);
  ASSERT_EQ(AsmRemoveDigits(60428), 0);
  ASSERT_EQ(AsmRemoveDigits(0x7FFFFFFF/* 2147483647 */), 1737);
  ASSERT_EQ(AsmRemoveDigits(0), 0);
  ASSERT_EQ(AsmRemoveDigits(-3427811), -3711);
  ASSERT_EQ(AsmRemoveDigits(-339911), -339911);
  ASSERT_EQ(AsmRemoveDigits(-204288101), -11);
  ASSERT_EQ(AsmRemoveDigits(-60428), 0);
  ASSERT_EQ(AsmRemoveDigits(-0x7FFFFFFF/* 2147483647 */), -1737);
}

TEST(AsmFormula, AsmFormula) {
  ASSERT_EQ(AsmFormula(2, 2), 0);
  ASSERT_EQ(AsmFormula(3, 2), 6);
  ASSERT_EQ(AsmFormula(1, 5), -36);
  ASSERT_EQ(AsmFormula(0xFFFFFFFF, 5), -1);
}

TEST(AsmBankDeposit, AsmBankDeposit) {
  ASSERT_EQ(AsmBankDeposit(2, 50, 1), 3);
  ASSERT_EQ(AsmBankDeposit(100, 13, 3), 143);
  ASSERT_EQ(AsmBankDeposit(0x4000000000000, 0, 100), 0x4000000000000);
  ASSERT_EQ(AsmBankDeposit(0x4000000000000, 100, 0), 0x4000000000000);
  // int64_t a = AsmBankDeposit(0x4FFFFFFFFFFFF, 20, 3);
  ASSERT_EQ(AsmBankDeposit(281474976710655, 20, 7), 1008575732230063);
}

TEST(AsmEvenDivisors, AsmEvenDivisors) {
  ASSERT_EQ(AsmEvenDivisors(5), 1);
}

TEST(AsmInfiniteManipulations, AsmInfiniteManipulations) {
  ASSERT_EQ(AsmInfiniteManipulations(1),
            9'223'372'036'854'775'807ull);
  ASSERT_EQ(AsmInfiniteManipulations(9'223'372'036'854'775'807),
            9'223'372'036'854'775'807ull);
  ASSERT_EQ(AsmInfiniteManipulations(-1), 0);
  ASSERT_EQ(AsmInfiniteManipulations(0), 0);
}

// ---------------------------------------------------------
