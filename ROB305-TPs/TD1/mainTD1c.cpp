#include <iostream>
#include <pthread.h>
#include <time.h>


void* incrementer(void* v_stop) {
        volatile bool* p_stop = (volatile bool*) v_stop;
        double counter = 0.0;
        while (not *p_stop) {
            counter += 1.0;
        }
        std::cout << "Counter value = " << counter << std::endl;
        return v_stop;
    }

void* incr(unsigned int nLoops, double* pCounter){
    for (unsigned int i = 0; i < nLoops; i++){
        *pCounter += 1.0;
    }
}

int main(int argc, char* argv[])
{
   // std::cout << "Hello World" << std::endl;

    unsigned int nLoops = std::stoi(argv[1]);
    double counter = 0.0;

    struct timespec debut, fin, duree;
    clock_gettime(CLOCK_REALTIME, &debut);
    // . . . . Section de code dont on veut mesurer la durée . . . .
    incr(nLoops, &counter);
    clock_gettime(CLOCK_REALTIME, &fin);

    std::cout << "Counter value = " << counter << std::endl;

    duree.tv_sec = fin.tv_sec - debut.tv_sec;
    if (fin.tv_nsec < debut.tv_nsec) {
    duree.tv_sec -= 1;
    fin.tv_nsec += 1000000000;
    }
    duree.tv_nsec = fin.tv_nsec - debut.tv_nsec;
    std::cout << duree.tv_sec + duree.tv_nsec/1000000000. << " seconds" << std::endl;

    // volatile bool stop = false;
    // pthread_t incrementThread;
    // pthread_create(&incrementThread, nullptr, incrementer, (void*) &stop);
    
    // for (char cmd = 'r'; cmd != 's'; std::cin >> cmd)
    // std::cout << "Type 's' to stop: " << std::flush;
    
    // stop = true;
    // pthread_join(incrementThread, nullptr);

    return 0;


}