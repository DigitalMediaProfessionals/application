include ../../env.mk

INC = -I../common/include -I/usr/include/agg2 `freetype-config --cflags`
LIB = -ldmpdv -L../common/lib -ldv700_util -lagg -lfreetype

CFLAGS = -pthread -std=c++11 $(OPT) -Wall -Werror -c $(INC)
LFLAGS = -pthread $(LIB)

DEPS = YOLOv3_gen.h DisNet_param.h DisNet_gen.h
OBJS = YOLOv3_gen.o DisNet_post.o DisNet_gen.o
TGT  = ../bin/DisNet

all: $(TGT)

../bin/%: %.o $(OBJS)
	$(GPP) $^ -o $@ $(LFLAGS)

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o $(TGT)
