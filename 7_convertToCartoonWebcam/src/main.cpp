#include <opencv2/opencv.hpp>

// Remove black dots (upto 4x4 in size) of noise from a pure black & white image.
// ie: The input image should be mostly white (255) and just contains some black (0) noise
// in addition to the black (0) edges.
void removePepperNoise(cv::Mat &mask)
{
    // For simplicity, ignore the top & bottom row border.
    for (int y=2; y<mask.rows-2; y++) {
        // Get access to each of the 5 rows near this pixel.
        uchar *pThis = mask.ptr(y);
        uchar *pUp1 = mask.ptr(y-1);
        uchar *pUp2 = mask.ptr(y-2);
        uchar *pDown1 = mask.ptr(y+1);
        uchar *pDown2 = mask.ptr(y+2);

        // For simplicity, ignore the left & right row border.
        pThis += 2;
        pUp1 += 2;
        pUp2 += 2;
        pDown1 += 2;
        pDown2 += 2;
        for (int x=2; x<mask.cols-2; x++) {
            uchar v = *pThis;   // Get the current pixel value (either 0 or 255).
            // If the current pixel is black, but all the pixels on the 2-pixel-radius-border are white
            // (ie: it is a small island of black pixels, surrounded by white), then delete that island.
            if (v == 0) {
                bool allAbove = *(pUp2 - 2) && *(pUp2 - 1) && *(pUp2) && *(pUp2 + 1) && *(pUp2 + 2);
                bool allLeft = *(pUp1 - 2) && *(pThis - 2) && *(pDown1 - 2);
                bool allBelow = *(pDown2 - 2) && *(pDown2 - 1) && *(pDown2) && *(pDown2 + 1) && *(pDown2 + 2);
                bool allRight = *(pUp1 + 2) && *(pThis + 2) && *(pDown1 + 2);
                bool surroundings = allAbove && allLeft && allBelow && allRight;
                if (surroundings == true) {
                    // Fill the whole 5x5 block as white. Since we know the 5x5 borders
                    // are already white, just need to fill the 3x3 inner region.
                    *(pUp1 - 1) = 255;
                    *(pUp1 + 0) = 255;
                    *(pUp1 + 1) = 255;
                    *(pThis - 1) = 255;
                    *(pThis + 0) = 255;
                    *(pThis + 1) = 255;
                    *(pDown1 - 1) = 255;
                    *(pDown1 + 0) = 255;
                    *(pDown1 + 1) = 255;
                }
                // Since we just covered the whole 5x5 block with white, we know the next 2 pixels
                // won't be black, so skip the next 2 pixels on the right.
                pThis += 2;
                pUp1 += 2;
                pUp2 += 2;
                pDown1 += 2;
                pDown2 += 2;
            }
            // Move to the next pixel.
            pThis++;
            pUp1++;
            pUp2++;
            pDown1++;
            pDown2++;
        }
    }
}



void cartoonify(cv::Mat srcColor, cv::Mat &dst)
{
    // Convert from BGR color to Grayscale
    cv::Mat gray;
    cvtColor(srcColor, gray, cv::COLOR_BGR2GRAY);

    // Remove the pixel noise with a good Median filter, before we start detecting edges.
    medianBlur(gray, gray, 7);

    cv::Size size = srcColor.size();
    cv::Mat mask = cv::Mat(size, CV_8U);
    cv::Mat edges = cv::Mat(size, CV_8U);
   
    // Generate a nice edge mask, similar to a pencil line drawing.
    Laplacian(gray, edges, CV_8U, 5);
    threshold(edges, mask, 80, 255, cv::THRESH_BINARY_INV);
    // Mobile cameras usually have lots of noise, so remove small
    // dots of black noise from the black & white edge mask.
    removePepperNoise(mask);

    // Do the bilateral filtering at a shrunken scale, since it
    // runs so slowly but doesn't need full resolution for a good effect.
    cv::Size smallSize;
    smallSize.width = size.width/2;
    smallSize.height = size.height/2;
    cv::Mat smallImg = cv::Mat(smallSize, CV_8UC3);
    resize(srcColor, smallImg, smallSize, 0,0, cv::INTER_LINEAR);

    // Perform many iterations of weak bilateral filtering, to enhance the edges
    // while blurring the flat regions, like a cartoon.
    cv::Mat tmp = cv::Mat(smallSize, CV_8UC3);
    int repetitions = 7;        // Repetitions for strong cartoon effect.
    for (int i=0; i<repetitions; i++) {
        int size = 9;           // Filter size. Has a large effect on speed.
        double sigmaColor = 9;  // Filter color strength.
        double sigmaSpace = 7;  // Positional strength. Effects speed.
        cv::bilateralFilter(smallImg, tmp, size, sigmaColor, sigmaSpace);
        cv::bilateralFilter(tmp, smallImg, size, sigmaColor, sigmaSpace);
    }
    cv::Mat bigImg; 
    resize(smallImg, bigImg, size, 0,0, cv::INTER_LINEAR); 
    dst.setTo(0); 
    bigImg.copyTo(dst, mask);	
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
	    cartoonify(cameraFrame, displayedFrame);

	    // Display the processed image onto the screen. 
	    imshow("Cartoonifier", displayedFrame); 


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

