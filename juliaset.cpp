#include "mtrx.cpp"
#ifdef _OPENMP
#include <omp.h>
#endif
#include <opencv2/highgui.hpp>
#include <cassert>

#define true 1
#define false 0


using namespace std::complex_literals;

void black_mtrx(Mtrx <uint8_t>& Img)
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
    uint8_t red = 1; uint8_t green = 40; uint8_t blue = 127; size_t contr = (2*256*256+255*256+255)/maxit;
    
    int i=0, j=0; size_t baseq = 256*256;
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
                    X(i,3*j) = it / baseq; //weakest channel
                    r = it % baseq;
                    X(i,3*j+1) = r / 256;
                    X(i, 3*j+2) = r; //strongest channel
                    z = z*z + c;
                }  
            }
    }
    
    color_mtrx(X, blue, green, red);
}


