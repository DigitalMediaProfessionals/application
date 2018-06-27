include ../../env.mk

INC = -I../include

# source files.
SRC =  	util_draw.cpp util_input.cpp nanojpeg.cpp v4l2-cam.cpp
 
OBJ = $(SRC:.cpp=.o)
	
OUT = ../lib/libdv700_util.a
 
# include directories
INCLUDES = -I. -I../include/ -I../../dv700/include
 
# C++ compiler flags (-g -O2 -Wall)
CCFLAGS =  -pthread -std=c++11 -O3 -D$(BDDEF) -Wall
 
# compiler
CCC = $(GPP)
 
# library paths
LIBS = -L../ -L/usr/local/lib -lm 
 
# compile flags
LDFLAGS = -O3
 
.SUFFIXES: .cpp
 
all: $(OUT)
 
.cpp.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@
 
$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)
 
clean:
	rm -f $(OBJ) $(OUT) Makefile.bak# DO NOT DELETE


