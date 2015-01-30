#include <ff.h>

int findMax(int a, int b)
{
  return (a>b)?a:b;
}

int main(int argc, char *argv[])
{
  ff::para<double> a;
  a([](){
      return findMax(3,8);
      });
  return 0;
}
