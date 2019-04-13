#include <num.h>
#include "mapreducer.h"
#include "gtest/gtest.h"
#include <malloc.h>

class MapReducerFixture : public testing::Test
{
protected:
  MapReducer<Num> m0;
  MapReducer<Num> m1;
  MapReducer<Num> m2;
  MapReducer<Num> bigMap;
  Num *one;
  Num *two;

  void SetUp() override
  {
    one = new Num(1);
    two = new Num(2);
    m1.addFirst(one);
    m2.addLast(one);
    m2.addLast(two);

    for(int i = 0; i < 43; i++)
    {
      Num *n = new Num(i);
      bigMap.addLast(n);
    }
  }

  void TearDown()
  {
    free(one);
    free(two);
    while(bigMap.size())
    {
      Num *n = bigMap.getFirst();
      free(n);
    }
  }
};



Num* DoubleIt(Num *n)
{
  return new Num(n->getNum() * 2);
}

bool isEven(Num *n)
{
  return (n->getNum() % 2) == 0;
}

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

  //get last item, verify it, validate size change
  ASSERT_EQ(1, m2.getFirst()->getNum());
  EXPECT_EQ(1, m2.size());

  //get last item, verify it, validate size change
  ASSERT_EQ(2, m2.getFirst()->getNum());
  EXPECT_EQ(0, m2.size());

  //verify the items removed haven't been deleted
  ASSERT_EQ(1, one->getNum());
}

TEST_F(MapReducerFixture, testGetLast)
{
  //verify current size
  EXPECT_EQ(2, m2.size());

  //get last item, verify it, validate size change
  ASSERT_EQ(2, m2.getLast()->getNum());
  EXPECT_EQ(1, m2.size());

  //get last item, verify it, validate size change
  ASSERT_EQ(1, m2.getLast()->getNum());
  EXPECT_EQ(0, m2.size());

  //verify the items removed haven't been deleted
  ASSERT_EQ(1, one->getNum());
}

TEST_F(MapReducerFixture, testPeekFirst)
{
  //verify current size
  EXPECT_EQ(2, m2.size());

  //peek at the last item and verify the size did not change
  ASSERT_EQ(1, m2.peekFirst()->getNum());
  EXPECT_EQ(2, m2.size());

  //peek again, same item should be returned
  ASSERT_EQ(1, m2.peekFirst()->getNum());
  EXPECT_EQ(2, m2.size());
}

TEST_F(MapReducerFixture, testPeekLast)
{
  //verify current size
  EXPECT_EQ(2, m2.size());

  //peek at the last item and verify the size did not change
  ASSERT_EQ(2, m2.peekLast()->getNum());
  EXPECT_EQ(2, m2.size());

  //peek again, same item should be returned
  ASSERT_EQ(2, m2.peekLast()->getNum());
  EXPECT_EQ(2, m2.size());
}

TEST_F(MapReducerFixture, testMap)
{
  MapReducer<Num>* ret = m2.map(DoubleIt);
  ASSERT_EQ(2, ret->size());

  while(ret->size())
  {
    ASSERT_EQ(m2.getFirst()->getNum(), ret->getFirst()->getNum() / 2);  
  }
}

TEST_F(MapReducerFixture, testMapBig)
{
  MapReducer<Num>* ret = bigMap.map(DoubleIt);
  ASSERT_EQ(43, ret->size());

  while(ret->size())
  {
    ASSERT_EQ(bigMap.getFirst()->getNum(), ret->getFirst()->getNum() / 2);
  }
}

TEST_F(MapReducerFixture, testReduce)
{
  MapReducer<Num>* ret = m2.reduce(isEven);
  ASSERT_EQ(1, ret->size());
  EXPECT_EQ(2, ret->getFirst()->getNum());
}

TEST_F(MapReducerFixture, testReduceBig)
{
  MapReducer<Num>* ret = bigMap.reduce(isEven);
  ASSERT_EQ(22, ret->size());
  
  for(int i = 0; ret->size(); i+=2)
  {
    ASSERT_EQ(i, ret->getFirst()->getNum());  
  }
}