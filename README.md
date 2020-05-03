# Image generation with Qt over cgi

Illustrates a quick method to stream image data produced using C++ std. library and Qt QImage over cgi.   

The complexity of the GUI and graphic engine API's that interact directly with standard C++ is among the deterrents that often push programmers to other prototyping languages and solutions. The image rendering device adopted by Qt implements a transparent class friendly with whatever container data the programmer likes to input. This piece of coding is a humble example that could have been entirely written using Qt's API but its purpose is to show that one can readily control pixels in C++ without learning Qt whose utility is way vaster than displaying graphics. The advantage: C++ native and concurrent programming freedom. The cost: the installation of Qt framework. Of course, any library that offers a method for constructing an image out of pixel content in matrix form can be used instead of Qt.

Julia or Mandelbrot sets are generated as matrices of complex numbers using the template Mtrx.h interface. 

The compiled file, obtained through Qt Creator for instance, can be placed in the cgi-bin of the server so that the image can be generated directly into the browser and thus accessed remotely.
