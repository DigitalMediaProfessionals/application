include ../env.mk

INC = -I../common -I../dv700/include -I../common/include
LIB = -L../dv700/lib -ldv700 -L../common/lib -ldv700_util

LFLAGS = -pthread -std=c++11 -O3
CFLAGS = -pthread -std=c++11 -O3 -D$(BDDEF) -Wall -c $(INC)
OBJS = KerasMobileNet_gen.o mobileNet.o 
 
TGT=KerasMobileNet

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)

KerasMobileNet_gen.o: KerasMobileNet_gen.h KerasMobileNet_gen.cpp
	$(GPP) $(CFLAGS) KerasMobileNet_gen.cpp


mobileNet.o: mobileNet.cpp 
	$(GPP) $(CFLAGS) mobileNet.cpp	

clean:
	rm *.o
	rm $(TGT)
	
