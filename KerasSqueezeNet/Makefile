include ../env.mk

INC = -I../common -I../dv700/include -I../common/include
LIB = -L../dv700/lib -ldv700 -L../common/lib -ldv700_util

LFLAGS = -pthread -std=c++11 -O3
CFLAGS = -pthread -std=c++11 -O3 -D$(BDDEF) -Wall -c $(INC)
OBJS = KerasSqueezeNet_gen.o squeezeNet.o 
 
TGT=KerasSqueezeNet

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)

KerasSqueezeNet_gen.o: KerasSqueezeNet_gen.h KerasSqueezeNet_gen.cpp
	$(GPP) $(CFLAGS) KerasSqueezeNet_gen.cpp


squeezeNet.o: squeezeNet.cpp 
	$(GPP) $(CFLAGS) squeezeNet.cpp	

clean:
	rm *.o
	rm $(TGT)
	
