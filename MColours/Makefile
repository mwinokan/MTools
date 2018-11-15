
libMColours.so: MColours.o
	g++ -shared $^ -o $@
	cp $@ $(HOME)/lib/

%.o: %.cc
	g++ -c -fPIC $^

demo: demo.cpp
	g++ $^ MColours.o -o $@

clean:
	rm *.o
	rm libMColours.so