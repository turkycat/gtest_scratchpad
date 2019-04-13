#include "gmock/gmock.h"
#include "num.h"

class MockNum : public Num
{

public:
  MockNum(int n) : Num(n) {}

  //virtual ~Num();

  //virtual int getNum();
  MOCK_METHOD0(getNum, int());

  //virtual void setNum(int);
  MOCK_METHOD1(setNum, void(int));
};