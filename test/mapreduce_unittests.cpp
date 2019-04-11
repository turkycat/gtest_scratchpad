#include "mapreducer.h"
#include "gtest/gtest.h"
#include <malloc.h>

class MapReducerFixture : public testing::Test
{
protected:
  MapReducer<int> m0;
  MapReducer<int> m1;
  MapReducer<int> m2;
  int *one;
  int *two;

  void SetUp() override
  {
    one = (int*)malloc(sizeof(int));
    two = (int*)malloc(sizeof(int));
    *one = 1;
    *two = 2;
    m1.addFirst(one);
    m2.addLast(one);
    m2.addLast(two);
  }
};

TEST_F(MapReducerFixture, testEmptyMap)
{
  ASSERT_EQ(0, m0.size());
  ASSERT_EQ(nullptr, m0.getFirst());
  ASSERT_EQ(nullptr, m0.getLast());
}

TEST_F(MapReducerFixture, testAddFirst)
{
  //verify current size
  EXPECT_EQ(0, m0.size());

  //try to add an invalid item
  ASSERT_FALSE(m0.addFirst(nullptr));
  EXPECT_EQ(0, m0.size());

  ASSERT_TRUE(m0.addFirst(one));
  EXPECT_EQ(1, m0.size());

  ASSERT_TRUE(m0.addFirst(two));
  EXPECT_EQ(2, m0.size());
}

TEST_F(MapReducerFixture, testAddLast)
{
  //verify current size
  EXPECT_EQ(0, m0.size());

  //try to add an invalid item
  ASSERT_FALSE(m0.addLast(nullptr));
  EXPECT_EQ(0, m0.size());

  ASSERT_TRUE(m0.addLast(one));
  EXPECT_EQ(1, m0.size());

  ASSERT_TRUE(m0.addLast(two));
  EXPECT_EQ(2, m0.size());
}

TEST_F(MapReducerFixture, testGetFirst)
{
  //verify current size
  EXPECT_EQ(2, m2.size());

  //try to add an invalid item
  ASSERT_EQ(1, *(m2.getFirst()));
  EXPECT_EQ(1, m2.size());

  ASSERT_EQ(2, *(m2.getFirst()));
  EXPECT_EQ(0, m2.size());

  //verify the items removed haven't been deleted
  ASSERT_EQ(1, *one);
}

TEST_F(MapReducerFixture, testGetLast)
{
  //verify current size
  EXPECT_EQ(2, m2.size());

  //try to add an invalid item
  ASSERT_EQ(2, *(m2.getLast()));
  EXPECT_EQ(1, m2.size());

  ASSERT_EQ(1, *(m2.getLast()));
  EXPECT_EQ(0, m2.size());

  //verify the items removed haven't been deleted
  ASSERT_EQ(1, *one);
}
