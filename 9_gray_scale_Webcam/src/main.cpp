	#include<opencv2/highgui/highgui.hpp>
	#include <opencv2/imgproc/imgproc.hpp>
	#include<iostream>

	using namespace cv;
	using namespace std;

	int main()
	{

// Create a VideoCapture object and open the input file, Enter '0' to use webcam and specify the path of video file VideoCapture cap to play pre-recorded video

  		cv::VideoCapture cap(0); 
   
 		// Check if camera opened successfully
		if(!cap.isOpened())
		{
    			std::cout << "Error opening video stream or file" << std::endl;
    			return -1;
 		}

		namedWindow("MyVideo",WINDOW_AUTOSIZE);

		 while (1)
   		 {
        		Mat frame;

        		bool bSuccess = cap.read(frame); // read a new frame from video

         		if (!bSuccess)
        		{
             			cout << "Cannot read a frame from video stream" << endl;
             			break;
        		}

        		Mat grayscale;
        		cvtColor(frame, grayscale, cv::COLOR_RGB2GRAY); 

        		imshow("MyVideo", grayscale); 

        		if (waitKey(30) == 27) 
       			{
            			cout << "esc key is pressed by user" << endl;
            			break; 
       			}
    		}
    		return 0;

		}
	

