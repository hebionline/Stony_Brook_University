#include Makefile.in
CXX = g++
CXXFLAGS = -std=c++11 -g
AR = ar
ARFLAGS = rv
RANDLIB = ranlib

#all: libarray.a prog

prog: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ main.cpp array.cpp
	./prog

#libams562proj1.a:
#	$(MAKE) -C srcs

../libarray.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	$(RANDLIB) $@


.PHONY: clean prog

clean:
#	make clean
	rm -f prog