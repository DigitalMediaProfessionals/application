include ../env.mk

INC = -I../common -I../dv700/include -I../common/include
LIB = -L../dv700/lib -ldv700 -L../common/lib -ldv700_util

CFLAGS = -pthread -std=c++11 -O3 -D$(BDDEF) -Wall -c  $(INC)
LFLAGS = -pthread -std=c++11 -O3

DEPS = YOLOv3_gen.h
OBJS = YOLOv3_gen.o YOLOv3.o
TGT  = YOLOv3Camera

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)

clean:
	rm *.o
	rm -f $(TGT)
