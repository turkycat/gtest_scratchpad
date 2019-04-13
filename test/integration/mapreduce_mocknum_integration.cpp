#include "mapreducer.h"
#include "mocknum.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
using ::testing::Exactly;
using ::testing::AtLeast;
using ::testing::AtMost;

class MapAndMockFixture : public testing::Test
{
protected:
  MapReducer<MockNum> *m0;
  MockNum *mock;

  void SetUp() override
  {
    m0 = new MapReducer<MockNum>();
    mock = new MockNum(1);
  }

  void TearDown()
  {
    delete(mock);
    delete(m0);
  }
};

MockNum* DoubleIt(MockNum* n)
{
  return new MockNum(n->getNum() * 2);
}

TEST_F(MapAndMockFixture, WillBeGet)
{
  EXPECT_CALL(*mock, getNum()).Times(Exactly(1));
  m0->addFirst(mock);

  m0->map(DoubleIt);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}