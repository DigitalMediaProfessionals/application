include ../../env.mk

INC = -I../common/include -I/usr/include/agg2 `freetype-config --cflags`
LIB = -ldmpdv -L../common/lib -ldv700_util -lagg -lfreetype

CFLAGS = -pthread -std=c++11 $(OPT) -Wall -Werror -c $(INC)
LFLAGS = -pthread -std=c++11 $(OPT)

DEPS = imagenet_1000_categories.h KerasSqueezeNet_gen.h
OBJS = KerasSqueezeNet_gen.o squeezeNet.o
TGT  = ../bin/KerasSqueezeNet

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)

clean:
	rm -f *.o $(TGT)
