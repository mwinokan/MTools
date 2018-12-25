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

MDouble MSpecManip::ConstFitStdErr(MSpec2D spec, MRange range, int verbosity) {
  MDouble dResult(spec.name + " Const. Fit",spec.yUnit);
  double mean = spec.MeanY(range,verbosity-1);
  dResult.SetValue(mean);
  double sumSq = SumSqYBetween(spec,mean,range,verbosity-1);
  int n = spec.NumPointsInRange(range,verbosity-1);
  dResult.SetError(sqrt(sumSq/((double) n - 1.0))/(sqrt(n)));
  if (verbosity > 0) dResult.Print();
  return dResult;
}

MDouble MSpecManip::ConstFitStdDev(MSpec2D spec, MRange range, int verbosity) {
  MDouble dResult(spec.name + " Const. Fit",spec.yUnit);
  double mean = spec.MeanY(range,verbosity-1);
  dResult.SetValue(mean);
  double sumSq = SumSqYBetween(spec,mean,range,verbosity-1);
  int n = spec.NumPointsInRange(range,verbosity-1);
  dResult.SetError(sqrt(sumSq/((double) n - 1.0)));
  if (verbosity > 0) dResult.Print();
  return dResult;
}

void MSpecManip::PeakFind(MSpec2D spec, double offset, double threshold, MPoint* trig, MPoint* peak, MPoint* zero) {

  double trigT, trigV, peakT, peakV, zeroT, zeroV;

  bool trigSearch = true;
  bool peakSearch = false;
  bool zeroSearch = false;

  double bestPeakT;
  double bestPeakV = offset + threshold;

  for (size_t i = 0; i < spec.xData.size(); i++) {
    double thisTime = spec.xData[i];
    double thisVolt = spec.yData[i];

    if (trigSearch && thisVolt > offset + threshold) {
          trigT = thisTime;
          trigV = thisVolt;
          trigSearch = false;
          peakSearch = true;
          zeroSearch = true;
          // cout << thisTime << " " << thisVolt << endl;
    }

    if (peakSearch) {
        // outputfile << thisVolt << " " << bestPeakV << " " << (thisVolt > bestPeakV) << endl;
        if (thisVolt > bestPeakV) {
          bestPeakV = thisVolt;
          bestPeakT = thisTime;
        }
      }

      if (zeroSearch && bestPeakV > offset + 2.0*threshold) {
        if (thisVolt < offset + threshold) {
          zeroT = thisTime;
          zeroV = thisVolt;
          peakSearch = false;
          zeroSearch = false;
        }
      }

      if (!trigSearch && !peakSearch && !zeroSearch) {
        break;
      }

  }

  peakT = bestPeakT;
  peakV = bestPeakV;

  trig->SetX(trigT,"[time]");
  trig->SetY(trigV,"[voltage]");
  peak->SetX(peakT,"[time]");
  peak->SetY(peakV,"[voltage]");
  zero->SetX(zeroT,"[time]");
  zero->SetY(zeroV,"[voltage]");

}

void MSpecManip::TroughFind(MSpec2D spec, double offset, double threshold, MPoint* trig, MPoint* trough, MPoint* zero) {

  double trigT, trigV, troughT, troughV, zeroT, zeroV;

  bool trigSearch = true;
  bool troughSearch = false;
  bool zeroSearch = false;

  double bestTroughT;
  double bestTroughV = offset + threshold;

  for (size_t i = 0; i < spec.xData.size(); i++) {
    double thisTime = spec.xData[i];
    double thisVolt = spec.yData[i];

    if (trigSearch && thisVolt < offset - threshold) {
          trigT = thisTime;
          trigV = thisVolt;
          trigSearch = false;
          troughSearch = true;
          zeroSearch = true;
          // cout << thisTime << " " << thisVolt << endl;
    }

    if (troughSearch) {
        // outputfile << thisVolt << " " << bestTroughV << " " << (thisVolt > bestTroughV) << endl;
        if (thisVolt < bestTroughV) {
          bestTroughV = thisVolt;
          bestTroughT = thisTime;
        }
      }

      if (zeroSearch && bestTroughV > offset - 2.0*threshold) {
        if (thisVolt > offset + threshold) {
          zeroT = thisTime;
          zeroV = thisVolt;
          troughSearch = false;
          zeroSearch = false;
        }
      }

      if (!trigSearch && !troughSearch && !zeroSearch) {
        break;
      }

  }

  troughT = bestTroughT;
  troughV = bestTroughV;

  trig->SetX(trigT,"[time]");
  trig->SetY(trigV,"[voltage]");
  trough->SetX(troughT,"[time]");
  trough->SetY(troughV,"[voltage]");
  zero->SetX(zeroT,"[time]");
  zero->SetY(zeroV,"[voltage]");

}

double MSpecManip::Integrate(MSpec2D spec, MRange range, int verbosity) {

  // find iteration range
  int start = spec.IteratorBelowX(range.Low());
  int stop = spec.IteratorAboveX(range.High());

  double w, h1, h2;
  double sum = 0.0;

  if (start == stop) return sum;
  
  for (size_t i = start; i < stop; i++) {
    // if start interpolate
    if (i == start) {
      w = spec.xData[start+1] - range.Low();
      h2 = spec.yData[start+1];
      h1 = spec.yData[start+1] - w*(spec.yData[start+1]-spec.yData[start])/(spec.xData[start+1]-spec.xData[start]);
    } else if (i == stop-1) {
      w = spec.xData[stop] - range.High();
      h1 = spec.yData[stop-1];
      h2 = spec.yData[stop-1] + w*(spec.yData[stop]-spec.yData[stop-1])/(spec.xData[stop]-spec.xData[stop-1]);
    } else {
      w = spec.xData[i+1] - spec.xData[i];
      h1 = spec.yData[i];
      h1 = spec.yData[i+1];
    }
    sum += w * (h1 + h2) / 2.0; 
  }
  if (verbosity > 0) 
    cout << colFunc << "Integrate" 
         << colClear << "(" 
         << colVarName << spec.name 
         << colClear << "," 
         << colArg << range.Low() 
         << colClear << ":"
         << colArg << range.High() 
         << colClear << ") = " 
         << colResult << sum 
         << colClear << endl;
  return sum;
}

double MSpecManip::Integrate(MSpec2D spec, int verbosity) {

  // find iteration range
  int start = 0;
  int stop = spec.numData;

  double w, h1, h2;
  double sum = 0.0;

  if (start == stop) return sum;

  for (size_t i = start; i < stop; i++) {
    w = spec.xData[i+1] - spec.xData[i];
    h1 = spec.yData[i];
    h1 = spec.yData[i+1];
    sum += w * (h1 + h2) / 2.0; 
  }
  if (verbosity > 0) 
    cout << colFunc << "Integrate" 
         << colClear << "(" 
         << colVarName << spec.name 
         << colClear << ") = " 
         << colResult << sum 
         << colClear << endl;
  return sum;
}

double MSpecManip::Integrate(MSpec2D spec, double offset, int verbosity) {

  // find iteration range
  int start = 0;
  int stop = spec.numData;

  double w, h1, h2;
  double sum = 0.0;

  if (start == stop) return sum;

  for (size_t i = start; i < stop; i++) {
    w = spec.xData[i+1] - spec.xData[i];
    h1 = spec.yData[i];
    h1 = spec.yData[i+1];
    sum += w * (h1 + h2) / 2.0 - w * offset; 
  }
  if (verbosity > 0) 
    cout << colFunc << "Integrate" 
         << colClear << "(" 
         << colVarName << spec.name 
         << colClear << ") = " 
         << colResult << sum 
         << colClear << endl;
  return sum;
}

double MSpecManip::Integrate(MSpec2D spec, double offset, MRange range, int verbosity) {

  // find iteration range
  int start = spec.IteratorBelowX(range.Low());
  int stop = spec.IteratorAboveX(range.High());

  double w, h1, h2;
  double sum = 0.0;

  if (start == stop) return sum;

  for (size_t i = start; i < stop; i++) {
    // if start interpolate
    if (i == start) {
      w = spec.xData[start+1] - range.Low();
      h2 = spec.yData[start+1];
      h1 = spec.yData[start+1] - w*(spec.yData[start+1]-spec.yData[start])/(spec.xData[start+1]-spec.xData[start]);
    } else if (i == stop-1) {
      w = spec.xData[stop] - range.High();
      h1 = spec.yData[stop-1];
      h2 = spec.yData[stop-1] + w*(spec.yData[stop]-spec.yData[stop-1])/(spec.xData[stop]-spec.xData[stop-1]);
    } else {
      w = spec.xData[i+1] - spec.xData[i];
      h1 = spec.yData[i];
      h1 = spec.yData[i+1];
    }
    sum += w * (h1 + h2) / 2.0 - w * offset; 
  }
  if (verbosity > 0) 
    cout << colFunc << "Integrate" 
         << colClear << "(" 
         << colVarName << spec.name 
         << colClear << "," 
         << colArg << range.Low() 
         << colClear << ":"
         << colArg << range.High() 
         << colClear << ") = " 
         << colResult << sum 
         << colClear << endl;
  return sum;
}