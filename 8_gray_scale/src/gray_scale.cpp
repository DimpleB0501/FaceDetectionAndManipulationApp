#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{

       //Converting the image into gray scale
       Mat img_gray;
       img_gray = imread("/home/mangla/Desktop/upliftProject-AppDev/UpliftProject-AppDevelopment/8_gray_scale/src/tweety.png",IMREAD_GRAYSCALE);

       //If image not found
       if (!img_gray.data)
       {
	       cout<<"Could not open or find the image";
	       return -1;
       }

       namedWindow("Display Window", WINDOW_AUTOSIZE); //Creating a window for display
       imshow("Display Window",img_gray); //Show image inside the window

       waitKey(0); //Wait for a keystroke 
       return 0;
}

