#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

timespec timespec_from_ms(double time_ms)
{
	timespec time;
	time.tv_sec = (int)time_ms / 1000;
	time.tv_nsec = (time_ms * 1000 * 1000 - int(time_ms) * 1000 * 1000);
	return time;
}

double timespec_to_ms(const timespec& time_ts)
{
	double time_ms = 0;
	time_ms = time_ts.tv_sec * 1000 + time_ts.tv_nsec / 1000000;
	return time_ms;	
}

timespec timespec_now()
{
	timespec time_now;
	clock_gettime(CLOCK_REALTIME, &time_now);
	return time_now;
}

timespec timespec_negate(const timespec& time_ts)
{
	timespec time;
	time.tv_sec = -time_ts.tv_sec;
	time.tv_nsec = -time_ts.tv_nsec;
	return time;
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts)
{
	timespec time;
	time.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
	time.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
	return time;
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts)
{
	timespec time;
	time.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;
	time.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec;
	return time;
}

timespec timespec_wait(const timespec& delay_ts)
{
	nanosleep(&delay_ts, NULL);
	return delay_ts;
}

timespec operator-(const timespec& time_ts)
{
	timespec negative;
	negative.tv_sec = -time_ts.tv_sec;
	negative.tv_nsec = -time_ts.tv_nsec;
	return negative;
}

timespec operator+(const timespec& time1_ts, const timespec& time2_ts)
{
	timespec time;
	time.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
	time.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
	return time;
}

timespec operator-(const timespec& time1_ts, const timespec& time2_ts)
{
	timespec time;
	time.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;
	time.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec;
	return time;
}

timespec operator+=(const timespec& time_ts, const timespec& delay_ts)
{
	timespec time;
	time.tv_sec = time_ts.tv_sec + delay_ts.tv_sec;
	time.tv_nsec = time_ts.tv_nsec + delay_ts.tv_nsec;
	return time;
}

timespec operator-=(const timespec& time_ts, const timespec& delay_ts)
{
	timespec time;
	time.tv_sec = time_ts.tv_sec - delay_ts.tv_sec;
	time.tv_nsec = time_ts.tv_nsec - delay_ts.tv_nsec;
	return time;
}

bool operator==(const timespec& time1_ts, const timespec& time2_ts)
{
	bool flag = false;
	if ((time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec == time2_ts.tv_nsec))
	{
		flag = true;
	}
	return flag;
}

bool operator!=(const timespec& time1_ts, const timespec& time2_ts)
{
	bool flag = true;
	if ((time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec == time2_ts.tv_nsec))
	{
		flag = false;
	}
	return flag;
}

bool operator<(const timespec& time1_ts, const timespec& time2_ts)
{
	bool flag = true;
	if (time1_ts.tv_sec > time2_ts.tv_sec)
	{
		flag = false;
	}
	else if (time1_ts.tv_sec == time2_ts.tv_sec)
	{
		if (time1_ts.tv_nsec >= time2_ts.tv_nsec)
		{
			flag = false;
		}
	}
	else
	{
		flag = true;
	}
	return flag;
}

bool operator>(const timespec& time1_ts, const timespec& time2_ts)
{
	bool flag = true;
	if (time1_ts.tv_sec < time2_ts.tv_sec)
	{
		flag = false;
	}
	else if (time1_ts.tv_sec == time2_ts.tv_sec)
	{
		if (time1_ts.tv_nsec <= time2_ts.tv_nsec)
		{
			flag = false;
		}
	}
	else
	{
		flag = true;
	}
	return flag;
}

int main()
{
	timespec ts, time_now, t1, t2;
	ts.tv_sec = 2;
	ts.tv_nsec = 1;
	t1.tv_sec = 5;
	t1.tv_nsec = 3;
	t2.tv_sec = 2;
	t2.tv_nsec = 2;
	const timespec& time_ts = ts;
	double tms;

	tms = timespec_to_ms(time_ts);
	cout << "time to ms:" << time_ts.tv_sec << "," << time_ts.tv_nsec << " -> " << tms << endl;
	ts = timespec_from_ms(tms);
	cout << "time from ms:" << tms << " -> " << ts.tv_sec << "," << ts.tv_nsec << endl;
	time_now = timespec_now();
	cout << "time for now:" << time_now.tv_sec << "," << time_now.tv_nsec << endl;
	ts = timespec_negate(time_ts);
	cout << "time negate:" << ts.tv_sec << "," << ts.tv_nsec << endl;
	ts = timespec_add(t1, t2);
	cout << "time add:" << t1.tv_sec << "," << t1.tv_nsec << " + " << t2.tv_sec << "," << t2.tv_nsec << " = " << ts.tv_sec << "," << ts.tv_nsec << endl;
	ts = timespec_subtract(t1, t2);
	cout << "time substract:" << t1.tv_sec << "," << t1.tv_nsec << " - " << t2.tv_sec << "," << t2.tv_nsec << " = " << ts.tv_sec << "," << ts.tv_nsec << endl;
	timespec_wait(time_ts);
	cout << "time wait:" << time_ts.tv_sec << "," << time_ts.tv_nsec << endl;
}
