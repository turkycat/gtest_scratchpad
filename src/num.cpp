#include "num.h"

Num::Num(int num)
{
  _num = num;
}

Num::~Num()
{
  //do nothing
}

int Num::getNum()
{
  return _num;
}

void Num::setNum(int num)
{
  _num = num;
}