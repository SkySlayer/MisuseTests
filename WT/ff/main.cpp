#include "ff.h"
#include <iostream>

void func()
{
  ff::para<> a;
  a([]{std::cout<<"do first thing"<<std::endl;});
  ff::para<> b;
  b[a].then([](){std::cout<<"do second thing"<<std::endl;});
  ff::ff_wait(a && b);
}
int main(int argc, char *argv[])
{
  func();
  return 0;
}
