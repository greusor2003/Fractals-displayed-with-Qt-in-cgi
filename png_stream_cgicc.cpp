#include "Juliaset.h"
#include <string>
#include <cmath>
#include <QImage>
#include <QImageWriter>
#include <QString>
#include <string>
#include <QByteArray>
#include <QBuffer>
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace cgicc;
using std::cout;
using std::string;

void set_content_type(string content_type) {
  cout << "Content-type: " << content_type << "\r\n\r\n";
}

int main()
{
    Cgicc cgi;

    // image size in px
       const size_t M = 1080;
       const size_t N = 1440;

    // fractal depth
       const size_t max_iter = 3*512;

    // zooming step as fraction of a unit
       const auto zs = 0.85;

    // center image as a complex number d=x+iy
    // double re = 0.0; double im = 0.0;
       double re = std::stod(cgi("re"));
       double im = std::stod(cgi("im"));
       cx<double> d = re + 1i * im;
       const auto a  = 2.0; const auto b = 1.6;


    // generating constant (determines positioniong on Mandelbrot set)
    // double x = -0.8, y = 0.156;
       double x = std::stod(cgi("x"));
       double y = std::stod(cgi("y"));
       cx<double> c = x + 1i*y;

    // number of zooming steps
       size_t Q = std::stoul(cgi("Q"));
       auto p = pow(zs, Q);

        cx<double> NW = (-a + 1i * b)* p + d;
        cx<double> SE = (a - 1i * b)* p + d;

        auto Jset = Juliaset(M, N, max_iter, NW, SE, c);

        QImage nimage = Jset.toImage(4,2,1);
        if(nimage.isNull())
        {
            std::cout <<  "Could not open or find the image" << std::endl;
            return -1;
        }
        QByteArray ba;
        QBuffer buf(&ba);
        buf.open(QIODevice::WriteOnly);
        nimage.save(&buf, "PNG");
            set_content_type("image/png");
        for(auto& x: ba)
            putc(x, stdout);
    return 0;
}
