#include <tbb/tbb.h>
#include <iostream>


class MainAppTask : public tbb::task 
{
  public:
    MainAppTask() 
    {
    }
    ~MainAppTask()
    {
    }

    tbb::task* execute() 
    { // Overrides virtual function task::execute
      set_ref_count(1);
      std::cout << "\\n Hello from the root task";
      double test = 0.0;
      for (int i = 0; i < 1000000; i++)
      {
        test += i;
      }
      return NULL;
    }

};

int main()
{
  tbb::task_scheduler_init anonymous;
  MainAppTask& a = *new(tbb::task::allocate_root()) MainAppTask();
  tbb::task::spawn_root_and_wait(a);

  return 1;
}
