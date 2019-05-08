#include "mtrx.h"
#include <random>
#include <complex>
#include <cassert>

using namespace std::complex_literals;

template<class T>
using cx = std::complex<T>;

template<class T>
struct cx_grid: public Mtrx<cx<T>>
{
    cx<T> NW;
    cx<T> SE;

    cx_grid(cx<T> nw, cx<T> se, size_t M, size_t N) : Mtrx<cx<T>>(M, N)
    { 
        assert(M >= 2 and N >= 2);
        NW = nw; SE = se;
        auto h = (SE.real()-NW.real()) / (N-1);
        auto v = (NW.imag()-SE.imag()) / (M-1);
        
        assert(h > 0 and v > 0 );
        for (size_t i = 0; i < M; i++)
            for (size_t j = 0; j < N; j++)
                Mtrx<cx<T>>::operator()(i,j) = NW + cx<T>(j*h, (T)0.0-i*v);
    }

};



void rnd_load(Mtrx<double>& M)
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_real_distribution<> dis(0.0, 1.0);
  for (size_t i = 0; i < M.nrow; i++)
      for (size_t j = 0; j < M.ncol; j++)
          M(i,j) = dis(gen);  
}

template<class T>
void printM(const Mtrx<T>& M, const size_t I, const size_t J )
{
    for (size_t i = 0; i < I; i++)
    {
        for (size_t j = 0; j < J; j++)
            std::cout << M(i,j) <<" ";
        std::cout << "\n";
    }
}

