// MSpecManip.hh

#ifndef _M_SPECMANIP
#define _M_SPECMANIP

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include <sys/stat.h>
#include <cmath>

#include "MSpec2D.hh"
#include "MRange.hh"
#include "MColours.hh"

using namespace std;

class MSpecManip {
  public: 
    MSpecManip() {};   // constructor
    ~MSpecManip() {};  // destructor

    // 2D Spectra Manipulation:
    MSpec2D Add(MSpec2D, MSpec2D, double s1 = 1.0, double s2 = 1.0); // addition
    MSpec2D Sub(MSpec2D, MSpec2D, double s1 = 1.0, double s2 = 1.0); // subtraction

    // 2D Spectra Statistics:
    double SumXBetween(MSpec2D, double, int verbosity = 0);
    double SumXBetween(MSpec2D, double, MRange, int verbosity = 0);
    double SumYBetween(MSpec2D, double, int verbosity = 0);
    double SumYBetween(MSpec2D, double, MRange, int verbosity = 0);
    double SumSqXBetween(MSpec2D, double, int verbosity = 0);
    double SumSqXBetween(MSpec2D, double, MRange, int verbosity = 0);
    double SumSqYBetween(MSpec2D, double, int verbosity = 0);
    double SumSqYBetween(MSpec2D, double, MRange, int verbosity = 0);
    double CoeffDetermination(MSpec2D, MSpec2D, int verbosity = 0);
    double CoeffDetermination(MSpec2D, MSpec2D, MRange, int verbosity = 0);

  private:

};

#endif