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

bool MSpec2D::Load1D(string file, char separator) {
  if (FileExists(file)) {
    int xTemp = 1;
    ifstream inFile(file);
    string line;
    while (getline(inFile,line)) {
      if (line.at(line.find_first_not_of(' ')) == '#') continue; // ignore lines starting with #
      if (separator != ' ') replace(line.begin(), line.end(), separator, ' '); // change to space-delimited
      istringstream sstream(line);
      double yTemp;
      sstream >> yTemp;
      Add((double)xTemp,yTemp);
      xTemp++;
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

bool MSpec2D::Load1D(string file, MRange range, char separator) {
  if (FileExists(file)) {
    int xTemp = 1;
    ifstream inFile(file);
    string line;
    while (getline(inFile,line)) {
      if (line.at(line.find_first_not_of(' ')) == '#') continue; // ignore lines starting with #
      if (separator != ' ') replace(line.begin(), line.end(), separator, ' '); // change to space-delimited
      istringstream sstream(line);
      double yTemp;
      sstream >> yTemp;
      if ((double)xTemp >= range.Low() && (double)xTemp <= range.High())
        Add((double)xTemp,yTemp);
      xTemp++;
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

bool MSpec2D::Load(string file, int col1, int col2, char separator) {
  if (FileExists(file)) {
    ifstream inFile(file);
    string line;
    int counter = 1;
    while (getline(inFile,line)) {
      if (line.at(line.find_first_not_of(' ')) == '#') continue; // ignore lines starting with #
      if (separator != ' ') replace(line.begin(), line.end(), separator, ' '); // change to space-delimited
      
      istringstream iss(line);

      double val1;
      double val2;
      bool set1 = false;
      bool set2 = false;
      int thisCol = 0;
      double num = 0;
      while(iss >> num || !iss.eof()) {
        thisCol++;
        if(iss.fail()) {
            iss.clear();
            string dummy;
            iss >> dummy;
            continue;
        }
        // cout << thisCol << " " << num << endl;
        if (thisCol == col1) {
          set1 = true;
          val1 = num;
        }
        if (thisCol == col2) {
          set2 = true;
          val2 = num;
        }
      }

      if ( col1 == 0 ) {
        set1 = true;
        val1 = counter;
      }
      if ( col2 == 0 ) {
        set2 = true;
        val2 = counter;
      }

      if ( set1 && set2 ) {
        Add(val1,val2);
      } else {
        cout << colWarning << "WARNING: Could not find desired columns. Data point "
             << colArg << counter
             << colWarning << " skipped." 
             << colClear << endl;
      }
      counter++;

    }

    if (xData.size() > 0 && yData.size() > 0 ) {
      return true;
    } else {
      cout << colError << "ERROR: No data loaded from "
           << colFile << file
           << colError << "!"
           << colClear << endl;
    }
  } else {
    cout << colError << "ERROR: File "
         << colFile << file
         << colError << "not accessible!"
         << colClear << endl;
    return false;
  }
  return false;
}

bool MSpec2D::Load(string file, MRange range, int col1, int col2, char separator) {
  if (FileExists(file)) {
    ifstream inFile(file);
    string line;
    int counter = 1;
    while (getline(inFile,line)) {
      if (line.at(line.find_first_not_of(' ')) == '#') continue; // ignore lines starting with #
      if (separator != ' ') replace(line.begin(), line.end(), separator, ' '); // change to space-delimited
      
      istringstream iss(line);

      double val1;
      double val2;
      bool set1 = false;
      bool set2 = false;
      int thisCol = 0;
      double num = 0;
      while(iss >> num || !iss.eof()) {
        thisCol++;
        if(iss.fail()) {
            iss.clear();
            string dummy;
            iss >> dummy;
            continue;
        }
        // cout << thisCol << " " << num << endl;
        if (thisCol == col1) {
          set1 = true;
          val1 = num;
        }
        if (thisCol == col2) {
          set2 = true;
          val2 = num;
        }
      }

      if ( col1 == 0 ) val1 = counter;
      if ( col2 == 0 ) val2 = counter;

      if ( set1 && set2 ) {
        if ( val1 >= range.Low() && val2 <= range.High() ) {
          Add(val1,val2);
        }
      } else {
        cout << colWarning << "WARNING: Could not find desired columns. Data point "
             << colArg << counter
             << colWarning << " skipped." 
             << colClear << endl;
      }
      counter++;

    }

    if (xData.size() > 0 && yData.size() > 0 ) {
      return true;
    } else {
      cout << colError << "ERROR: No data loaded from "
           << colFile << file
           << colError << "!"
           << colClear << endl;
    }
  } else {
    cout << colError << "ERROR: File "
         << colFile << file
         << colError << "not accessible!"
         << colClear << endl;
    return false;
  }
  return false;
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

double MSpec2D::MeanX(MRange range, int verbosity) {
  if (CheckEmpty()) return (double) NULL;

  double sum = 0.0;
  int numPointsInRange = 0;
  for (size_t i = 0; i < xData.size(); i++ ) {
    if ( xData[i] >= range.Low() && xData[i] <= range.High() ) {
      numPointsInRange++;
      sum += xData[i];
    }
  }
  double mean = sum / (double) numPointsInRange;
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

double MSpec2D::MeanY(MRange range, int verbosity) {
  if (CheckEmpty()) return (double) NULL;

  double sum = 0.0;
  int numPointsInRange = 0;
  for (size_t i = 0; i < yData.size(); i++ ) {
    if ( xData[i] >= range.Low() && xData[i] <= range.High() ) {
      numPointsInRange++;
      sum += yData[i];
    }
  }
  double mean = sum / (double) numPointsInRange;
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
         << colArg << i 
         << colClear << "] = ("
         << colResult << xData[i] 
         << colClear << "," 
         << colResult << yData[i] 
         << colClear << ")" << endl;
  }
  return true;
}

bool MSpec2D::Print(MRange range) {
  if (CheckEmpty()) return false;

  for (size_t i = 0; i < numData; i++) {
    if (xData[i] >= range.Low() && xData[i] <= range.High())
      cout << colVarName << name 
           << colClear << "[" 
           << colArg << i 
           << colClear << "] = ("
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

bool MSpec2D::Print(string file, MRange range, bool append) {
  if (CheckEmpty()) return false;

  ofstream outFile(file);
  outFile << "# " << name << ": " 
          << xLabel << "[" << xUnit << "]" << outSep
          << yLabel << "[" << yUnit << "]" << endl;

  for (size_t i = 0; i < numData; i++) {
    if (xData[i] >= range.Low() && xData[i] <= range.High())
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

int MSpec2D::NumPointsInRange(MRange range, int verbose) {
  int numPoints = 0;
  for (size_t i = 0; i < numData; i++) {
    if (xData[i] >= range.Low() && xData[i] <= range.High()) 
      numPoints++;
  }
  return numPoints;
}

int MSpec2D::IteratorBelowX(double value) {
  for (size_t i = 0; i < numData; i++) {
    if ( xData[i] > value ) {
      if (i == 0) return 0;
      return i-1;
    } else if ( xData[i] == value ) {
      return i;
    }
  }
  return numData;
}

int MSpec2D::IteratorAboveX(double value) {
  for (size_t i = numData-1; i >= 0; i--) {
    if ( xData[i] < value ) {
      if (i == 0) return 0;
      return i+1;
    } else if ( xData[i] == value ) {
      return i;
    }
  }
  return 0;
}