#include "gtest/gtest.h"

extern "C" int64_t StrLen(const char* str);
extern "C" int64_t StrComp(const char* str1, const char* str2);

TEST(StrLen, StrLen) {
  {
    const char* str = "1234567890123";
    EXPECT_EQ(StrLen(str), 13);
  }
  {
    const char* str = "aaaaaa";
    EXPECT_EQ(StrLen(str), 6);
  }
  {
    const char* str = "";
    EXPECT_EQ(StrLen(str), 0);
  }
}

TEST(StrComp, StrComp) {
  {
    const char* str1 = "1239567";
    const char* str2 = "1234567";
    EXPECT_EQ(StrComp(str1, str2), 1);
    EXPECT_EQ(StrComp(str2, str1), -1);
  }
  {
    const char* str1 = "1234568";
    const char* str2 = "1234567";
    EXPECT_EQ(StrComp(str1, str2), 1);
    EXPECT_EQ(StrComp(str2, str1), -1);
  }
  {
    const char* str1 = "";
    const char* str2 = "1234567";
    EXPECT_EQ(StrComp(str1, str2), -1);
    EXPECT_EQ(StrComp(str2, str1), 1);
  }

  {
    const char* str1 = "123456";
    const char* str2 = "123456";
    EXPECT_EQ(StrComp(str1, str2), 0);
    EXPECT_EQ(StrComp(str2, str1), 0);
  }
  {
    const char* str1 = "12345678";
    const char* str2 = "1234567";
    EXPECT_EQ(StrComp(str1, str2), 1);
    EXPECT_EQ(StrComp(str2, str1), -1);
  }
  {
    const char* str1 = "12345678";
    const char* str2 = "32345678";
    EXPECT_EQ(StrComp(str1, str2), -1);
    EXPECT_EQ(StrComp(str2, str1), 1);
  }
  {
    const char* str1 = "";
    const char* str2 = "";
    EXPECT_EQ(StrComp(str1, str2), 0);
    EXPECT_EQ(StrComp(str2, str1), 0);
  }
  {
    const char* str1 = "a";
    const char* str2 = "b";
    EXPECT_EQ(StrComp(str1 + 1, str2 + 1), 0);
  }
}
