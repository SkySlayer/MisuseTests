#include "ff.h"
#include <stdio.h>
#include "common/log.h"

void func()
{
  ff::paragroup a;
  ff::para<> b;
  a.add(b);
}
int main(int argc, char *argv[])
{
  func();
  return 0;
}
