include ../../env.mk

INC = -I../../dv-user-driver/include -I../common/include
LIB = -L../../dv-user-driver -ldmpdv -L../common/lib -ldv700_util

CFLAGS = -pthread -std=c++11 -O3 -D$(BDDEF) -Wall -Werror -c $(INC)
LFLAGS = -pthread -std=c++11 -O3

DEPS = YOLOv3_gen.h
OBJS = YOLOv3_gen.o YOLOv3.o
TGT  = ../SDCard/YOLOv3

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)

clean:
	rm *.o
	rm -f $(TGT)
