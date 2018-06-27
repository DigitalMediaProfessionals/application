include ../env.mk

INC = -I../common -I../dv700/include -I../common/include
LIB = -L../dv700/lib -ldv700 -L../common/lib -ldv700_util

LFLAGS = -pthread -std=c++11 -O3
CFLAGS = -pthread -std=c++11 -O3 -D$(BDDEF) -Wall -c $(INC)
OBJS = CaffeSqueezeNet_gen.o squeezeNet.o 
 
TGT=CaffeSqueezeNet

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)

CaffeSqueezeNet_gen.o: CaffeSqueezeNet_gen.h CaffeSqueezeNet_gen.cpp
	$(GPP) $(CFLAGS) CaffeSqueezeNet_gen.cpp


squeezeNet.o: squeezeNet.cpp 
	$(GPP) $(CFLAGS) squeezeNet.cpp	

clean:
	rm *.o
	rm $(TGT)
	
