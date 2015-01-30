#include <tbb/tbb.h>
#include <vector>
#include <iostream>

typedef std::vector<double> VecDoub;
typedef std::vector<double> MatDoub;

int64_t fib(int n)
{
  if(n <=2)
    return 1;
  return fib(n-1) + fib(n-2);
}

void CalculateGA(VecDoub & tmpxValue, MatDoub & ga, double k, double r)
{
  //do something here
  std::cout<<tmpxValue.size() + ga.size() + k + r + fib(15)<<std::endl;
}

void CalculateGp(VecDoub & tmpxValue, MatDoub & ga, double k, double r)
{
  //do something here
  std::cout<<fib(18) + tmpxValue.size() + ga.size() + k + r<<std::endl;
}

void CalculateEp(VecDoub & XValue, VecDoub & ep, double k, double lr, double* externalFore)
{
  std::cout<<fib(21) + XValue.size() + ep.size() + k + lr + (*externalFore)<<std::endl;
}
void CalculateEA(VecDoub & XValue, MatDoub & ea, double k, double lr, double* externalFore)
{
  std::cout<<fib(28) + XValue.size() + ea.size() + k + lr<<std::endl;
}

class PCalculateGA:public tbb::task{

  public:

    VecDoub & m_tempXValue;

    MatDoub & m_ga;

    double m_k;

    double m_lr;

    PCalculateGA(VecDoub & XValue, MatDoub & ga, double k, double lr):

      m_tempXValue(XValue),m_ga(ga),m_k(k),m_lr(lr){}

    task* execute(){

      CalculateGA(m_tempXValue, m_ga, m_k, m_lr);

      return NULL;

    }

};

class PCalculateGp:public tbb::task{

  public:

    VecDoub & m_tempXValue;

    VecDoub & m_gp;

    double m_k;

    double m_lr;

    PCalculateGp(VecDoub & XValue, VecDoub & gp, double k, double lr):

      m_tempXValue(XValue),m_gp(gp),m_k(k),m_lr(lr){}

    task* execute(){

      CalculateGp(m_tempXValue, m_gp, m_k, m_lr);

      return NULL;

    }

};

class PCalculateEp:public tbb::task{

  public:

    VecDoub & m_tempXValue;

    VecDoub & m_ep;

    double m_k;

    double m_lr;

    double* m_externalFore;

    PCalculateEp(VecDoub & XValue, VecDoub & ep, double k, double lr, double* externalFore):

      m_tempXValue(XValue),m_ep(ep),m_k(k),m_lr(lr),m_externalFore(externalFore){}

    task* execute(){

      CalculateEp(m_tempXValue, m_ep, m_k, m_lr, m_externalFore);

      return NULL;

    }

};

class PCalculateEA:public tbb::task{

  public:

    VecDoub & m_tempXValue;

    MatDoub & m_ea;

    double m_k;

    double m_lr;

    double* m_externalFore;

    PCalculateEA(VecDoub & XValue, MatDoub & ea, double k, double lr, double* externalFore):

      m_tempXValue(XValue),m_ea(ea),m_k(k),m_lr(lr),m_externalFore(externalFore){}

    task* execute(){

      CalculateEA(m_tempXValue, m_ea, m_k, m_lr, m_externalFore);

      return NULL;

    }

};


class ParallelCalculation:public tbb::task{

  public:

    VecDoub & m_tempXValue;

    MatDoub & m_ga;

    VecDoub & m_gp;

    VecDoub & m_ep;

    MatDoub & m_ea;

    double m_k;

    double m_lr;

    double* m_externalFore;

    ParallelCalculation(VecDoub & XValue,MatDoub & ga, VecDoub & gp, VecDoub & ep, MatDoub & ea, double k,double lrt,double* externalFore):

      m_tempXValue(XValue),m_ga(ga),m_gp(gp),m_ep(ep),m_ea(ea),m_k(k),m_lr(lrt),m_externalFore(externalFore){}

    task* execute(){

      set_ref_count(5);

      PCalculateGA& t4 = *new(allocate_child())PCalculateGA(m_tempXValue,m_ga,m_k,m_lr);

      PCalculateGp& t3 = *new(allocate_child())PCalculateGp(m_tempXValue,m_gp,m_k,m_lr);

      PCalculateEp& t2 = *new(allocate_child())PCalculateEp(m_tempXValue,m_ep,m_k,m_lr,m_externalFore);

      PCalculateEA& t1 = *new(allocate_child())PCalculateEA(m_tempXValue,m_ea,m_k,m_lr,m_externalFore);

      spawn(t4);

      spawn(t3);

      spawn(t2);

      spawn_and_wait_for_all(t1);

      return NULL;

    }

};

int main()
{
  tbb::task_scheduler_init anonymous;
  VecDoub xv;
  MatDoub ga;
  VecDoub gp;
  VecDoub ep;
  MatDoub ea;
  double k = 1.8, lrt = 9.2;
  double externalFore = 3.41;
  ParallelCalculation &pc = *new (tbb::task::allocate_root()) ParallelCalculation(xv, ga, gp, ep, ea, k, lrt, &externalFore);
  pc.spawn_and_wait_for_all(pc);
  return 0;
}
