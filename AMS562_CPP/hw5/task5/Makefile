include Makefile.in

prog: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ main.cpp matrix.cpp
	./prog

../libarray.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^
	$(RANDLIB) $@


.PHONY: clean prog

clean:
	rm -f prog
