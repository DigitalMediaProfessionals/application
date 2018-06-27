include ../env.mk

INC = -I../common -I../dv700/include -I../common/include
LIB = -L../dv700/lib -ldv700 -L../common/lib -ldv700_util

LFLAGS = -pthread -std=c++11 -O3 
CFLAGS = -pthread -std=c++11 -O3 -D$(BDDEF) -c  $(INC)
OBJS = CaffeGoogLeNet_gen.o    googleNet.o

TGT=CaffeGoogLeNet

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)
	

CaffeGoogLeNet_gen.o: CaffeGoogLeNet_gen.h CaffeGoogLeNet_gen.cpp
	$(GPP) $(CFLAGS) CaffeGoogLeNet_gen.cpp
	
googleNet.o: googleNet.cpp
	$(GPP) $(CFLAGS) googleNet.cpp	

clean:
	rm *.o
	rm -f $(TGT)
