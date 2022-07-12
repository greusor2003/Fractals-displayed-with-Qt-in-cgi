# Image generation with Qt over cgi

These are some examples of interacting with image data produced using the C++ std. library and Qt QImage over cgi.The server side interface is Cgicc. The client side interface uses Javascript.  

The complexity of the GUI and graphic engine API's that interact directly with standard C++ is among the deterrents that often push programmers to other prototyping languages and solutions. The image rendering device adopted by Qt implements a transparent class friendly with whatever container data the programmer likes to input. This piece of coding is a humble example that could have been entirely written using Qt's API but its purpose is to show that one can readily control pixels in C++ without learning Qt whose utility is way vaster than displaying graphics. The advantage: C++ native and concurrent programming freedom. The cost: the installation of the Qt framework. Of course, any library that offers a method for constructing an image out of pixel content in matrix form can be used instead of Qt.

The Julia set is generated as a matrix of complex numbers using the matrix class defined in Mtrx.cpp. 

To compile, please load the project Juliaset.pro in Qt Creator, build and run.
The compiled file can be placed in the cgi-bin of the server so that the image can be generated directly into the browser and thus interacting with it remotely via form_cgi.html.

Juliaset is an already available executable binary.


