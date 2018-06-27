include ../../env.mk

INC = -I../../dv-user-driver/include -I../common/include
LIB = -L../../dv-user-driver/lib -ldv700 -L../common/lib -ldv700_util

CFLAGS = -pthread -std=c++11 -O3 -D$(BDDEF) -Wall -c  $(INC)
LFLAGS = -pthread -std=c++11 -O3 

DEPS = imagenet_1000_categories.h CaffeGoogLeNet_gen.h
OBJS = CaffeGoogLeNet_gen.o googleNet.o
TGT  = ../SDCard/CaffeGoogLeNet

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)

clean:
	rm *.o
	rm -f $(TGT)
