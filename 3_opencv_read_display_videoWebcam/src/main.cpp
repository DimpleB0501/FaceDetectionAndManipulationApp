#include "opencv2/opencv.hpp"
#include <iostream>

int main(){

  // Create a VideoCapture object and open the input file, Enter '0' to use webcam and specify the path of video file VideoCapture cap("cars.mp4") to play pre-recorded video
  cv::VideoCapture cap(0); 
   
  // Check if camera opened successfully
  if(!cap.isOpened()){
    std::cout << "Error opening video stream or file" << std::endl;
    return -1;
  }
	
  while(1){

    cv::Mat frame;
    // Capture frames
    cap >> frame;
 
    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    // Display the resulting frame
    cv::imshow( "Frame", frame );

    // Press  ESC on keyboard to exit
    char c=(char)cv::waitKey(25);
    if(c==27)
      break;
  }
 
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  cv::destroyAllWindows();
	
  return 0;
}
