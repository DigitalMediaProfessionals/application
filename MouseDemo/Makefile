include ../../env.mk

INC = -I../../dv-user-driver/include -I../common/include -I/usr/include/agg2 `freetype-config --cflags`
LIB = -L../../dv-user-driver -ldmpdv -L../common/lib -ldv700_util -lagg -lfreetype

CFLAGS = -pthread -std=c++11 $(OPT) -Wall -Werror -c $(INC)
LFLAGS = -pthread -std=c++11 $(OPT)

OBJS = MouseDemo.o
TGT  = ../bin/MouseDemo

%.o: %.cpp $(DEPS)
	$(GPP) $(CFLAGS) -o $@ $<

all : $(OBJS)
	$(GPP) $(LFLAGS) $(OBJS) -o $(TGT) $(LIB)

clean:
	rm -f *.o $(TGT)
