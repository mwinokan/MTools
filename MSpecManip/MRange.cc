// MRange.cc

#include "MRange.hh"
#include "MColours.hh"

MRange::MRange() {
  name = "";
  lowSet = false;
  highSet = false;
  stepSet = false;
}

MRange::MRange(double aLow, double aHigh) {
  name = "";
  low = aLow;
  high = aHigh;
  lowSet = true;
  highSet = true;
  stepSet = false;
  Calculate();
}

MRange::MRange(string aName, double aLow, double aHigh) {
  name = aName;
  low = aLow;
  high = aHigh;
  lowSet = true;
  highSet = true;
  stepSet = false;
  Calculate();
}

MRange::MRange(double aLow, double aStep, double aHigh) {
  name = "";
  low = aLow;
  high = aHigh;
  step = aStep;
  lowSet = true;
  highSet = true;
  stepSet = true;
  Calculate();
}

MRange::MRange(string aName, double aLow, double aStep, double aHigh) {
  name = aName;
  low = aLow;
  high = aHigh;
  step = aStep;
  lowSet = true;
  highSet = true;
  stepSet = true;
  Calculate();
}

void MRange::Calculate() {
  if (!lowSet || !highSet) return;

  range = high - low;

  if (!stepSet) {
    numsteps = 0;
  } else {
    if (range == 0) {
      numsteps = 1;
      step = 0.0;
    } else {
      if (step > range) {
        cout << colWarning << "WARNING: step size larger than range for "
             << colVarName << name << colClear << endl;
        cout << colWarning << "         defaulted to " << colVarName << "step" 
             << colWarning << " = " << colVarName << "range" << colClear << endl;
        step = range;
        numsteps = 2;
      }
      numsteps = range / step + 1;
    }
  }
}

double MRange::Low(int verbosity) {
  if (verbosity > 0) 
    cout << colVarName << name << colClear << "." << colFunc << "Low" 
         << colClear << "() = " << colResult << low << colClear << endl;
  return low;
}

double MRange::High(int verbosity) {
  if (verbosity > 0) 
    cout << colVarName << name << colClear << "." << colFunc << "High" 
         << colClear << "() = " << colResult << high << colClear << endl;
  return high;
}

double MRange::Step(int verbosity) {
  if (verbosity > 0) 
    cout << colVarName << name << colClear << "." << colFunc << "Step" 
         << colClear << "() = " << colResult << step << colClear << endl;
  return step;
}

double MRange::Range(int verbosity) {
  if (verbosity > 0) 
    cout << colVarName << name << colClear << "." << colFunc << "Range" 
         << colClear << "() = " << colResult << range << colClear << endl;
  return step;
}

double MRange::NumSteps(int verbosity) {
  if (verbosity > 0) 
    cout << colVarName << name << colClear << "." << colFunc << "NumSteps" 
         << colClear << "() = " << colResult << numsteps << colClear << endl;
  return numsteps;
}

string MRange::Name(int verbosity) {
  if (verbosity > 0) 
    cout << colVarName << name << colClear << "." << colFunc << "Name" 
         << colClear << "() = " << colResult << name << colClear << endl;
  return name;
}

void MRange::SetLow(double value) {
  low = value;
  lowSet = true;
  Calculate();
}

void MRange::SetHigh(double value) {
  high = value;
  highSet = true;
  Calculate();
}

void MRange::SetStep(double value) {
  step = value;
  stepSet = true;
  Calculate();
}

vector <double> MRange::Vector() {
  vector <double> steps;
  for (int i = 0; i < numsteps; i++)
    steps.push_back(low + step*i);
  return steps;
}