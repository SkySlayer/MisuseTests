#include <iostream>
#define TBB_PREVIEW_TASK_ARENA 1
#include "tbb/task_arena.h"
#include "tbb/task_scheduler_init.h"
#include <tbb/mutex.h>

tbb::mutex printmutex;

class test_task : public tbb::task { 
  public: 
    test_task(int n): m_i(n){}
    tbb::task* execute() { 
      printmutex.lock();
      std::cout << "I'm the  " << i <<"th happy task!"<< std::endl;
      printmutex.unlock();
      return NULL;
    }
  protected:
    int m_i;
};

int main(void) {

  tbb::task_scheduler_init def_init; 
  tbb::task_arena limited(2);// no more than 2 threads in this arena
  test_task & t1 = *new(tbb::task::allocate_root()) test_task();
  test_task & t2 = *new(tbb::task::allocate_root()) test_task();

  limited.enqueue([&t1,&t2] { 
      t1.execute();
      t2.execute();
      });

  limited.wait_until_empty(); // ensure async work is finished


  return 0;
}

