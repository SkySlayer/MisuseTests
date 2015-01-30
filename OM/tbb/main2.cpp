#include <iostream>
#include <atomic>
#include <tbb/tbb.h>

namespace test {
  class UpdateTask : public tbb::task  {
    public:

      UpdateTask()        {
        std::cout << "[UpdateTask]" << std::endl;
      }

      ~UpdateTask()       {
        std::cout << "\n[/UpdateTask]" << std::endl;
      }

      tbb::task* execute()        {
        std::cout << "Tick "<< m_count <<std::endl;

        ++m_count;

        this->recycle_to_reexecute();           
        return new(tbb::task::allocate_continuation()) tbb::empty_task();             
        //return nullptr;                 
      }

    private:

      std::atomic<int> m_count;

  };
  tbb::task_list m_task_list;
  void register_update_task()     {
    UpdateTask& updater =
      *new(tbb::task::allocate_root()) UpdateTask();
    m_task_list.push_back( updater );
  }
  void run_and_wait()     {
    tbb::task::spawn_root_and_wait( m_task_list );
  }
  void tbb_test()     {
    register_update_task();
    run_and_wait();        
  }
};//end namespace test

int main(void)
{

  test::tbb_test();

  std::cout << "\nEND";
  std::cin.ignore();

  return 0;
}

