// MPoint.cc

#include "MPoint.hh"

MPoint::MPoint() {
  name = "";
  xUnit = "";
  yUnit = "";
  xSet = false;
  ySet = false;
};

MPoint::MPoint(string n) {
  name = n;
  xUnit = "";
  yUnit = "";
  xSet = false;
  ySet = false;
};

void MPoint::Set(MDouble x,MDouble y) {
  xVal = x.Value();
  xErr = x.Error();
  yVal = y.Value();
  yErr = y.Error();
  xUnit = x.Unit();
  yUnit = y.Unit();
  xSet = true;
  ySet = true;
}

void MPoint::Set(double x,double y) {
  xVal = x;
  yVal = y;
  xErr = 0.0;
  yErr = 0.0;
  xSet = true;
  ySet = true;
}

void MPoint::Set(double xv,double xe,double yv,double ye) {
  xVal = xv;
  yVal = yv;
  xErr = xe;
  yErr = ye;
  xSet = true;
  ySet = true;
}

void MPoint::SetX(MDouble x) {
  xVal = x.Value();
  xErr = x.Error();
  xUnit = x.Unit();
  xSet = true;
}

void MPoint::SetX(double v, double e, string u) {
  xVal = v;
  xErr = e;
  xUnit = u;
  xSet = true;
}

void MPoint::SetX(double v, string u) {
  xVal = v;
  xErr = 0.0;
  xUnit = u;
  xSet = true;
}

void MPoint::SetY(MDouble y) {
  yVal = y.Value();
  yErr = y.Error();
  yUnit = y.Unit();
  ySet = true;
}

void MPoint::SetY(double v, double e, string u) {
  yVal = v;
  yErr = e;
  yUnit = u;
  ySet = true;
}

void MPoint::SetY(double v, string u) {
  yVal = v;
  yErr = 0.0;
  yUnit = u;
  ySet = true;
}

void MPoint::Print() {
  if (!xSet) {
    cout << colWarning << "WARNING: " 
         << colVarName << name 
         << colWarning << " x-value not set." 
         << colClear << endl;
    return;
  }
  if (!ySet) {
    cout << colWarning << "WARNING: " 
         << colVarName << name 
         << colWarning << " y-value not set." 
         << colClear << endl;
    return;
  }
  cout << colVarName << name
       << colClear << "."
       << colFunc << "X"
       << colClear << "() = "
       << colResult << xVal
       << colClear << " +/- "
       << colResult << xErr
       << " "
       << colVarType << xUnit
       << colClear << endl;
  cout << colVarName << name
       << colClear << "."
       << colFunc << "Y"
       << colClear << "() = "
       << colResult << yVal
       << colClear << " +/- "
       << colResult << yErr
       << " "
       << colVarType << yUnit
       << colClear << endl;
}