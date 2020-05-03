#include <omp.h>
#include "Julia.h"
#define NUM_THREADS 4


void black_mtrx(Mtrx<uint8_t>& Img)
{
    for (size_t i = 0; i < Img.nrow; i++)
        for (size_t j = 0; j < Img.ncol; j++)
            Img(i,j) = 0;
}

void color_mtrx(Mtrx <uint8_t>& Img, uint8_t b = 1, uint8_t g = 1, uint8_t r = 1)
{
    assert(Img.ncol != 0 and Img.ncol % 3 == 0);
    auto N = Img.ncol / 3;
    for (size_t i = 0; i < Img.nrow; i++)
        for (size_t j = 0; j < N; j++)
        {
            Img(i,3*j) *= b;
            Img(i,3*j+1) *= g;
            Img(i,3*j+2) *= r;
        }

}

Mtrx<uint8_t> juliaset(size_t M, size_t N, size_t maxit, const cx<double>& NW, const cx<double>& SE, const cx<double>& c)
{

    bool nthr_checked = false;
    //int nthr =1;

    auto G = cx_grid<double>(NW, SE, M, N);

    //std::cout << "Image px size: " << N << " " << M << "\n";
    //std::cout << "Iterations: " << maxit <<"\n";

    auto X = Mtrx<uint8_t>(M, 3*N);

    black_mtrx(X);

    // color boosters and contrast
    uint8_t red = 1; uint8_t green = 1; uint8_t blue = 1; size_t contr = 1;

    size_t i=0, j=0; //size_t baseq = 256*256;
    #pragma omp parallel private(i,j)
    {
        #pragma omp single nowait
        if (!nthr_checked)
            {
                    #ifdef _OPENMP
                omp_set_num_threads(NUM_THREADS);
                //auto nthr = omp_get_num_threads();
                    #endif
            //std::cout <<  "\nWe are using " << nthr << "thread(s)\n";
            nthr_checked = true;
            }

        #pragma omp for private(i,j)
        for (i = 0; i < M; i++)
            for (j = 0; j < N; j++)
            {
                auto z = G(i,j); size_t it = 0;
                while (norm(z) < 4 and it < maxit)
                {
                    it += contr;
                    z = z*z + c;
                }
        X(i, 3*j) = (it -1200); //weakest channel
                X(i, 3*j+1) = (it-600);
                X(i, 3*j+2) = it; //strongest channel


            }
    }

    color_mtrx(X, blue, green, red);

    return X;
}
