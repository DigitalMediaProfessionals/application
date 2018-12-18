include ../../env.mk

INC = -I../../dv-user-driver/include -I../common/include -I/usr/include/agg2 `freetype-config --cflags`
LIB = -L../../dv-user-driver -ldmpdv -L../common/lib -ldv700_util -lagg -lfreetype

CXXFLAGS = -pthread -std=c++11 $(OPT) -Wall -Werror -c $(INC)
LDFLAGS = -pthread $(LIB)

DEPS = SegNetBasic_gen.h
OBJS = SegNetBasic_gen.o segnet_post.o
TGT = ../bin/SegNetBasic ../bin/SegNetBasic_threaded

all: $(TGT)

../bin/SegNetBasic: $(OBJS) segnet.o
	$(CXX) -o $@ $^ $(LDFLAGS)

../bin/SegNetBasic_threaded: $(OBJS) segnet_threaded.o
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: $(DEPS)

clean:
	rm -f *.o $(TGT)
