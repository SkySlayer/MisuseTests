#include <iostream>
#include <tbb/tbb.h>
#include <stdio.h>
#include <cassert>

#include <vector>


class Matrix{
  public:
    Matrix(int m, int n)
      : m_iM(m)
        , m_iN(n){
          for(int i = 0; i < m*n; i++)
            m_oData.push_back(0);
        }

    const double  operator () (int i,int j) const{
      return m_oData[i * m_iN + j];
    }
    double & operator () (int i, int j){
      return m_oData[i * m_iN + j];
    }

    int M() const {return m_iM;}
    int N() const {return m_iN;}

    bool operator ==(const Matrix & m) const{
      if(M() != m.M() || N() != m.N())
        return false;
      for(int i = 0; i < m.M() * m.N(); ++i)
      {
        if(m_oData[i] != m.m_oData[i])
          return false;
      }
      return true;
    }

    static Matrix random_matrix(int m, int n)
    {
      Matrix res(m, n);
      int c = 0;
      for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
        {
          res(i, j) = c;
          c++;
        }
      return res;
    }

  protected:
    int m_iM;
    int m_iN;
    std::vector<double> m_oData;
};//end class Matrix

Matrix mul(const Matrix & m1, const Matrix & m2)
{
  assert(m1.N() == m2.M());
  Matrix res (m1.M(), m2.N());
  for (int i = 0; i < m1.M(); ++i){  
    for (int j = 0; j < m2.N(); ++j){  
      res(i,j) = 0;  
      for (int k = 0; k < m1.N(); ++k){  
        res(i, j) += m1(i, k) * m2(k, j);  
      }  
    }  
  }  
  return res;
}

Matrix parallel_mul(const Matrix & m1, const Matrix & m2)
{
  assert(m1.N() == m2.M());
  Matrix res (m1.M(), m2.N());
  //write your code here!

  return res;
}

void print_matrix(const Matrix & m)
{
  for(int i = 0; i < m.M(); i++)
  {
    std::cout<<std::endl;
    for(int j = 0; j < m.N(); j++)
    {
      printf("\t%f", m(i, j));
    }
  }
}


int main(int argc, char *argv[])
{

  Matrix m1 = Matrix::random_matrix(10, 10);
  Matrix m2 = Matrix::random_matrix(10, 10);
  //print_matrix(m1);
  //std::cout<<"\nxxxxxxxxxxxxxxxxxxxxxx"<<std::endl;
  //print_matrix(m2);
  Matrix r1 = mul(m1, m2);
  Matrix r2 = parallel_mul(m1, m2);
  if(r1 == r2)
  {
    std::cout<<"Congrats! you are done!"<<std::endl;
  }
  else
  {
    std::cout<<"\nsorry! wrong results, please keep trying!"<<std::endl;
  }
  return 0;
}
