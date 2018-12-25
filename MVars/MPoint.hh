// MPoint.hh

#ifndef _M_POINT
#define _M_POINT

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
#include "MDouble.hh"

using namespace std;

// Coordinate made of two doubles

class MPoint {
  public:

    // Construction & Destruction
    MPoint();
    MPoint(string name);
    ~MPoint() {};

    // Getters
    MDouble X() { return MDouble(name+" X",xVal,xErr,xUnit); };
    MDouble Y() { return MDouble(name+" Y",yVal,yErr,yUnit); };
    double XVal() { return xVal; };
    double XErr() { return xErr; };
    double YVal() { return yVal; };
    double YErr() { return yErr; };

    // Setters
    void Set(MDouble,MDouble);
    void Set(double,double);
    void Set(double,double,double,double);
    void SetX(MDouble);
    void SetX(double, string unit = "");
    void SetX(double, double, string unit = "");
    void SetY(MDouble);
    void SetY(double, string unit = "");
    void SetY(double, double, string unit = "");

    // Output
    void Print();

  private: 
    string name;
    string xUnit;
    string yUnit;
    bool xSet;
    bool ySet;
    double xVal;
    double yVal;
    double xErr;
    double yErr;
};

#endif