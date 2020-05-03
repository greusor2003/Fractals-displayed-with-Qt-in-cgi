#ifndef MTRX_HPP
#define MTRX_HPP

#include "Mtrx.h"
#include <random>
#include <cassert>

template <class T>
Mtrx<T>::Mtrx(const Mtrx<T>& A)
  {
        Mtrx(A.nrow, A.ncol);
        for(size_t i=0; i< nrow*ncol; i++ )
            content[i] = A.content[i];
  }

template <class T>
Mtrx<T>::~Mtrx()
{
    delete [] content;
}

template <class T>
Mtrx<T>::Mtrx(Mtrx<T>&& A)
{
    nrow = A.nrow;
    ncol = A.ncol;
    content = A.content;
    A.content = nullptr;

}

template<class T>
Mtrx<T>& Mtrx<T>::operator = (const Mtrx<T>& A)
{
    if (this != &A)
    {
        delete [] content;
        nrow = A.nrow;
        ncol = A.ncol;
        content = new T[ncol*nrow];
        for(size_t i=0; i< nrow*ncol; i++ )
            content[i] = A.content[i];
        return *this;
    }
    else
        return *this;
}


template<class T>
Mtrx<T>& Mtrx<T>::operator = (Mtrx<T>&& A)
{
    if (this != &A)
    {
        delete [] content;
        ncol = A.ncol;
        nrow = A.nrow;
        content = A.content;
        A.content = nullptr;
        return *this;
    }
    return *this;
}


template<class T>
Mtrx<T>& Mtrx<T>::operator *= (Mtrx<T>& B)
{
    assert(ncol == B.nrow);
    Mtrx<T> temp(nrow, B.ncol);
    mult<T>(*this, B, temp);
    *this = temp;
    return *this;
}

template<class T>
Mtrx<T> operator * (Mtrx<T>& A, Mtrx<T>& B)
{
    assert(A.ncol == B.nrow);
    Mtrx<T> temp(A.nrow, B.ncol);
    mult<T>(A, B, temp);
    return temp;
}

template <class T>
T& Mtrx<T>::operator()(size_t i, size_t j)
{
    assert(ncol*i+j < nrow*ncol);
    return content[ncol*i + j];
}

template <class T>
T Mtrx<T>::operator()(size_t i, size_t j) const
{
    assert(ncol*i+j < nrow*ncol);
    return content[ncol*i + j];
}


template <class T>
void printM(const Mtrx<T>& M, const size_t I, const size_t J )
{
    assert(M.nrow >= I and M.ncol >= J);
    for (size_t i = 0; i < I; i++)
    {
        for (size_t j = 0; j < J; j++)
            std::cout << std::fixed << std::setprecision(2)<< M(i,j) <<" ";
        std::cout << "\n";
    }
    std::cout<<"\n";
}


#endif // MTRX_HPP


