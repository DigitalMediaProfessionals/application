include ../../env.mk

INC = -I../../dv-user-driver/include -I../common/include -I/usr/include/agg2
LIB = -L../../dv-user-driver -ldmpdv -L../common/lib -ldv700_util -lagg \
	 -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab \
	 -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib \
	 -lopencv_datasets -lopencv_dpm -lopencv_face -lopencv_freetype \
	 -lopencv_fuzzy -lopencv_hdf -lopencv_line_descriptor -lopencv_optflow \
	 -lopencv_video -lopencv_plot -lopencv_reg -lopencv_saliency -lopencv_stereo \
	 -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_rgbd -lopencv_viz \
	 -lopencv_surface_matching -lopencv_text -lopencv_ximgproc -lopencv_calib3d \
	 -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect \
	 -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs \
	 -lopencv_photo -lopencv_imgproc -lopencv_core \
	 -L/opt/Xilinx/SDK/2018.2/gnu/aarch32/lin/gcc-arm-linux-gnueabi/arm-linux-gnueabihf/libc/usr/lib

CFLAGS = -pthread -std=c++11 $(OPT) -Wall -Werror -c $(INC)
LFLAGS = -pthread -std=c++11 $(OPT)

DEPS = KerasDepthMap_gen.h imagenet_1000_categories.h
OBJS = KerasDepthMap_gen.o depthMap.o
TGT  = ../bin/KerasDepthMap

# %.o: %.cpp $(DEPS)
%.o: %.cpp
	$(GPP) $(CFLAGS) -o $@ $<

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB) $(pkg-config --cflags --libs opencv)

clean:
	rm *.o
	rm -f $(TGT)

