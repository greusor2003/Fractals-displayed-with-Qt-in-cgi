#include "juliaset.cpp"

int main()
{
    // image size in px
    size_t M = 720;
    size_t N = 1080;

    // fractal depth
    size_t max_iter = 49999;

    // generating constant (determines positioniong on Mandelbrot set)
    cx<double> c = 0.278 + 1i*0.009;

    // zone (north-west south-east rectangle) of tracking in the complex plane (smaller values to zoom in)
    cx<double> NW = -0.5 + 1i*0.5;
    cx<double> SE = 0.5 - 1i*0.5;

    // initial image matrix
    Mtrx <uint8_t> X(M, 3*N); 
    
    // tranforms X to max_iter depth
    juliaset(X, max_iter, NW, SE, c);
        
    // using OpenCV to build and display the image
    cv::Mat nimage(M, N, CV_8UC3);
    nimage.data = X.get_data();
    
    if(!nimage.data ) {
      std::cout <<  "Could not open or find the image" << std::endl;
      return -1;
    }
    
    imwrite( "Julia04.png", nimage );

    std::cout << cv::WINDOW_AUTOSIZE << "\n";
    cv::namedWindow( "Display window", cv::WINDOW_NORMAL );
    cv::imshow( "Display window", nimage );
  
    cv::waitKey(0); 
    
    return 0;
}
