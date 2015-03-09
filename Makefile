## Uncomment for range checks
CXXFLAGS += -DRANGE_CHECK

## uncomment for maybe faster execution
#CXXFLAGS += -march=native

CXXFLAGS += -std=c++11 -O3  -Wall -Wno-write-strings 
CXXFLAGS += -Wno-comment 
CFLAGS += -fPIC -Wall -ansi -pedantic
LIB_DIRS += 
LIBS += -lm
OBJECTS = tensor.o 

%.o: %.cpp
	$(CXX) $(INCLUDES) -c $(CXXFLAGS) $*.cpp -o $*.o
	$(CXX) $(INCLUDES) -MM $(CXXFLAGS) $*.cpp > $*.d

tensor: tensor.o
	$(CXX) $(LIB_DIRS) $< -o $@ $(LIB_DIRS) $(LIBS)

distclean: clean
	rm -f tensor multiarray static_mat

clean: depclean
	rm -f *.o 

depclean:
	rm -f *.d

FORCE:

test: FORCE tensor
	./tensor

all: FORCE tensor test

-include $(OBJECTS:.o=.d)

.PHONY: clean depclean
