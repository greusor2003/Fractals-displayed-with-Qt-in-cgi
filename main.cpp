#include <QImage>
#include <QImageWriter>
#include <QString>
#include <string>
#include <cmath>

#include "Julia.h"


int main()
{

    // image size in px
       size_t M = 800;
       size_t N = 1280;

       // fractal depth
       size_t max_iter = 3*1200;

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
           //Mtrx <uint8_t> X = Mandelbrot(M, N, max_iter, NW, SE); // use for displaying Mandelbrot set


           if(nimage.isNull())
           {
               std::cout <<  "Could not open or find the image" << std::endl;
               return -1;
           }
               // naming the images
           QString im_name = QString::number(0) + QString::number(i) + QString(".png");
                   // path to the location of the images
           QString path_to_image(im_name);
           QImageWriter writer(path_to_image);
           writer.write(nimage);

           a *= 0.85; b *= 0.85; // adjust the frame for generating the next image (zoom into the set)

        }

    return 0;
}
