include ../../env.mk

INC = -I../../dv-user-driver/include -I../common/include -I/usr/include/agg2 `freetype-config --cflags`
LIB = -L../../dv-user-driver -ldmpdv -L../common/lib -ldv700_util -lagg -lfreetype

CFLAGS = -pthread -std=c++11 $(OPT) -Wall -Werror -c $(INC)
LFLAGS = -pthread $(LIB)

DEPS = DeconvNetBasic_gen.h
OBJS = DeconvNetBasic_gen.o postproc.o
TGT = ../bin/DeconvNetBasic_pipelined

all: $(TGT)

../bin/DeconvNetBasic: $(OBJS) deconvnet.o
	$(GPP) -o $@ $^ $(LFLAGS)

../bin/DeconvNetBasic_pipelined: $(OBJS) deconvnet_pipelined.o
	$(GPP) -o $@ $^ $(LFLAGS)

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o $(TGT)
