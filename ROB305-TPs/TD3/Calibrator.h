#ifndef Calibrator_h_INCLUDED
#define Calibrator_h_INCLUDED

#include <vector>

#include "./PeriodicTimer.h"
#include "./Looper.h"

struct coefficients {
	double a;
	double b;
};

class Calibrator 
  : public PeriodicTimer
{
private:
	double a; 
	double b; 
	std::vector<double> samples; 
	unsigned int pCounter; 

protected:
	void callback(); 

public:
	Looper* looper; 
	Calibrator(double samplingPeriod_ms, unsigned nSamples); 
	double nLoops(double duration); 

};

#endif