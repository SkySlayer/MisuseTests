#include <iostream>
#include <vector>
#include <cmath>
#include <tbb/tbb.h>

typedef tbb::queuing_mutex Mutex;

struct Parallel
{
  Mutex mutex;
  std::vector<int> * values;

  Parallel(std::vector<int> * values_) : values(values_) {}

  void operator()( tbb::blocked_range< unsigned int > & range ) const {
    for(unsigned int i = range.begin(); i < range.end(); ++i) 
    {
      Mutex::scoped_lock lock(mutex);
      if ( (*values)[i] > 40)
      {
        std::cout << "NO SCRAMBLING ALLOWED!\n";
        std::cout.flush();
      }
      lock.release();
    }
  }
};

int main() {
  const int someValue = 20000;

  std::vector<int> data(someValue);
  for(int i = 0; i < someValue; ++i) {
    data[i] = std::rand();
  }

  tbb::parallel_for( tbb::blocked_range<unsigned int>(0, data.size()),Parallel(&data) );
  return 0;
}
