// MSpec2D.cc

#include "MSpec2D.hh"
#include "MColours.hh"

MSpec2D::MSpec2D(string thisName) {
  name = thisName;
  numData = 0;
  xLabel = "x";
  yLabel = "y";
  xUnit = "";
  yUnit = "";
  xData.clear();
  yData.clear();
  outSep = " ";
}

MSpec2D::~MSpec2D() {
}

void MSpec2D::ClearData() {
  numData = 0;
  xData.clear();
  yData.clear();
}

void MSpec2D::ClearAll() {
  numData = 0;
  xLabel = "x";
  yLabel = "y";
  xUnit = "";
  yUnit = "";
  xData.clear();
  yData.clear();
  outSep = " ";
}

// x' = x * s + o
void MSpec2D::CalibrateX(double scale, double offset) {
  for (size_t i = 0; i < xData.size(); i++) {
    xData[i] *= scale;
    xData[i] += offset;
  }
}

// x' = x * s + o
void MSpec2D::CalibrateY(double scale, double offset) {
  for (size_t i = 0; i < yData.size(); i++) {
    yData[i] *= scale;
    yData[i] += offset;
  }
}

bool MSpec2D::Load2D(string file, char separator) {
  if (FileExists(file)) {
    ifstream inFile(file);
    string line;
    while (getline(inFile,line)) {
      if (line.at(line.find_first_not_of(' ')) == '#') continue; // ignore lines starting with #
      if (separator != ' ') replace(line.begin(), line.end(), separator, ' '); // change to space-delimited
      istringstream sstream(line);
      double xTemp, yTemp;
      sstream >> xTemp >> yTemp;
      Add(xTemp,yTemp);
    }
    return true;
  } else {
    cout << colError << "ERROR: File "
         << colFile << file
         << colError << "not accessible!"
         << colClear << endl;
    return false;
  }
}

bool MSpec2D::Load2D(string file, MRange range, char separator) {
  if (FileExists(file)) {
    ifstream inFile(file);
    string line;
    while (getline(inFile,line)) {
      if (line.at(line.find_first_not_of(' ')) == '#') continue; // ignore lines starting with #
      if (separator != ' ') replace(line.begin(), line.end(), separator, ' '); // change to space-delimited
      istringstream sstream(line);
      double xTemp, yTemp;
      sstream >> xTemp >> yTemp;
      if (xTemp >= range.Low() && xTemp <= range.High())
        Add(xTemp,yTemp);
    }
    return true;
  } else {
    cout << colError << "ERROR: File "
         << colFile << file
         << colError << "not accessible!"
         << colClear << endl;
    return false;
  }
}

void MSpec2D::Add(double x, double y) {
  xData.push_back(x);
  yData.push_back(y);
  numData++;
}

double MSpec2D::MeanX(int verbosity) {
  if (CheckEmpty()) return (double) NULL;

  double sum = 0.0;
  for (size_t i = 0; i < xData.size(); i++ ) {
    sum += xData[i];
  }
  double mean = sum / (double) xData.size();
  if (verbosity > 0) 
    cout << colVarName << name << colClear << "." << colFunc << "MeanY" 
         << colClear << "() = " << colResult << mean << colClear << endl;
  return mean;
}

double MSpec2D::MeanY(int verbosity) {
  if (CheckEmpty()) return (double) NULL;

  double sum = 0.0;
  for (size_t i = 0; i < yData.size(); i++ ) {
    sum += yData[i];
  }
  double mean = sum / (double) yData.size();
  if (verbosity > 0) 
    cout << colVarName << name << colClear << "." << colFunc << "MeanY" 
         << colClear << "() = " << colResult << mean << colClear << endl;
  return mean;
}

bool MSpec2D::Print() {
  if (CheckEmpty()) return false;

  for (size_t i = 0; i < numData; i++) {
    cout << colVarName << name 
         << colClear << "["
         << i << "] = ("
         << colResult << xData[i] 
         << colClear << "," 
         << colResult << yData[i] 
         << colClear << ")" << endl;
  }
  return true;
}

bool MSpec2D::Print(string file, bool append) {
  if (CheckEmpty()) return false;

  ofstream outFile(file);
  outFile << "# " << name << ": " 
          << xLabel << "[" << xUnit << "]" << outSep
          << yLabel << "[" << yUnit << "]" << endl;

  for (size_t i = 0; i < numData; i++) {
    outFile << xData[i] << outSep << yData[i] << endl;
  }
  return true;
}

void MSpec2D::SetLabels(string xL, string yL) {
  xLabel = xL;
  yLabel = yL;
}

void MSpec2D::SetUnits(string xU, string yU) {
  xUnit = xU;
  yUnit = yU;
}

void MSpec2D::SetName(string thisName) {
  name = thisName;
}

void MSpec2D::SetPrintSeparator(string sep) {
  outSep = sep;
}

bool MSpec2D::FileExists(const string& name) {
  struct stat buffer;
  if (stat (name.c_str(), &buffer) == 0) return true;
  else return false;
}

bool MSpec2D::CheckEmpty() {
  if (numData == 0 || xData.size() == 0 || yData.size() == 0 ) {
    cout << colError << "ERROR: Spec2D '"
         << colVarName << name
         << colError << "' is empty!"
         << colClear << endl;
    return true;
  } else return false;
}