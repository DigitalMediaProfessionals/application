include ../../env.mk

INC = -I../../dv-user-driver/include -I../common/include -I/usr/include/python3.6
LIB = -L../../dv-user-driver -ldmpdv -lboost_python3 -lboost_numpy3

CFLAGS = -pthread -std=c++11 $(OPT) -fPIC -Wall -Werror -c $(INC)
LFLAGS = -pthread -std=c++11 $(OPT) -shared -fPIC

DEPS = YOLOv3Pywrap_gen.h
OBJS = YOLOv3Pywrap_gen.o yolov3_wrap.o dmp_network.o
TGT  = ../bin/yolov3_wrap.so

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

dmp_network.o: ../common/src/dmp_network.cpp
	$(GPP) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o $(TGT)
