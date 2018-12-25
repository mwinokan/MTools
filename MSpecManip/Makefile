
# compile a shared object library

NAME = MSpecManip

# additional class files:

MORE_NAMES = MSpec2D MRange

# dependencies:

M_COLOURS_DIR = ../MColours/
M_VARS_DIR = ../MVars/
INCLUDE = -I$(M_COLOURS_DIR) -I$(M_VARS_DIR)
LIBSDIR = -L$(HOME)/lib
LIBLOAD = -lMColours -lMVars

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