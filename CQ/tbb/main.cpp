#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/partitioner.h"
#include <iostream>
#include <vector>

class Do{
  private:
    std::vector< std::vector<unsigned int> >* lv;
  private:
    void Count(const std::vector<unsigned int>& v) {
      int c(0);
      for(int i=0;i<v.size();++i) ++c;
    }
  public:
    Do(std::vector< std::vector<unsigned int> >* lv_):lv(lv_){}
    void operator()(const tbb::blocked_range<unsigned int>& r) {
      for(unsigned int i=r.begin();i<r.end();++i) {
        for(unsigned int k(0); k<10; ++k){
          (*lv)[i].push_back(k+i);
        }
        int cnt(0);
        Count((*lv)[i]);
      }
    }
};
int main(int argc, char* argv[]) {
  std::vector< std::vector<unsigned int> > gv;
  gv.reserve(2);

  tbb::parallel_for(tbb::blocked_range<unsigned int>(0,2),Do(&gv),tbb::auto_partitioner());
  for(unsigned int i(0);i<2;++i) {
    std::cout << "Line " << i << ": ";
    for(unsigned int j(0);j<gv[i].size();++j){
      std::cout << gv[i][j] << " ";
    }
    std::cout << "n";
  }
  return 0;
}
