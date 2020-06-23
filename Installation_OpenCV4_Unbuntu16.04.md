### Install dependancies <br/>
`sudo apt-get -y install libopencv-dev build-essential cmake libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev libtiff5-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libxine2-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev libtbb-dev libqt4-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils` <br/>

### To download and build opencv4 run in terminal the following commands <br/> 
* `wget "https://github.com/opencv/opencv/archive/4.0.0.tar.gz" -O opencv.tar.gz` <br/>
* `wget "https://github.com/opencv/opencv_contrib/archive/4.0.0.tar.gz" -O opencv_contrib.tar.gz ` <br/>
* `tar -zxvf opencv.tar.gz ` <br/>
* `tar -zxvf opencv_contrib.tar.gz` <br/>
* `cd opencv-4.0.0` <br/>
* `mkdir build ` <br/>
* `cd build ` <br/>
* `cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local/opencv4 -D OPENCV_EXTRA_MODULES_PATH=/path_to(where your contrib modules are located)/opencv_contrib/modules .. ` <br/>

See the **Notes** below for errors at this step <br/>
* `make -j4 `<br/>
* `sudo make install`<br/>


#### Notes
**Note1** <br/>
/path_to(where your contrib modules are located)<br/>
For example: <br/>
My path is `/home/dimple/opencv_contrib/modules`<br/>
So I will run the following in terminal <br/>
 `cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local/opencv4 -D OPENCV_EXTRA_MODULES_PATH=/home/dimple/opencv_contrib/modules ..` 

**Note2**: During the build I had cmake error due to contrib path, following is the snapshot of the error <br/>
![cmakeError](./Images/cmakeError.png)
<br/> 
I implemented a simple fix to rename the contrib folder from <br/> 
![fix](./Images/fix.png) <br/> 
to <br/> 
![fix1](./Images/nameChange.png) <br/> 
