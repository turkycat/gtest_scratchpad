#include <iostream>
#include "num.h"

using namespace std;

int main(int argc, char *argv[])
{
  //this is some production code that uses the Num class for now.
  //we don't really care... we just want to make sure it's linking
  Num *n = new Num(42);
  cout << "The answer to the ultimate question is " << n->getNum() << endl;
  delete (n);
}