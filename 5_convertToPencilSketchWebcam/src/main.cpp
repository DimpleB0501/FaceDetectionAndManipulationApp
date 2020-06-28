#include <opencv2/opencv.hpp>

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
	auto cameraNumber = 0; 
	cv::VideoCapture camera(cameraNumber);//Open VideoCapture Device
	
	if (!camera.isOpened()) { 
	   std::cerr<<"ERROR: Could not access the camera or video!"<< std::endl; 
	   exit(1); 
	} 

	// Try to set the camera resolution. 
	//camera.set(cv::CAP_PROP_FRAME_WIDTH, 640); 
	//camera.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

	while (true) { 
	    // Grab the next camera frame. 
	    cv::Mat cameraFrame; 
	    camera >> cameraFrame; 
	    if (cameraFrame.empty()) { 
		std::cerr<<"ERROR: Couldn't grab a camera frame."<< 
		std::endl; 
		exit(1); 
	    } 
	    // Create a blank output image, that we will draw onto. 
	    cv::Mat displayedFrame; 

	    // Run the cartoonifier filter on the camera frame. 
	    pencilSketch(cameraFrame, displayedFrame); 

	    // Display the processed image onto the screen. 
	    imshow("Pencil Sketch", displayedFrame); 


	    // IMPORTANT: Wait for atleast 20 milliseconds, 
	    // so that the image can be displayed on the screen! 
	    // Also checks if a key was pressed in the GUI window. 
	    // Note that it should be a "char" to support Linux. 
	    auto keypress = cv::waitKey(20); // Needed to see anything! 
	    if (keypress == 27) { // Escape Key 
	       // Quit the program! 
	       break; 
	    } 
	 }//end while	
}

