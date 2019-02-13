// MUnits.cc

#include "MUnits.hh"
#include "MColours.hh"

#include <cmath>
#include <iostream>

using namespace std;

extern const double cG = 6.67408e11;

MUnits::MUnits() : 
  Metre(),
  Second(),
  KiloGram(),
  MetresPerSecond(),
  MetresSquaredPerSecondSquared(),
  Minute(),
  Hour(),
  Day(),
  Year(),
  AstronomicalUnits(),
  Parsec(),
  KiloParsec(),
  SolarMass(),
  AstronomicalUnitsPerSecond(),
  AstronomicalUnitsSquaredPerSecondSquared(),
  uLength(), 
  uMass(), 
  uSpeed(), 
  uSpeedSq()
{
  Metre = MUnit("length","m","metre",1.0),
  Second = MUnit("time","s","second",1.0),
  KiloGram = MUnit("mass","kg","kilogram",1.0),
  MetresPerSecond = MUnit("speed","m/s","metres per second",1.0),
  MetresSquaredPerSecondSquared = MUnit("speed^2","(m/s)^2","metres squared per second squared",1.0),
  Minute = MUnit("time","m","minute",60),
  Hour = MUnit("time","h","hour",3600),
  Day = MUnit("time","d","day",86400),
  Year = MUnit("time","y","year",31557600),
  AstronomicalUnits = MUnit("length","AU","Astronomical Units",1.496e11),
  Parsec = MUnit("length","pc","parsec",3.0857e16),
  KiloParsec = MUnit("length","kpc","kiloparsec",3.0857e19),
  SolarMass = MUnit("mass","M_sun","Solar Mass",1.989e30),
  AstronomicalUnitsPerSecond = MUnit("speed","AU/s","Astronomical Units per second",1.496e11),
  AstronomicalUnitsSquaredPerSecondSquared = MUnit("speed^2","(AU/s)^2","Astronomical Units squared per second squared",pow(1.496e11,2)),

  uLength = MUnit(Metre);
  uTime = MUnit(Second);
  uMass = MUnit(KiloGram);
  uSpeed = MUnit(MetresPerSecond);
  uSpeedSq = MUnit(MetresSquaredPerSecondSquared);
}

double MUnits::ConvertSI(MUnit uFrom) {
  return uFrom.ConversionSI();
}

double MUnits::Convert(MUnit uFrom) {
  MUnit uTo;
  if (uFrom.Type() == "length") uTo = uLength;
  else if (uFrom.Type() == "time") uTo = uTime;
  else if (uFrom.Type() == "mass") uTo = uMass;
  else if (uFrom.Type() == "speed") uTo = uSpeed;
  else if (uFrom.Type() == "speed^2") uTo = uSpeedSq;
  else {
    cout << colError << "ERROR: Unknown unit type: " 
         << uFrom.Type() << colClear << endl;
    return 0.0;
  }
  return Convert(uFrom,uTo);
}

double MUnits::Convert(MUnit uFrom, MUnit uTo) {
  if (uFrom.Type() != uTo.Type()) {
    cout << colError << "ERROR: Units incompatible: " 
      << uFrom.Name() << " (" << uFrom.Type() << ") to "
      << uTo.Name() << " (" << uTo.Type() << ")!" << colClear << endl;
    return 0.0;
  }
  double ratio = uTo.ConversionSI() / uFrom.ConversionSI();
  return ratio;
}

MUnit::MUnit(MUnit &mUnit) {
  name = mUnit.Name();
  longName = mUnit.LongName();
  type = mUnit.Type();
  isSI = mUnit.IsSI();
  conversionSI = mUnit.ConversionSI();
}

MUnit::MUnit(string t, string n, string lN) {
  name = n;
  longName = lN;
  type = t;
}

MUnit::MUnit(string t, string n, double cSI) {
  name = n;
  longName = "";
  type = t;
  conversionSI = cSI;
  if (conversionSI == 1.0) isSI = true;
  else isSI = false;
}

MUnit::MUnit(string t, string n, string lN, double cSI) {
  name = n;
  longName = lN;
  type = t;
  conversionSI = cSI;
  if (conversionSI == 1.0) isSI = true;
  else isSI = false;
}