MARCH = -march=native
CXX = clang++

#SHAPE_DERIVATIVE = -DCOMPUTE_SHAPE_DERIVATIVE -DFD_H_DIFF=1e-4
#SHAPE_DERIVATIVE = -DFD_H_DIFF=1e-6
USE_RT_SCALING = -DUSE_RT_SCALING
#USE_RT_SCALING =

#CXXFLAGS = -std=c++0x -march=core-avx2 -O3 -funroll-loops -Wno-write-strings
CXXFLAGS = -std=c++11 -O3  -Wall -Wno-write-strings 
#CXXFLAGS += -gcc-name=/usr/bin/gcc-4.7 -gxx-name=/usr/bin/g++-4.7
CXXFLAGS += -Wno-comment 
CFLAGS = -fPIC -Wall -ansi -pedantic
CC = gcc

#INCLUDES = -I/usr/include/x86_64-linux-gnu/c++/4.7
LIB_DIRS = 

#LIBS = -ltbb -ltbbmalloc_proxy -ltbbmalloc -lhdf5_cpp -lhdf5 -lmkl_rt -lm
LIBS = -lm
OBJECTS := tensor.o multiarray.o static_mat.o

%.o: %.cpp
	$(CXX) $(INCLUDES) -c $(CXXFLAGS) $*.cpp -o $*.o
	$(CXX) $(INCLUDES) -MM $(CXXFLAGS) $*.cpp > $*.d

-include $(OBJECTS:.o=.d)

tensor: tensor.o
	$(CXX) $(LIB_DIRS) $^ -o $@ $(LIB_DIRS) $(LIBS)

multiarray: multiarray.o
	$(CXX) $(LIB_DIRS) $^ -o $@ $(LIB_DIRS) $(LIBS)

static_mat: static_mat.o
	$(CXX) $(LIB_DIRS) $^ -o $@ $(LIB_DIRS) $(LIBS)


distclean: clean
	rm -f tensor multiarray static_mat

clean: depclean
	rm -f *.o 

depclean:
	rm -f *.d

all: static_mat multiarray tensor


.PHONY: clean depclean 
