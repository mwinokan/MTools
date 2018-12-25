# MTools

Simple C++ libraries for command line interfacing and 2D spectrum manipulation. Compile separately using ```make``` within the various library directories.

### MColours

Escape strings to add ANSI colours to console/terminal output of your programs.

### MInterface

Class for flexible command line argument parsing for your programs. Add new arguments via ```AddArg(string flag, string description, type &variable)``` and parse via ```ParseArgs(int argc, char** argv)```.

### MSpecManip

Beginnings of a spectrum manipulation library. Manipulator class ```MSpecManip``` which uses:

- ```MRange``` class to define ranges for variables.
- ```MSpec2D``` class to define, load, and work with two-dimensional spectral data.

### MVars

Beginnings of a set of custom variable classes.

- ```MDouble``` double precision floating value with uncertainty.
- ```MPoint``` two-dimensional double precision floating coordinate with uncertainty.

### MTest

Example single ```.cpp``` file project using the various ```MTools``` classes, and example ```Makefile```.
