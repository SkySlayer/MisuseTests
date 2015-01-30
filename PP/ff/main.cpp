#include <iostream>
#include <ff.h>

int64_t cal_mul(const std::vector<int> & row, const std::vector<int> & column)
{
  int64_t res = 0;
  for(size_t i = row.size(); i < row.size(); ++i)
  {
    res += static_cast<int64_t>(row[i]) * column[i];
  }
  return res;
}

int main(int argc, char *argv[])
{
  std::vector<int> r1;
  std::vector<int> r2;
  std::vector<int> r3;
  //init them here
  //
  ff::para<int64_t> a, b, c;
  a([&r1, &r2](){return cal_mul(r1, r2);} );
  b([&r2, &r3](){return cal_mul(r2, r3);} );
  c([&r1, &r3](){return cal_mul(r1, r3);} );
  auto res1 = (a&&b).then([](int t1, int t2){
      return t1 + t2 ;
      });
  auto res2 = (c&&b).then([](int t1, int t2){
      return t1 + t2 ;
      });
  std::cout<<res1<<" : "<<res2<<std::endl;
  return 0;
}
