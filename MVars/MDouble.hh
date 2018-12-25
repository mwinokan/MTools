// MDouble.hh

#ifndef _M_DOUBLE
#define _M_DOUBLE

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include <sys/stat.h>
#include <cmath>

#include "MColours.hh"

using namespace std;

class MDouble {
  public:

    // Construction & Destruction
    MDouble();
    MDouble(string name);
    MDouble(string name, string unit);
    MDouble(double value);
    MDouble(double value, string unit);
    MDouble(string name, double value);
    MDouble(string name, double value, string unit);
    MDouble(double value, double error);
    MDouble(double value, double error, string unit);
    MDouble(string name, double value, double error);
    MDouble(string name, double value, double error, string unit);
    ~MDouble() {};

    // Getters
    double Value() { return value; };
    double Error() { return error; };
    string Unit() { return unit; }
    vector <double> Vector();

    // Setters
    void SetValue(double);
    void SetError(double);

    // Output
    void Print();

  private: 
    string name;
    string unit;
    bool valSet;
    bool errSet;
    double value;
    double error;
};

#endif