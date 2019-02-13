// MUnits.hh

#ifndef _M_UNITS
#define _M_UNITS

#include <string>

using namespace std;

extern const double cG;

class MUnit {
  public: 
    // Construction & Destruction
    MUnit() {};
    MUnit(MUnit &mUnit);
    MUnit(string type, string name, string longName = "");
    MUnit(string type, string name, double conversionSI);
    MUnit(string type, string name, string longName, double conversionSI);
    ~MUnit() {};

    // Getters:
    string Name() { return name; };
    string LongName() { return longName; };
    string Type() { return type; };
    bool IsSI() { return isSI; };
    double ConversionSI() { return conversionSI; };

  private: 
    string name;
    string longName;
    string type;
    bool isSI;
    double conversionSI;
};

class MUnits {
  public:
    // Construction & Destruction
    MUnits();
    ~MUnits() {};

    // Getters:
    MUnit Time() { return uTime; };
    MUnit Length() { return uLength; };
    MUnit Mass() { return uMass; };
    MUnit Speed() { return uSpeed; };
    MUnit SpeedSq() { return uSpeedSq; };

    // Setters:
    void SetLengthUnit(MUnit mUnit) { uLength = mUnit; };
    void SetMassUnit(MUnit mUnit) { uMass = mUnit; };
    void SetSpeedUnit(MUnit mUnit) { uSpeed = mUnit; };
    void SetSpeedSqUnit(MUnit mUnit) { uSpeedSq = mUnit; };

    // Conversion
    double ConvertSI(MUnit uFrom); // Returns conversion to SI unit
    double Convert(MUnit uFrom); // Returns conversion to current units
    double Convert(MUnit uFrom, MUnit uTo); // Returns conversion to given unit

    // SI Defaults:
    MUnit Metre;
    MUnit Second;
    MUnit KiloGram;
    MUnit MetresPerSecond;
    MUnit MetresSquaredPerSecondSquared;

    // Derived Units:
    MUnit Minute;
    MUnit Hour;
    MUnit Day;
    MUnit Year;
    MUnit AstronomicalUnits;
    MUnit Parsec;
    MUnit KiloParsec;
    MUnit SolarMass;
    MUnit AstronomicalUnitsPerSecond;
    MUnit AstronomicalUnitsSquaredPerSecondSquared;

    // Null:
    MUnit Null;

  private:
    // Selected Units (SI Default);
    MUnit uTime;
    MUnit uLength;
    MUnit uMass;
    MUnit uSpeed;
    MUnit uSpeedSq;
};

extern MUnits mUnits;

#endif