# To compile and run type <br/>
* `cd opencv_read_display_image` <br/>
* `make` <br/>
* `cd build` <br/>
* `./mainExample /path_to_image/tweety.png`  <br/>
 <br/>
 
# Fixing .so error  
If there is an error of missing **.so** files. <br/>
I had an error of missing **libopencv_highgui.so.4.0** you can search where exactly your file is by the following command  <br/>
`sudo find / -name "libopencv_highgui.so.4.0"` <br/>
following will be the output <br/>
![search](./Images/search.png)
Once you find the correct path, create a file called /etc/ld.so.conf.d/opencv.conf <br/>
and write to it the paths to the folders where the libraries are stored. <br/>
Do the following to achieve this
* `cd /etc/ld.so.conf.d/` <br/>
* `sudo touch opencv.conf` <br/>
* `sudo gedit opencv.conf` <br/>
and add the path till lib as shown below <br/>
![fix](./Images/fix_so.png) <br/>
Then run <br/>
sudo ldconfig -v <br/>
<br/>
Now run from build `./mainExample /path_to_image/tweety.png`  <br/> again and your code should read and display image. <br/>
