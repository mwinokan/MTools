
# compile a shared object library

NAME = MVars

# additional class files:

MORE_NAMES = MDouble MPoint

# dependencies:

M_COLOURS_DIR = ../MColours/
INCLUDE = -I$(M_COLOURS_DIR)
LIBSDIR = -L$(M_COLOURS_DIR)
LIBLOAD = -lMColours

# compilation:

lib$(NAME).so: $(NAME).o $(MORE_NAMES:=.o)
	g++ $(INCLUDE) -o $@ -shared $(LIBSDIR) $^ $(LIBLOAD)
	cp $@ $(HOME)/lib/

%.o: %.cc
	g++ -c -fPIC -std=c++11 $(INCLUDE) $^

clean:
	rm *.o
	rm *.so
	rm $(HOME)/lib/lib$(NAME).so