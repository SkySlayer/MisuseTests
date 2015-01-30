#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
#include <iostream>

using namespace tbb;

struct Sum {
  float value;
  Sum() : value(0) {}
  Sum( Sum& s, split ) {value = 0;}
  void operator()( const blocked_range<int *>& r ) {
    float temp = value;
    for( float* a=r.begin(); a!=r.end(); ++a ) {
      temp += *a;
    }
    value = temp;
  }
  void join( Sum& rhs ) {value += rhs.value;}
};

float ParallelSum( float array[], size_t n ) {
  Sum total;
  parallel_reduce( blocked_range<int *>( array, array+n ), 
      total );
  return total.value;
}

int main(void)
{
  float array[20];
  for(int i = 0; i < 20; ++i)
    array[i] = i * 0.02 + 0.03;
  float result = ParallelSum(array,20);
  std::cout << result << std::endl;
  return 0;
}
