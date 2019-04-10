#include <iostream>
#include "gtest/gtest.h"

using namespace std;

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  cout << "Running all tests!" << endl;
  return RUN_ALL_TESTS();
}
