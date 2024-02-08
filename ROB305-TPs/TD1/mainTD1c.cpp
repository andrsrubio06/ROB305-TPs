#include <unistd.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>


timespec timespec_now(){
	timespec time_now;
	clock_gettime(CLOCK_REALTIME, &time_now);
	return time_now;
}


void incr(unsigned int nLoops, double* pCounter)
{
    for(unsigned int i = 0; i < nLoops; ++i)
    {
        *pCounter += 1.0;
    }
}

int main(int argc, char* argv[])
{
    double counter = 0.0;
   	timespec time_begin, time_end;

    if (argc == 1) 
    {
        std::cout << "Loop value requise, insert into format './execfile nLoops'" << std::endl;
        return 1;
    }

    unsigned int nLoops = strtoul(argv[1], NULL, 10);

    time_begin = timespec_now();
    incr(nLoops, &counter);          
    time_end = timespec_now();

    std::cout << "Counter value: " << counter << std::endl;    
    std::cout << std::fixed << std::setprecision(9) << "Time needed: " << (timespec_to_ms(time_end - time_begin)/1000) << " seconds" << std::endl; 
    
    return 0;
}