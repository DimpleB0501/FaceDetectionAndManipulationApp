CC = g++ -std=c++0x
CFLAGS = -c -v -Wall

OPENCVINCLUDES = -I/usr/local/opencv4/include/opencv4
OPENCVINCLUDES += -I/usr/local/opencv4/include/opencv4/opencv2
OPENCVINCLUDES += -DUSE_OPENCV
OPENCVLIBPATH = -L/usr/local/opencv4/lib
OPENCVLIBS = -lopencv_stitching -lopencv_superres  -lopencv_videostab -lopencv_photo -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dpm -lopencv_face -lopencv_fuzzy -lopencv_img_hash -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ml -lopencv_ximgproc -lopencv_calib3d  -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_flann  -lopencv_xobjdetect -lopencv_imgcodecs -lopencv_objdetect -lopencv_xphoto -lopencv_imgproc -lopencv_core
EXTRAOPENCV = -Wl,-rpath,/usr/local/opencv3/lib


SOURCES_TEST = src/main.cpp
OBJECTS_TEST = $(SOURCES_TEST:.cpp = .o)
EXECUTABLE_TEST = mainExample
$(EXECUTABLE_TEST):
	$(CC) $(OPENCVINCLUDES) $(OPENCVLIBPATH) $(OBJECTS_TEST) $(OPENCVLIBS) $(EXTRAOPENCV) -o build/$@

