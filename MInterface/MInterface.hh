// MInterface.hh

#ifndef _M_INTERFACE
#define _M_INTERFACE

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include <sys/stat.h>

using namespace std;

string exec(const char* cmd);
string exec(const string cmd);

class MInterface {
  public: 
    MInterface();   // constructor
    ~MInterface();  // destructor

    // Main function to parse and check the passed argument array:
    bool ParseArgs(int, char**, bool debug = false);

    // Functions to add acceptable flags/arguments:
    void AddArg(const char*); // add a comment
    void AddArg(const char*, const char*, int*); // add an integer flag
    void AddArg(const char*, const char*, bool*); // add a boolean flag
    void AddArg(const char*, const char*, double*); // add a double flag
    void AddArg(const char*, const char*, string*); // add a string flag

    void AddMacro(const char*, const char*, string*); // add a macro override flag

    bool IsSet(const char*);

  private:
    // maximal sizes for flags, comments, and types:
    size_t fMaxFlagLength; 
    size_t fMaxCommentLength; 
    size_t fMaxTypeLength; 

    // vectors to store flags, comments, types and values:
    vector<string> fFlags;
    vector<string> fComments;
    vector<void*> fValues;
    vector<string> fTypes;
    vector<bool> fSet;

    // int newArgc;
    // char** newArgv;
    char** tempArgv;

    // functions
    bool FlagExists(const char*);
    vector<string> ArgsFromMacro(string, int*, char**);
    bool FileExists(const string&, const int);
    void split(const string &s, char delim, vector<string> &elems);
    vector<string> split(const string &s, char delim);

};

#endif