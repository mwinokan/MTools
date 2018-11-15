// MInterface

#include "MInterface.hh"
#include "MColours.hh"

using namespace std;

// Constructor:
MInterface::MInterface() {
  fMaxFlagLength = 0;
  fMaxCommentLength = 0;
  fMaxTypeLength = 0;
}

// Destructor
MInterface::~MInterface() {
}

bool MInterface::ParseArgs(int argc, char** argv, bool debug) {

  // if no arguments:
  if ( argc == 1 ) {

    // write out all comments not associated to flags:
    for(size_t i = 0; i < fFlags.size(); i++) {
      if(fTypes[i].empty()) cout<<fComments[i]<< endl << endl;
    }

    // write out usage:
    cout << "Usage for " << colFile << argv[0] << colClear << ":" << endl;

    // write out usage:
    for(size_t i = 0; i < fFlags.size(); i++) {

      // for all added flags:
      if (fTypes[i] == "bool") {
        cout << "[ "
             << colVarName << setw(fMaxFlagLength) << left
             << fFlags[i] << colClear
             << colVarType
             << "" << colClear
             << setw(fMaxTypeLength + 3) << ""
             << " : "
             << setw(fMaxCommentLength) << left
             << fComments[i] << " ]" << endl;
      } else if (!fTypes[i].empty())
        cout << "[ "
             << colVarName << setw(fMaxFlagLength) << left
             << fFlags[i] << colClear << " <"
             << colVarType
             << fTypes[i] << colClear << ">" 
             << setw(fMaxTypeLength - fTypes[i].length()) << ""
             << " : "
             << setw(fMaxCommentLength) << left
             << fComments[i] << " ]" << endl;
    }

    cout << endl;
    return true;
  }

  // if at this point then arguments have been passed:

  size_t a,f;

  // load arguments into string vector:
  vector<string> argStrings;
  argStrings.reserve(argc);
  for (a = 0; a < (size_t) argc; a++) {
    argStrings.push_back(argv[a]);
  }

  bool done = false;

  // first look for a macro override:
  for (a = 1; a < (size_t) argc; a++) {
    for (f = 0; f < fFlags.size(); f++) {
      if (argv[a] == fFlags[f] && fTypes[f] == "macro") {
        if (a+1 >= (size_t) argc) {
          cout << colError 
               << "ERROR: flag " 
               << colVarName << fFlags[f] 
               << colError << " requires an argument." 
               << colClear << endl;
          return false;
        }
        if (!FileExists(argv[a+1],0)) {
          cout << colError 
               << "ERROR: macro " 
               << colVarName << argv[a+1]
               << colError << " cannot be found." 
               << colClear << endl;
          return false;
        }
        vector<string> newArgs = ArgsFromMacro(argv[a+1],&argc,argv);
        argStrings.clear();
        argStrings = newArgs;
        done = true;
        break;
      }
    }
    if (done) break;
  }

  // loop over all given arguments:
  for (a = 1; a < argStrings.size(); a++) {
    if (debug) cout << argStrings[a] << " " << argStrings[a+1] << endl;
    // loop over all known flags:
    for (f = 0; f < fFlags.size(); f++) {

      if (argStrings[a] == fFlags[f]) { // if this argument is this flag


        if (fTypes[f] == "bool") { // if this flag is a boolean type
          * ((bool*) fValues[f]) = true; // set the pointer to the boolean as true
          fSet[f] = true; // this flag has now been set
          break; // flag for this argument has been found
        } else if (a+1 >= argStrings.size()) { // if not bool and no more args
          cout << colError 
               << "ERROR: flag " 
               << colVarName << fFlags[f] 
               << colError << " requires an argument." 
               << colClear << endl;
          return false;
        } else if (fTypes[f] == "int") { // if this flag is of integer type
          * ((int*) fValues[f]) = atoi(argStrings[a+1].c_str()); // return pointer to next argument
          a++; // skip next argument
          fSet[f] = true; // this flag has now been set
          break; // flag for this argument has been found
        } else if (fTypes[f] == "double") { // if this flag is of integer type
          * ((double*) fValues[f]) = atof(argStrings[a+1].c_str()); // return pointer to next argument
          a++; // skip next argument
          fSet[f] = true; // this flag has now been set
          break; // flag for this argument has been found
        } else if(fTypes[f] == "string") {
          *((string*) fValues[f]) = argStrings[a+1]; // pointer to next argument
          if (debug) cout << "returned: " << argStrings[a+1] << endl;
          a+=2;
          
          while(a < (size_t) argc) { //as long as there are arguments left
            if(argStrings[a].at(0) != '-') { // if no flag is found
              // append to the returned string
              ( * ((string*) fValues[f])).append(" ");
              ( * ((string*) fValues[f])).append(argStrings[a]);
              if (debug) cout << "appended: " << argStrings[a] << endl;
              a++;
            } else {
              fSet[f] = true; // this flag has now been set
              break;
            }
          }
          a--;
        } else if(fTypes[f] == "macro") {
          *((string*) fValues[f]) = argStrings[a+1]; // pointer to next argument
          a++;
          fSet[f] = true; // this flag has now been set
          break;
        }
        if(f == fFlags.size()) { // no matching flag was found
          cout << colError << "ERROR: flag ["<< a <<"]" 
               << colVarName << argStrings[a] 
               << colError << " unknown" 
               << colClear << endl;
          return false;
        }
      }
    }
  }

  return true;
}

// add a comment:
void MInterface::AddArg(const char* comment) {

  // push_back on required vectors
  fComments.push_back(string(comment));

  // null push_back on unneeded vectors:
  fFlags.push_back(string());
  fValues.push_back((void*) NULL);
  fTypes.push_back(string());
  fSet.push_back((bool) NULL);
}

// add an integer flag:
void MInterface::AddArg(const char* flag, const char* comment, int* value) {
  if (FlagExists(flag)) return;
  char* type = (char*) "int";

  // update maximum lengths if needed:
  if(strlen(comment) > fMaxCommentLength) fMaxCommentLength = strlen(comment);
  if(strlen(flag) > fMaxFlagLength) fMaxFlagLength = strlen(flag);
  if(strlen(type) > fMaxTypeLength) fMaxTypeLength = strlen(type);

  // push_back on required vectors
  fComments.push_back(string(comment));
  fFlags.push_back(string(flag));
  fTypes.push_back(string(type));
  fValues.push_back((void*) value);
  fSet.push_back(false);
}

// add a boolean flag:
void MInterface::AddArg(const char* flag, const char* comment, bool* value) {
  if (FlagExists(flag)) return;
  char* type = (char*) "bool";

  // update maximum lengths if needed:
  if(strlen(comment) > fMaxCommentLength) fMaxCommentLength = strlen(comment);
  if(strlen(flag) > fMaxFlagLength) fMaxFlagLength = strlen(flag);
  // if(strlen(type) > fMaxTypeLength) fMaxTypeLength = strlen(type);

  // push_back on required vectors
  fComments.push_back(string(comment));
  fFlags.push_back(string(flag));
  fTypes.push_back(string(type));
  fValues.push_back((void*) value);
  fSet.push_back(false);
}

// add a double flag:
void MInterface::AddArg(const char* flag, const char* comment, double* value) {
  if (FlagExists(flag)) return;
  char* type = (char*) "double";

  // update maximum lengths if needed:
  if(strlen(comment) > fMaxCommentLength) fMaxCommentLength = strlen(comment);
  if(strlen(flag) > fMaxFlagLength) fMaxFlagLength = strlen(flag);
  if(strlen(type) > fMaxTypeLength) fMaxTypeLength = strlen(type);

  // push_back on required vectors
  fComments.push_back(string(comment));
  fFlags.push_back(string(flag));
  fTypes.push_back(string(type));
  fValues.push_back((void*) value);
  fSet.push_back(false);
}

// add a string flag:
void MInterface::AddArg(const char* flag, const char* comment, string* value) {
  if (FlagExists(flag)) return;
  char* type = (char*) "string";

  // update maximum lengths if needed:
  if(strlen(comment) > fMaxCommentLength) fMaxCommentLength = strlen(comment);
  if(strlen(flag) > fMaxFlagLength) fMaxFlagLength = strlen(flag);
  if(strlen(type) > fMaxTypeLength) fMaxTypeLength = strlen(type);

  // push_back on required vectors
  fComments.push_back(string(comment));
  fFlags.push_back(string(flag));
  fTypes.push_back(string(type));
  fValues.push_back((void*) value);
  fSet.push_back(false);
}

// add a macro flag:
void MInterface::AddMacro(const char* flag, const char* comment, string* value) {
  if (FlagExists(flag)) return;
  char* type = (char*) "macro";

  // update maximum lengths if needed:
  if(strlen(comment) > fMaxCommentLength) fMaxCommentLength = strlen(comment);
  if(strlen(flag) > fMaxFlagLength) fMaxFlagLength = strlen(flag);
  if(strlen(type) > fMaxTypeLength) fMaxTypeLength = strlen(type);

  // push_back on required vectors
  fComments.push_back(string(comment));
  fFlags.push_back(string(flag));
  fTypes.push_back(string(type));
  fValues.push_back((void*) value);
  fSet.push_back(false);
}

bool MInterface::FlagExists(const char* flag) {
  //check if this flag already exists
  for(size_t i = 0; i < fFlags.size(); i++) {
    if(flag == fFlags[i]) {
      cout << colError 
           << "ERROR: flag " << flag << " already exists " 
           << colClear << endl;
      return true;
    }
  }
  return false;
}

bool MInterface::IsSet(const char* flag) {
  for (size_t f = 0; f < fFlags.size(); f++) {
    cout << fFlags[f] << " : " << fSet[f] << endl;
  }

  bool found = false;

  for (size_t i = 0; i < fFlags.size(); i++) {
    return fSet[i];
  }

  return (bool) NULL;
}

vector<string> MInterface::ArgsFromMacro(string macro, int* argc, char** argv) {

  ifstream macroFile(macro);
  string line;

  int newArgc = 1;

  vector<string> allWords;

  while (getline(macroFile,line)) {
    if (line.at(line.find_first_not_of(' ')) == '#') continue;
    vector<string> words = split(line,' ');
    for (size_t i = 0; i < words.size(); i++) {
      newArgc++;
      allWords.push_back(words[i]);
    }
  }

  vector<string> newArgs;
  newArgs.reserve(newArgc);

  *argc = newArgc;

  newArgs.push_back(argv[0]);

  for (auto& s: allWords) {
    newArgs.push_back(s);
  }

  return newArgs;
}

void MInterface::split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> MInterface::split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

bool MInterface::FileExists(const string& name, const int verbose) {
  struct stat buffer;
  if (stat (name.c_str(), &buffer) == 0) {
    if (verbose > 1) { 
      cout << "\033[32m" 
           << "File accessible. (" 
           << name.c_str() << ")" 
           << "\033[0m" << endl;
    }
    return true;
  } else {
    if (verbose > 0) { 
      cout << "\033[31m" 
           << "ERROR: File inaccessible. (" 
           << name.c_str() << ")" 
           << "\033[0m" << endl;
    }
    return false;
  }
}