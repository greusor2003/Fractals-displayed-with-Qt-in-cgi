#include "juliaset.cpp"
#include <string>
#include <cmath>
#include<stdio.h>

int main(int argc, char* argv[], char* env[])
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
    	// using OpenCV to build and display the image
    	cv::Mat nimage(M, N, CV_8UC3); // OpenCV image as matrix
    	nimage.data = X.get_data();
	
		if(!nimage.data ) 
		{
			std::cout <<  "Could not open or find the image" << std::endl;
			return -1;
    	}
	        // naming the images
		std::string im_name = std::to_string(0) + std::to_string(i) + std::string(".png");
                // path to the location of the images
		std::string path_to_image = "";
	
	
		imwrite(path_to_image + im_name, nimage);
    
        a *= 0.85; b *= 0.85; // adjust the frame for generating the next image (zoom into the set)
		
   }

    return 0;
}
