#include <iostream>
#include <pthread.h>
#include <time.h>



struct Data {
volatile unsigned int nLoops;
volatile double pCounter;
//pthread_mutex_t mutex;
};

void* incrementer(void* v_stop) {
        volatile bool* p_stop = (volatile bool*) v_stop;
        double counter = 0.0;
        while (not *p_stop) {
            counter += 1.0;
        }
        std::cout << "Counter value = " << counter << std::endl;
        return v_stop;
    }

// void* incr(unsigned int nLoops, double* pCounter){
//     for (unsigned int i = 0; i < nLoops; i++){
//         *pCounter += 1.0;
//     }
// }

void* incr(void* v_data){
    Data* pData = (Data*) v_data;
    for (unsigned int i = 0; i < pData->nLoops; i++){
        pData->pCounter += 1.0;
    }
    return v_data;
}


int main(int argc, char* argv[])
{
   // std::cout << "Hello World" << std::endl;


    unsigned int nLoops = std::stoi(argv[1]);
    unsigned int nTasks = std::stoi(argv[2]);
    double counter = 0.0;
    Data data = {nLoops, counter};
    pthread_t incrementThread[nTasks];

    struct timespec debut, fin, duree;
    clock_gettime(CLOCK_REALTIME, &debut);
    // . . . . Section de code dont on veut mesurer la durée . . . .
    for (unsigned int i = 0; i < nTasks; i++){
        pthread_create(&incrementThread[i], nullptr, incr, &data);
        //incr(nLoops, &counter);
    }
    for (unsigned int i = 0; i < nTasks; i++){
        pthread_join(incrementThread[i], nullptr);
    }
    clock_gettime(CLOCK_REALTIME, &fin);

    std::cout << "Counter value = " << data.pCounter << std::endl;

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