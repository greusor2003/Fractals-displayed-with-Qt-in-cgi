#include "Juliaset.h"

Juliaset::Juliaset(size_t m, size_t n, size_t max, cx<double>nw, cx<double> se, cx<double> ct): M(m), N(n), maxit(max), NW(nw), SE(se), c(ct),
    J(new Mtrx<uint8_t>(M, 3*N))
{
    size_t i=0, j=0;
    black_mtrx(*J);

    auto G =  cx_grid(NW, SE, M, N);

#pragma omp parallel private(i,j)
    {

#pragma omp single nowait

#ifdef _OPENMP
        omp_set_num_threads(NUM_THREADS);
#endif

#pragma omp for private(i,j)
        for (i = 0; i < M; i++)
            for (j = 0; j < N; j++)
            {
                auto z = G(i,j);

                size_t it = 0;
                while (norm(z) < 3 and it < maxit)
                {
                    it += 1;
                    z = z*z + c;
                }

                (*J)(i, 3*j) = it;
                (*J)(i, 3*j+1) = it;
                (*J)(i, 3*j+2) = it;
            }
    }
}

Juliaset::~Juliaset()
{
    delete J;
}

QImage Juliaset::toImage(uint8_t r, uint8_t g, uint8_t b)
{
    assert((*J).ncol != 0 and (*J).ncol % 3 == 0);
        auto N = (*J).ncol / 3; auto M = (*J).nrow;

        QImage Img(N,M, QImage::Format_RGB888);

        for (size_t i = 0; i < M; i++)
           for (size_t j = 0; j < N; j++)

              Img.setPixel(j, i, qRgb((*J)(i,3*j)*r, (*J)(i,3*j+1)*g, (*J)(i,3*j+2)*b));

        return Img;
}

void Juliaset::black_mtrx(Mtrx<uint8_t> &Img)
{
    for (size_t i = 0; i < Img.nrow; i++)
        for (size_t j = 0; j < Img.ncol; j++)
            Img(i,j) = 0;
}


