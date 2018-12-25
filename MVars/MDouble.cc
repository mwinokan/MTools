// MDouble.cc

#include "MDouble.hh"

MDouble::MDouble() {
  name = "";
  unit = "";
  valSet = false;
  errSet = false;
};

MDouble::MDouble(string n) {
  name = n;
  unit = "";
  valSet = false;
  errSet = false;
};

MDouble::MDouble(string n, string u) {
  name = n;
  unit = u;
  valSet = false;
  errSet = false;
};

MDouble::MDouble(double val) {
  name = "";
  unit = "";
  valSet = true;
  errSet = false;
  value = val;
  error = 0.0;
};

MDouble::MDouble(double val, string u) {
  name = "";
  unit = u;
  valSet = true;
  errSet = false;
  value = val;
  error = 0.0;
};

MDouble::MDouble(string n, double val) {
  name = n;
  unit = "";
  valSet = true;
  errSet = false;
  value = val;
  error = 0.0;
};

MDouble::MDouble(string n, double val, string u) {
  name = n;
  unit = u;
  valSet = true;
  errSet = false;
  value = val;
  error = 0.0;
};

MDouble::MDouble(double val, double err) {
  name = "";
  unit = "";
  valSet = true;
  errSet = true;
  value = val;
  error = err;
};

MDouble::MDouble(double val, double err, string u) {
  name = "";
  unit = u;
  valSet = true;
  errSet = true;
  value = val;
  error = err;
};

MDouble::MDouble(string n, double val, double err) {
  name = n;
  unit = "";
  valSet = true;
  errSet = true;
  value = val;
  error = err;
};

MDouble::MDouble(string n, double val, double err, string u) {
  name = n;
  unit = u;
  valSet = true;
  errSet = true;
  value = val;
  error = err;
};

vector <double> MDouble::Vector() {
  vector <double> vec;
  vec.push_back(value);
  vec.push_back(error);
  return vec;
}

void MDouble::SetValue(double val) {
  valSet = true;
  value = val;
}

void MDouble::SetError(double err) {
  errSet = true;
  error = err;
}

void MDouble::Print() {
  if (!valSet) {
    cout << colWarning << "WARNING: " 
         << colVarName << name 
         << colWarning << "value not set." 
         << colClear << endl;
    return;
  }
  cout << colVarName << name
       << colClear << " = "
       << colResult << value;
  if (errSet)
    cout << colClear << " +/- "
         << colResult << error;
  cout << " "
       << colVarType << unit
       << colClear << endl;
}