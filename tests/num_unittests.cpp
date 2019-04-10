#include "gtest/gtest.h"
#include "num.h"

TEST(basicNumTests, testConstructor)
{
  Num n0(0);
  Num n_neg(-1);
  Num n_pos(42);
  
  EXPECT_EQ(0, n0.getNum());
  EXPECT_EQ(-1, n_neg.getNum());
  EXPECT_EQ(42, n_pos.getNum());
}

TEST(basicNumTests, testSetter)
{
  Num n(123);
  n.setNum(321);

  ASSERT_NE(123, n.getNum());
  ASSERT_EQ(321, n.getNum());
}