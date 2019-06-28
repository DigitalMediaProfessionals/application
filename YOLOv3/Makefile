include ../../env.mk

INC = -I../common/include -I/usr/include/agg2 `freetype-config --cflags`
LIB = -ldmpdv -L../common/lib -ldv700_util -lagg -lfreetype

CFLAGS = -pthread -std=c++11 $(OPT) -Wall -Werror -c $(INC)
LFLAGS = -pthread $(LIB)

DEPS = YOLOv3_gen.h YOLOv3_param.h
OBJS = YOLOv3_gen.o YOLOv3_post.o
TGT  = ../bin/YOLOv3 ../bin/YOLOv3_pipelined

all: $(TGT)

../bin/%: %.o $(OBJS)
	$(GPP) $^ -o $@ $(LFLAGS)

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o $(TGT)
