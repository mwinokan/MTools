// MSpecManip.cc

#include "MSpecManip.hh"

MSpec2D MSpecManip::Add(MSpec2D spec1, MSpec2D spec2, double scale1, double scale2) {

  if (spec1.CheckEmpty()) return (MSpec2D) NULL;
  if (spec2.CheckEmpty()) return (MSpec2D) NULL;

  vector<double> energy_1 = spec1.xData;
  vector<double> value_1 = spec1.yData;  
  vector<double> energy_2 = spec2.xData;
  vector<double> value_2 = spec2.yData;

  for (size_t i = 0; i < value_1.size(); i++) value_1[i] *= scale1; 
  for (size_t i = 0; i < value_2.size(); i++) value_2[i] *= scale2; 

  bool done = false;

  vector<double> energies;
  vector<bool> hasData_1;
  vector<bool> hasData_2;
  vector<int> location_1;
  vector<int> location_2;
  vector<double> summed;

  if (energy_1.front() <= energy_2.front()) energies.push_back(energy_1.front());
  else energies.push_back(energy_2.front());
  
  double thisEnergy = energies.front();
  int i = 0;
  int j = 0;
  int k = 0;
  bool last_1 = false;
  bool last_2 = false;

  while (!done) {

    // check which data has this energy
    hasData_1.push_back(false);
    location_1.push_back(-1);
    for (int n = 0; n < energy_1.size(); n++) {
      if (thisEnergy == energy_1[n]) {
        hasData_1[i] = true;
        location_1[i] = n;
        if (n == energy_1.size() - 1) last_1 = true;
      }
    }
    hasData_2.push_back(false);
    location_2.push_back(-1);
    for (int n = 0; n < energy_2.size(); n++) {
      if (thisEnergy == energy_2[n]) {
        hasData_2[i] = true; 
        location_2[i] = n;
        if (n == energy_2.size() - 1) last_2 = true;
      }
    }

    // look for next lowest energy
    if (!last_1 && !last_2) {
      if (energy_1[j+1] < energy_2[k+1]) {
        energies.push_back(energy_1[j+1]);
        j++;
      } else if (energy_1[j+1] == energy_2[k+1]) {
        energies.push_back(energy_1[j+1]);
        j++;
        k++;
      } else {
        energies.push_back(energy_2[k+1]);
        k++;
      }
    } else if (last_1 && last_2) {
      done = true;
    } else if (last_1 && !last_2) {
      energies.push_back(energy_2[k+1]);
      k++;
    } else if (!last_1 && last_2) {
      energies.push_back(energy_1[j+1]);
      j++;
    }

    i++;
    thisEnergy = energies[i];
  }


  for (int i = 0; i < energies.size(); i++) {

    if (hasData_1[i] && hasData_2[i]) {

      summed.push_back(value_1[location_1[i]]+value_2[location_2[i]]);
    
    } else if (hasData_1[i] && !hasData_2[i]) {

      double target = energy_1[location_1[i]];

      if (target < energy_2[0]) {
        summed.push_back(value_1[location_1[i]]);
      } else if (target > energy_2[energy_2.size()-1]) {
        summed.push_back(value_1[location_1[i]]);
      } else {

        double thisEnergy = energy_2[0];
        double nextEnergy;

        done = false;
        int j = 0;
        while (!done) {
          if (target < energy_2[j]) {
            thisEnergy = energy_2[j-1];
            nextEnergy = energy_2[j];
            double intraVal = value_2[j-1] + (value_2[j] - value_2[j-1])*(target - thisEnergy)/(nextEnergy - thisEnergy);
            summed.push_back(value_1[location_1[i]]+intraVal);
            done = true;
          }
          j++;
        }
      }

    } else if (hasData_2[i] && !hasData_1[i]) {

      double target = energy_2[location_2[i]];

      if (target < energy_1[0]) {
        summed.push_back(value_2[location_2[i]]);
      } else if (target > energy_1[energy_1.size()-1]) {
        summed.push_back(value_2[location_2[i]]);
      } else {

        double thisEnergy = energy_1[0];
        double nextEnergy;

        done = false;
        int j = 0;
        while (!done) {
          if (target < energy_1[j]) {
            thisEnergy = energy_1[j-1];
            nextEnergy = energy_1[j];
            double intraVal = value_1[j-1] + (value_1[j] - value_1[j-1])*(target - thisEnergy)/(nextEnergy - thisEnergy);
            summed.push_back(value_2[location_2[i]]+intraVal);
            done = true;
          }
          j++;
        }
      }

    } else {
      summed.push_back(-1);
    }
  }

  MSpec2D sAdded("sAdded");
  for (size_t i = 0; i < energies.size(); i++) sAdded.Add(energies[i],summed[i]);
  return sAdded;
}

MSpec2D MSpecManip::Sub(MSpec2D spec1, MSpec2D spec2, double scale1, double scale2) {
  MSpec2D sSubbed("sSubbed");
  sSubbed = Add(spec1, spec2, scale1, -scale2);
  return sSubbed;
}

double MSpecManip::SumXBetween(MSpec2D spec, double reference, int verbosity) {
  if (spec.CheckEmpty()) return (double) NULL;
  double sum = 0.0;
  for (size_t i = 0; i < spec.xData.size(); i++) sum += spec.xData[i] - reference;
  if (verbosity > 0) 
    cout << colFunc << "SumXBetween" << colClear << "(" << colVarName << spec.name 
         << colClear << "," << reference <<  ") = " << colResult << sum << colClear << endl;
  return sum;
}

double MSpecManip::SumXBetween(MSpec2D spec, double reference, MRange range, int verbosity) {
  if (spec.CheckEmpty()) return (double) NULL;
  double sum = 0.0;
  for (size_t i = 0; i < spec.xData.size(); i++)
    if (spec.xData[i] >= range.Low() && spec.xData[i] <= range.High())
      sum += spec.xData[i] - reference;
  if (verbosity > 0) 
    cout << colFunc << "SumXBetween" << colClear << "(" << colVarName << spec.name 
         << colClear << "," << reference <<  ") = " << colResult << sum << colClear << endl;
  return sum;
}

double MSpecManip::SumSqXBetween(MSpec2D spec, double reference, int verbosity) {
  if (spec.CheckEmpty()) return (double) NULL;
  double sum = 0.0;
  for (size_t i = 0; i < spec.xData.size(); i++) sum += pow(spec.xData[i] - reference,2);
  if (verbosity > 0) 
    cout << colFunc << "SumSqXBetween" << colClear << "(" << colVarName << spec.name 
         << colClear << "," << reference <<  ") = " << colResult << sum << colClear << endl;
  return sum;
}

double MSpecManip::SumSqXBetween(MSpec2D spec, double reference, MRange range, int verbosity) {
  if (spec.CheckEmpty()) return (double) NULL;
  double sum = 0.0;
  for (size_t i = 0; i < spec.xData.size(); i++) 
    if (spec.xData[i] >= range.Low() && spec.xData[i] <= range.High())
      sum += pow(spec.xData[i] - reference,2);
  if (verbosity > 0) 
    cout << colFunc << "SumSqXBetween" << colClear << "(" << colVarName << spec.name 
         << colClear << "," << reference <<  ") = " << colResult << sum << colClear << endl;
  return sum;
}

double MSpecManip::SumYBetween(MSpec2D spec, double reference, int verbosity) {
  if (spec.CheckEmpty()) return (double) NULL;
  double sum = 0.0;
  for (size_t i = 0; i < spec.yData.size(); i++) sum += spec.yData[i] - reference;
  if (verbosity > 0) 
    cout << colFunc << "SumYBetween" << colClear << "(" << colVarName << spec.name 
         << colClear << "," << reference <<  ") = " << colResult << sum << colClear << endl;
  return sum;
}

double MSpecManip::SumYBetween(MSpec2D spec, double reference, MRange range, int verbosity) {
  if (spec.CheckEmpty()) return (double) NULL;
  double sum = 0.0;
  for (size_t i = 0; i < spec.yData.size(); i++) 
    if (spec.xData[i] >= range.Low() && spec.xData[i] <= range.High())
      sum += spec.yData[i] - reference;
  if (verbosity > 0) 
    cout << colFunc << "SumYBetween" << colClear << "(" << colVarName << spec.name 
         << colClear << "," << reference <<  ") = " << colResult << sum << colClear << endl;
  return sum;
}

double MSpecManip::SumSqYBetween(MSpec2D spec, double reference, int verbosity) {
  if (spec.CheckEmpty()) return (double) NULL;
  double sum = 0.0;
  for (size_t i = 0; i < spec.yData.size(); i++) sum += pow(spec.yData[i] - reference,2);
  if (verbosity > 0) 
    cout << colFunc << "SumSqYBetween" << colClear << "(" << colVarName << spec.name 
         << colClear << "," << reference <<  ") = " << colResult << sum << colClear << endl;
  return sum;
}

double MSpecManip::SumSqYBetween(MSpec2D spec, double reference, MRange range, int verbosity) {
  if (spec.CheckEmpty()) return (double) NULL;
  double sum = 0.0;
  for (size_t i = 0; i < spec.yData.size(); i++) 
    if (spec.xData[i] >= range.Low() && spec.xData[i] <= range.High())
      sum += pow(spec.yData[i] - reference,2);
  if (verbosity > 0) 
    cout << colFunc << "SumSqYBetween" << colClear << "(" << colVarName << spec.name 
         << colClear << "," << reference <<  ") = " << colResult << sum << colClear << endl;
  return sum;
}

double MSpecManip::CoeffDetermination(MSpec2D refSpec, MSpec2D fitSpec, int verbosity) {
  MSpec2D sSubbed("sSubbed");
  sSubbed = Sub(refSpec,fitSpec);
  double SSresiduals = SumSqYBetween(sSubbed,0.0,verbosity-1);
  double SStotal = SumSqYBetween(refSpec,refSpec.MeanY(),verbosity-1);
  double coeffDetermination = 1.0 - SSresiduals/SStotal;
  if (verbosity > 0) 
    cout << colFunc << "CoeffDetermination" << colClear << "(" << colVarName 
         << refSpec.name << colClear << "," << colVarName << fitSpec.name << colClear
         <<  ") = " << colResult << coeffDetermination << colClear << endl;
  return coeffDetermination;
}

double MSpecManip::CoeffDetermination(MSpec2D refSpec, MSpec2D fitSpec, MRange range, int verbosity) {
  MSpec2D sSubbed("sSubbed");
  sSubbed = Sub(refSpec,fitSpec);
  double SSresiduals = SumSqYBetween(sSubbed,0.0,range,verbosity-1);
  double SStotal = SumSqYBetween(refSpec,refSpec.MeanY(),range,verbosity-1);
  double coeffDetermination = 1.0 - SSresiduals/SStotal;
  if (verbosity > 0) 
    cout << colFunc << "CoeffDetermination" << colClear << "(" << colVarName 
         << refSpec.name << colClear << "," << colVarName << fitSpec.name << colClear
         <<  ") = " << colResult << coeffDetermination << colClear << endl;
  return coeffDetermination;
}