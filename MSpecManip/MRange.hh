// MRange.hh

#ifndef _M_RANGE
#define _M_RANGE

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MRange {
  public:
    // construction and destruction
    MRange();
    MRange(double aLow, double aHigh);
    MRange(string aName, double aLow, double aHigh);
    MRange(double aLow, double aStep, double aHigh);
    MRange(string aName, double aLow, double aStep, double aHigh);
    ~MRange() {};

    // getters
    double Low(int verbosity = 0);
    double High(int verbosity = 0);
    double Step(int verbosity = 0);
    double Range(int verbosity = 0);
    double NumSteps(int verbosity = 0);
    string Name(int verbosity = 0);
    vector<double> Vector();

    // setters
    void SetLow(double);
    void SetHigh(double);
    void SetStep(double);
    void SetName(string);

  private:
    string name;
    double low;
    double high;
    double step;
    double range;
    int numsteps;

    bool lowSet;
    bool highSet;
    bool stepSet;

    void Calculate();
};

#endif