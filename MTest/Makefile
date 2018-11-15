

M_INTERFACE_DIR = ../MInterface

INCLUDE = -I$(M_INTERFACE_DIR)
# LIBSDIR = -L$(M_INTERFACE_DIR)
LIBSDIR = -L$(HOME)/lib
LIBLOAD = -lMInterface

CXXCOMPL = g++
CXXFLAGS = -g -Wall

MTest: MTest.cpp
	$(CXXCOMPL) $(INCLUDE) -o $@ $(LIBSDIR) $< $(LIBLOAD)

clean: 
	rm MTest