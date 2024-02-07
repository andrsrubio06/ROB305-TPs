#include <pthread.h>
#include "Mutex.h"
#include <stdexcept>
#include <ctime>

Mutex::Mutex() {
    if (pthread_mutex_init(&posixId, nullptr) != 0) {
        throw std::runtime_error("Failed to initialize mutex");
    }
    if (pthread_cond_init(&posixCondId, nullptr) != 0) {
        pthread_mutex_destroy(&posixId);
        throw std::runtime_error("Failed to initialize condition variable");
    }
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&posixId);
    pthread_cond_destroy(&posixCondId);
}


void Mutex::lock() {
    pthread_mutex_lock(&posixId);
}

bool Mutex::tryLock() {
    return pthread_mutex_trylock(&posixId) == 0;
}

bool Mutex::lock(double timeout_ms) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        return false;
    }
    ts.tv_sec += static_cast<time_t>(timeout_ms / 1000);
    ts.tv_nsec += static_cast<long>((timeout_ms - (timeout_ms / 1000) * 1000) * 1000000);
    return pthread_mutex_timedlock(&posixId, &ts) == 0;
}

void Mutex::unlock() {
    pthread_mutex_unlock(&posixId);
}

int main() {
    return 0;
}

