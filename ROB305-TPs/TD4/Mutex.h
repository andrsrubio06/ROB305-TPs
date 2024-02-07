#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex {
public:
    Mutex();
    ~Mutex();

private:
    pthread_mutex_t posixId;
    pthread_cond_t posixCondId;

private:
    void lock();
    bool lock(double timeout_ms);
    bool tryLock();
    void unlock();
};

#endif // MUTEX_H
