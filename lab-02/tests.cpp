#include "gtest/gtest.h"
#include <iostream>

extern "C" const char* Positivity(int64_t x);
extern "C" bool CheckOverflow(int64_t x, int64_t y);
extern "C" int64_t Function(int64_t x);
extern "C" bool IsInCircle(int64_t x, int64_t y, int64_t d);
extern "C" bool TwoIntegers(int64_t x, int64_t y);
extern "C" int8_t CountNumbers(int64_t a, int64_t b, int64_t c);
extern "C" const char* Switch(int64_t k);
extern "C" int8_t MagicMetric(int64_t x);

// ---------------------------------------------------------

TEST(Positivity, Positivity) {
  std::string pos_str = "Yeah) It's positive :D";
  std::string neg_str = "Ohh.. so much negative :(";
  ASSERT_EQ(Positivity(1), pos_str);
  ASSERT_EQ(Positivity(-1), neg_str);
  ASSERT_EQ(Positivity(0), neg_str);
}

TEST(CheckOverflow, CheckOverflow) {
  ASSERT_EQ(CheckOverflow(1,1), false);
  ASSERT_EQ(CheckOverflow(0,0xFFFFFFFF), true);
}

TEST(Function, Function) {
  ASSERT_EQ(Function(-2), 5);
  ASSERT_EQ(Function(-1), 3);
  ASSERT_EQ(Function(0), 4);
  ASSERT_EQ(Function(4), -10);
  ASSERT_EQ(Function(10), 4);
  ASSERT_EQ(Function(17), 7);
  ASSERT_EQ(Function(20), -8002);
}

TEST(IsInCircle, IsInCircle) {
  ASSERT_TRUE(IsInCircle(1, 0, 2));
  ASSERT_TRUE(IsInCircle(1, -1, 3));
  ASSERT_TRUE(IsInCircle(0, 0, 1));
  ASSERT_TRUE(IsInCircle(4, 2, 9));
  ASSERT_FALSE(IsInCircle(2,-1,4));
  ASSERT_FALSE(IsInCircle(-4,-1,8));
  ASSERT_FALSE(IsInCircle(1,1,2));
}

TEST(TwoIntegers, TwoIntegers) {
  ASSERT_TRUE(TwoIntegers(1, 7));
  ASSERT_TRUE(TwoIntegers(4, 2));
  ASSERT_TRUE(TwoIntegers(123321, 11));
  ASSERT_TRUE(TwoIntegers(3, 9));
  ASSERT_TRUE(TwoIntegers(11, 11));
  ASSERT_FALSE(TwoIntegers(11, 111));
  ASSERT_FALSE(TwoIntegers(4, 15));
  ASSERT_FALSE(TwoIntegers(6, 4));
}

TEST(CountNumbers, CountNumbers) {
  ASSERT_EQ(CountNumbers(1, 2, 3), 0);
  ASSERT_EQ(CountNumbers(2, 5, 3), 2);
  ASSERT_EQ(CountNumbers(2, 4, 3), 1);
  ASSERT_EQ(CountNumbers(22, 44, 6), 0);
  ASSERT_EQ(CountNumbers(22, 41, 6), 1);
}

TEST(Switch, Switch) {
  std::string case_1_str = "That's bad";
  std::string case_2_str = "No comments.";
  std::string case_3_str = "Not bad...";
  std::string case_4_str = "Nice :)";
  std::string case_5_str = "Perfecto!!!";
  std::string default_str = "Ooops";
  ASSERT_EQ(Switch(0), case_1_str);
  ASSERT_EQ(Switch(1), case_1_str);
  ASSERT_EQ(Switch(2), case_1_str);
  ASSERT_EQ(Switch(3), default_str);
  ASSERT_EQ(Switch(4), case_2_str);
  ASSERT_EQ(Switch(5), case_1_str);
  ASSERT_EQ(Switch(43), case_2_str);
  ASSERT_EQ(Switch(-100), case_4_str);
  ASSERT_EQ(Switch(13), case_3_str);
  ASSERT_EQ(Switch(1000), case_5_str);
  ASSERT_EQ(Switch(1001), default_str);
}
// ---------------------------------------------------------