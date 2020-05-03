#include "Julia.h"
#include <string>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <QImage>
#include <QImageWriter>
#include <QString>
#include <QByteArray>
#include <QBuffer>



using std::vector;

int main()
{
    // image size in px
    size_t M = 720;
    size_t N = 1080;

    // fractal depth
    size_t max_iter = 3*600;

    // generating constant (determines positioniong on Mandelbrot set)
    //cx<double> c = 0.278 + 1i*0.009;
    cx<double> c = -0.8 + 1i*0.156;
    // zone (north-west south-east rectangle) of tracking in the complex plane (smaller values to zoom in)
    //cx<double> NW = 0.38125 + 1i*0.5764;
    //cx<double> SE = 0.38375 + 1i*0.5744;

    size_t Q = 1; // desired number of images to generate
    auto a = 2.0*pow(0.85, 40); auto b = 1.6*pow(0.85,40);
    for (size_t i = 0; i < Q; i++)
    {
    cx<double> NW = -a + 1i*b-0.000027-1i*0.000006;
        cx<double> SE = a -1i*b-0.000027-1i*0.000006;

        Mtrx <uint8_t> X = juliaset(M, N, max_iter, NW, SE, c);
        //Mtrx <uint8_t> X = Mandelbrot(M, N, max_iter, NW, SE);

       // cv::Mat nimage(M, N, CV_8UC3);
        QImage nimage(X.get_data(), N, M, QImage::Format_RGB888);
        QByteArray ba;
        QBuffer buf(&ba);
        buf.open(QIODevice::WriteOnly);
        nimage.save(&buf, "PNG");
        std::cout << "Content-type:image/png\n\n";
        for(auto& x: ba)
            putc(x, stdout);

        a *= 0.85; b *= 0.85;

   }

    return 0;
}
