#include <tbb/tbb.h>
#include <cmath>

typedef double val;

val Foo(double x)
{
  for (int i=0; i<10; i++) x = cos(x); return x;
}

class SumFoo
{
  val *const my_a;
  public:
  val my_sum;
  void operator()( const tbb::blocked_range<int>& r ) {
    val *a = my_a;
    val sum = my_sum;
    size_t end = r.end();
    for (size_t i=r.begin(); i!=end; ++i)
      sum += Foo(a[i]);
    my_sum = sum;
  }
  SumFoo( val *a ) : my_a(a), my_sum(0) { }
  SumFoo( SumFoo &x, tbb::split ) : my_a(x.my_a), my_sum(0)  { }
  void join( const SumFoo& y)  {  my_sum +=y.my_sum; }
  void runme(int n)
  {
    tbb::parallel_reduce(tbb::blocked_range<int>(0, n), this, tbb::auto_partitioner() );
  }
};

int main()
{
  double res = 0.0;
  SumFoo sf(&res);
  sf.runme(10);
  return 0;
}
