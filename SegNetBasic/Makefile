include ../../env.mk

INC = -I../../dv-user-driver/include -I../common/include -I/usr/include/agg2 `freetype-config --cflags`
LIB = -L../../dv-user-driver -ldmpdv -L../common/lib -ldv700_util -lagg -lfreetype

CFLAGS = -pthread -std=c++11 $(OPT) -Wall -Werror -c $(INC)
LFLAGS = -pthread $(LIB)

DEPS = SegNetBasic_gen.h
OBJS = SegNetBasic_gen.o segnet_post.o
TGT = ../bin/SegNetBasic ../bin/SegNetBasic_pipelined

all: $(TGT)

../bin/SegNetBasic: $(OBJS) segnet.o
	$(GPP) -o $@ $^ $(LFLAGS)

../bin/SegNetBasic_pipelined: $(OBJS) segnet_pipelined.o
	$(GPP) -o $@ $^ $(LFLAGS)

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o $(TGT)
