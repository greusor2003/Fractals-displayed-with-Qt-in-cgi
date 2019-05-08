#include "mtrx.cpp"
#ifdef _OPENMP
#include <omp.h>
#endif
#include <opencv2/highgui.hpp>

#define true 1
#define false 0


using namespace std::complex_literals;

void black_mtrx(Mtrx <uint8_t>& Img)
{
    for (size_t i = 0; i < Img.nrow; i++)
        for (size_t j = 0; j < Img.ncol; j++)
            Img(i,j) = 0;  
}

void juliaset(Mtrx <uint8_t>& X, size_t maxit, const cx<double>& NW, const cx<double>& SE, const cx<double>& c) 
{
    // processes an externally initialized X of dimensions giving the wanted image size
    
    bool nthr_checked = false;
    int nthr =1;

    black_mtrx(X);
    auto G = cx_grid<double>(NW, SE, X.nrow, X.ncol / 3);
    auto M = (int)G.nrow;
    auto N = (int)G.ncol;
    std::cout << "Image px size: " << N << " " << M << "\n";
    std::cout << "Iterations: " << maxit <<"\n";
    
    // color boosters and contrast
    uint8_t red = 10; uint8_t green = 80; uint8_t blue = 20; uint8_t contr = 8;
    
    int i=0, j=0; 
    #pragma omp parallel private(i,j)
    {
        #pragma omp single nowait
		if (!nthr_checked) 
        {
            #ifdef _OPENMP
			    nthr = omp_get_num_threads();
            #endif
			std::cout <<  "\nWe are using " << nthr << "thread(s)\n";
			nthr_checked = true;
        }

        #pragma omp for nowait
        for (i = 0; i < M; i++)
            for (j = 0; j < N; j++)
            {
                auto z = G(i,j); size_t it = 0; size_t r = 0;
                while (norm(z) < 4 and it < maxit) 
                {
                    it += contr;
                    X(i,3*j) = blue + (it / (256*256));
                    r = it % (256*256);
                    X(i,3*j+1) = green * r / 256;
                    X(i, 3*j+2) = red + r % 256; 
                    z = z*z + c;
                }  
            }
    }
}


