#ifndef JULIASET_H
#define JULIASET_H

#include "Mtrx.hpp"
#include <complex>
#include <cassert>
#include <QImage>
#include "/usr/lib/gcc/x86_64-linux-gnu/9/include/omp.h"

#define NUM_THREADS 8

template <class T>
using cx = std::complex<T>;

using namespace std::complex_literals;

template <class T>
Mtrx<cx<T>> cx_grid (cx<T> nw, cx<T> se, size_t m, size_t n)
{
    assert(m >= 2 and n >= 2);
    auto NW=nw; auto SE=se; auto M=m; auto N=n;
    auto h = (SE.real()-NW.real()) / (N-1);
    auto v = (NW.imag()-SE.imag()) / (M-1);
    auto Mat = Mtrx<cx<T>>(M,N);
    for (size_t i = 0; i < M; i++)
        for (size_t j = 0; j < N; j++)
           Mat(i,j) = NW + cx<T>(j*h, (T)0.0-i*v);
    return Mat;
}
class Juliaset
{
public:
    Juliaset(size_t m, size_t n, size_t max, cx<double> nw, cx<double> se, cx<double> ct);
    ~Juliaset();

    // generates the set's picture using the rgb color scheme given by the arguments
    // default for monochrome image
    QImage toImage(uint8_t = 1, uint8_t = 1, uint8_t = 1);


private:
    // height of the image
    size_t M;

    // width of the image
    size_t N;

    // number of iterations
    size_t maxit;

    // north-west corner of the rectangular portion of the complex plane considered fot generating the set
    cx<double> NW;

    // south-eastcorner of the rectangular portion of the complex plane considered for generating the set
    cx<double> SE;

    // generating constant
    cx<double> c;

    // matrix holding the set's data
    Mtrx<uint8_t>* J;

    //image constructing methods
    void black_mtrx(Mtrx<uint8_t>& Img);

};

#endif // JULIASET_H
