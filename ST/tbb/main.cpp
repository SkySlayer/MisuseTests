#include <vector>
#include <iostream>
#include "tbb/atomic.h"
struct MyPair{
  int v;
  double d;
};//end struct MyPair

int main()
{
  tbb::atomic<MyPair> b;
  
  return 0;
}
