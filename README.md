# Fractals-displayed-with-OpenCV

Illustrates a quick method to display image data produced using one's C++ library of choice with OpenCV.   

The complexity of GUI and graphic engine API's that interact directly with standard C++ is among the deterrents that often push programmers to other prototyping languages and solutions. The image rendering device adopted by OpenCV implements a transparent class friendly with whatever container of 1 byte data the programmer likes to input. This piece of coding is a humble example that could have been entirely written using OpenCV's API but its purpose is to show that one can readily control pixels in C++ without learning OpenCV whose utility is way vaster than displaying graphics. The advantage: C++ native and concurrent programming freedom. The cost: the installation of the OpenCV C++ library.  

Julia or Mandelbrot sets are generated as matrices of complex numbers using the template Mtrx.h interface. 

makefile1 compiles to main to generate images in the local folder

makefile compiles to png_stream which can be placed in the cgi-bin of the server so that the image can be generated directly into the browser and thus accessed remotely.
