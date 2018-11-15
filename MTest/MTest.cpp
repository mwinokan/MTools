// MTest

#include <iostream>

#include "MInterface.hh"

using namespace std;

int main(int argc, char** argv) {

  cout << "\n \033[1m >> This is MTest << \033[0m" << endl << endl;

  MInterface mInterface;

  string testMacro = "test.mac";
  mInterface.AddMacro("-m", "macro override", &testMacro);
  
  int testInt = 0;
  mInterface.AddArg("-i", "test integer", &testInt);
  bool testBool = false;
  mInterface.AddArg("-b", "test bool (default = false)", &testBool);
  double testDouble = 0.0;
  mInterface.AddArg("-d", "test double", &testDouble);
  string testString = "";
  mInterface.AddArg("-s", "test string", &testString);
  
  if (mInterface.ParseArgs(argc, argv)) {
    if (argc == 1) return 0;
    cout << "can now run " << argv[0] << " with: " << endl;
    cout << "test integer = " << testInt << endl;
    cout << "test double = " << testDouble << endl;
    cout << "test bool = " << testBool << endl;
    cout << "test string = " << testString << endl;
  } else {
    cout << "cannot run " << argv[0] << "!" << endl;
    return 0;
  }
  
}