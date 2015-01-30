#include <ff.h>
#include <iostream>

bool is_prime(int64_t n)
{
  return false;
}
bool found_first_smaller_prime = false;
int64_t first_smaller_prime = 0;

std::vector<int64_t> find_smaller_prime(int64_t n)
{
  std::vector<int64_t> res ;
  for(int64_t t = n; t >=1; t--)
  {
    if(is_prime(t))
    {
      if(!found_first_smaller_prime)
      {
        found_first_smaller_prime = true;
        first_smaller_prime = t;
      }
      res.push_back(t);
    }
  }
  return res;
}
int64_t find_bigger_prime(int64_t n)
{
  int64_t t = n+1;
  while(true)
  {
    if(is_prime(t))
      break;
    t ++;
  }
  return t;
}
using namespace ff;
int main(int argc, char *argv[])
{
  para<int64_t> fb;
  int64_t n = 1024*1024*1024;
  fb([n](){return find_bigger_prime(n);});
  para<std::vector<int64_t> > fs;
  fs([n](){return find_smaller_prime(n);});
  (fb && found_first_smaller_prime).then([]{
      std::cout<<"got the bigger one and the first smaller one!"<<std::endl;});
  ff_wait(fb && fs);
  return 0;
}
