#ifndef MTRX_H
#define MTRX_H

#include <iostream>
#include <iomanip>

template<class T>
struct Mtrx
{
    size_t nrow;
    size_t ncol;
    Mtrx(): nrow(0), ncol(0), content(nullptr){};
    explicit Mtrx(size_t M, size_t N): nrow{M}, ncol{N}, content{new T[M*N]} {}
    ~Mtrx();
    Mtrx(const Mtrx<T>& A);
    Mtrx(Mtrx<T>&& A);

    T& operator()(size_t, size_t);
    T operator()(size_t, size_t) const;
    Mtrx<T>& operator = (const Mtrx<T>&);
    Mtrx<T>& operator = (Mtrx<T>&&);
    Mtrx<T>& operator *= (Mtrx<T>&);

    auto get_data() {return content;}

    private:
    T* content;
};

#endif // MTRX_H
