include ../env.mk

INC = -I../common -I../dv700/include -I../common/include
LIB = -L../dv700/lib -ldv700 -L../common/lib -ldv700_util

LFLAGS = -pthread -std=c++11 -O3
CFLAGS = -pthread -std=c++11 -O3 -D$(BDDEF) -Wall -c  $(INC)
OBJS = SegNetBasic_gen.o segnet.o

TGT=SegNetBasic

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)

SegNetBasic_gen.o: SegNetBasic_gen.h SegNetBasic_gen.cpp
	$(GPP) $(CFLAGS) SegNetBasic_gen.cpp

segnet.o: segnet.cpp
	$(GPP) $(CFLAGS) segnet.cpp	

clean:
	rm *.o
	rm -f $(TGT)
