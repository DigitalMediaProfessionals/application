include ../../env.mk

INC = -I../../dv-user-driver/include -I../common/include -I/usr/include/agg2 `freetype-config --cflags`
LIB = -L../../dv-user-driver -ldmpdv -L../common/lib -ldv700_util -lagg -lfreetype

CXXFLAGS = -pthread -std=c++11 $(OPT) -Wall -Werror -c $(INC)
LDFLAGS = -pthread $(LIB)

DEPS = YOLOv3_gen.h YOLOv3_param.h
OBJS = YOLOv3_gen.o YOLOv3_post.o
TGT  = ../bin/YOLOv3 ../bin/YOLOv3_pipelined

CXX = $(GPP)

all: $(TGT)

../bin/%: %.o $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp $(DEPS)

clean:
	rm -f *.o $(TGT)
