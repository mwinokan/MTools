// MSpecManip.hh

#ifndef _M_SPEC2D
#define _M_SPEC2D

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include <sys/stat.h>
#include <algorithm>

#include "MRange.hh"

using namespace std;

class MSpec2D {
  public: 
    MSpec2D(string name = "");  // constructor
    ~MSpec2D();                 // destructor

    // properties
    string name;
    string outSep;

    // data
    size_t numData;
    string xLabel;
    string yLabel;
    string xUnit;
    string yUnit;
    vector<double> xData;
    vector<double> yData;

    // data input functions:
    void Add(double, double);
    bool Load1D(string, char separator = ' ');
    bool Load1D(string, MRange, char separator = ' ');
    bool Load2D(string, char separator = ' ');
    bool Load2D(string, MRange, char separator = ' ');
    void ClearData();
    void ClearAll();

    // data manipulation functions:
    void CalibrateX(double scale, double offset = 0.0);
    void CalibrateY(double scale, double offset = 0.0);

    // statistics:
    double MeanX(int verbose = 0);
    double MeanY(int verbose = 0);

    // set properties:
    void SetName(string);
    void SetPrintSeparator(string);
    void SetLabels(string, string);
    void SetUnits(string, string);

    // data output functions:
    bool Print();
    bool Print(MRange);
    bool Print(string file, bool append = false);
    bool Print(string file, MRange, bool append = false);

    // checks/errors:
    bool CheckEmpty();
  
  private:

    bool FileExists(const string& name);

};

#endif