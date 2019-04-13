#include <iostream>
#include "num.h"
#include "mapreducer.h"

using namespace std;

int main(int argc, char *argv[])
{
  //this is some production code that uses the Num class for now.
  //we don't really care... we just want to make sure it's linking
  MapReducer<Num> queue;
  for(int i = 0; i < 43; ++i)
  {
    queue.addLast(new Num(i));
  }

  cout << "The answer to the ultimate question is " << queue.peekLast()->getNum() << endl;
}