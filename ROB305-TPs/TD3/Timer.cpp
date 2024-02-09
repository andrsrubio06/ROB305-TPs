#include <iostream>
#include "Timer.h"

//took from TD1-a
timespec timespec_from_ms(double time_ms)
{
	timespec time;
	time.tv_sec = (int)time_ms / 1000;
	time.tv_nsec = (time_ms * 1000 * 1000 - int(time_ms) * 1000 * 1000);
	return time;
}

Timer::Timer()
{
	struct sigaction sa;
	sa.sa_flags	= SA_SIGINFO;
	sa.sa_sigaction = call_callback;

	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN, &sa, NULL);

	struct sigevent sev;
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = this;

	timer_create(CLOCK_REALTIME, &sev, &tid);
	
}

Timer::~Timer()
{
	timer_delete(tid);
}

void Timer::call_callback(int, siginfo_t *si, void *)
{
	Timer* timer = (Timer*) si->si_value.sival_ptr;
	timer->callback();

}

void Timer::stop()
{	
	itimerspec its;

	its.it_value.tv_sec = 0;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = 0;  

	timer_settime(tid, 0, &its, NULL);
}

void Timer::start(double duration_ms)
{
    itimerspec its;

    its.it_value = timespec_from_ms(duration_ms);
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    
    timer_settime(tid, 0, &its, NULL);
}