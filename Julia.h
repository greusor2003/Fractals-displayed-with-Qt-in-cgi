#ifndef JULIA_H
#define JULIA_H

#include "Mtrx.hpp"
#include <complex>
#include <cassert>

#define true 1
#define false 0

template <class T>
using cx = std::complex<T>;

using namespace std::complex_literals;

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

void black_mtrx(Mtrx<uint8_t>&);
void color_mtrx(Mtrx <uint8_t>&, uint8_t, uint8_t, uint8_t);
Mtrx<uint8_t> juliaset(size_t, size_t, size_t, const cx<double>&, const cx<double>&, const cx<double>&);
Mtrx<uint8_t> Mandelbrot(size_t, size_t, size_t, const cx<double>&, const cx<double>&);


#endif // JULIA_H
