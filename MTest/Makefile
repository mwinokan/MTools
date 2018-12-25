

M_INTERFACE_DIR = ../MInterface
M_VARS_DIR = ../MVars
M_COLOURS_DIR = ../MColours
M_SPECMANIP_DIR = ../MSpecManip

INCLUDE = -I$(M_INTERFACE_DIR) -I$(M_VARS_DIR) -I$(M_COLOURS_DIR) -I$(M_SPECMANIP_DIR)
LIBSDIR = -L$(HOME)/lib
LIBLOAD = -lMInterface -lMVars -lMColours -lMSpecManip

CXXCOMPL = g++
CXXFLAGS = -g -Wall

MTest: MTest.cpp
	$(CXXCOMPL) $(INCLUDE) -o $@ $(LIBSDIR) $< $(LIBLOAD)

clean: 
	rm MTest