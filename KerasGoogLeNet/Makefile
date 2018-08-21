include ../../env.mk

INC = -I../../dv-user-driver/include -I../common/include
LIB = -L../../dv-user-driver -ldmpdv -L../common/lib -ldv700_util

CFLAGS = -pthread -std=c++11 -O3 -Wall -Werror -c  $(INC)
LFLAGS = -pthread -std=c++11 -O3 

DEPS = imagenet_1000_categories.h KerasGoogLeNet_gen.h
OBJS = KerasGoogLeNet_gen.o googleNet.o
TGT  = ../SDCard/KerasGoogLeNet

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)

clean:
	rm *.o
	rm -f $(TGT)
