include ../env.mk

INC = -I../common -I../dv700/include -I../common/include
LIB = -L../dv700/lib -ldv700 -L../common/lib -ldv700_util

LFLAGS = -pthread -std=c++11 -O3
CFLAGS = -pthread -std=c++11 -O3 -D$(BDDEF) -Wall -c  $(INC)
OBJS = KerasGoogLeNet_gen.o    googleNet.o

TGT=KerasGoogLeNet

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)
	

KerasGoogLeNet_gen.o: KerasGoogLeNet_gen.h KerasGoogLeNet_gen.cpp
	$(GPP) $(CFLAGS) KerasGoogLeNet_gen.cpp
	
googleNet.o: googleNet.cpp
	$(GPP) $(CFLAGS) googleNet.cpp	

clean:
	rm *.o
	rm -f $(TGT)
