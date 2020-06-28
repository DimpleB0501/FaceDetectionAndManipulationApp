#include <opencv2/opencv.hpp>
#include <iostream>

void pencilSketch(cv::Mat srcColor, cv::Mat &dst)
{
	cv::Mat gray;
	cv::cvtColor(srcColor, gray, cv::COLOR_BGR2GRAY);//GrayScale Image
	const int MEDIAN_BLUR_FILTER_SIZE = 7; 
	cv::medianBlur(gray, gray, MEDIAN_BLUR_FILTER_SIZE);//Removing Noise From Image
	cv::Size size = srcColor.size();
	cv::Mat mask = cv::Mat(size, CV_8U);
	cv::Mat edges = cv::Mat(size, CV_8U);
	const int LAPLACIAN_FILTER_SIZE = 5; 
	cv::Laplacian(gray, edges, CV_8U, LAPLACIAN_FILTER_SIZE);
	const int EDGES_THRESHOLD = 80; 
	cv::threshold(edges, mask, EDGES_THRESHOLD, 255, cv::THRESH_BINARY_INV);
	//this is enough for sketch image
	cv::cvtColor(mask, dst, cv::COLOR_GRAY2BGR);
	return;

}
int main()
{

	cv::Mat image;
	image = cv::imread("/home/dimple/Desktop/C++/convertToPencilSketchImage/src/lena.png");	
	if(!image.data )                              // Check for invalid input
	    {
		std::cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	    }
	cv::Mat dispImage;
	pencilSketch(image, dispImage);

    	cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
   	imshow( "Display window", dispImage);                   // Show our image inside it.

    	cv::waitKey(0);                                          // Wait for a keystroke in the window
   	return 0;
	
}

