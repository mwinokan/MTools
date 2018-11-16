#include "MColours.hh"

#include <iostream>
using namespace std;

int main() {
	
  cout << colBold << "colBold (1m)" << colClear << endl;
	cout << colVarName << "colVarName (36m)" << colClear << endl;
  cout << colVarType << "colVarType (95m)" << colClear << endl;
  cout << colFunc << "colFunc (36;4m)" << colClear << endl;
  cout << colFile << "colFile (38;5;11m)" << colClear << endl;
  cout << colError << "colError (31;1m)" << colClear << endl;
  cout << colSuccess << "colSuccess (32;1m)" << colClear << endl;
  cout << colResult << "colResult (34m)" << colClear << endl;
  cout << colWarning << "colWarning (38;5;166m)" << colClear << endl;
  cout << colArg << "colArg (38;5;154m)" << colClear << endl;
  cout << colInverse << "colInverse (34m)" << colClear << endl;
  cout << colClear << "colClear (0m)" << colClear << endl;

  cout << endl;

  cout << colBold << "demo" << colClear << endl;

  cout << "In: " 
       << colFile << "file.cpp" 
       << colClear << " line 10 : " 
       << colVarName << "class" 
       << colClear << "." 
       << colFunc << "function" 
       << colClear << "((" 
       << colVarType << "double" 
       << colClear << ") "
       << colArg << "arg" 
       << colClear << " ) = "
       << colResult << "42.0" 
       << colClear << endl;
	
}
