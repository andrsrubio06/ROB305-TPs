#ifndef Timer_h_INCLUDED
#define Timer_h_INCLUDED
#include <signal.h>
#include <time.h>
class Timer
{
protected:
	timer_t tid;
	virtual void callback() = 0;
		
public:
	Timer();
	virtual ~Timer();
	virtual void start(double duration_ms) = 0;
	void stop();

private:
	static void call_callback(int, siginfo_t* si, void*);
	
};

#endif