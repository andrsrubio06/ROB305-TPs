#ifndef CpuLoop_h_INCLUDED
#define CpuLoop_h_INCLUDED

#include "./Calibrator.h"


class CpuLoop 
  : public Looper
{
private:
	Calibrator calibrator;

public:
	CpuLoop(Calibrator& calibrator);
	void runTime(double duration_ms);
  
};

#endif