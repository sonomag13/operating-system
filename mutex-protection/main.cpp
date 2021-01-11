
/**
 * https://www.youtube.com/watch?v=GXXE42bkqQk
 */

#include <iostream>
// #include <thread>
#include <atomic>

#define NUM_LOOPS 5E6

// std::atomic<long long> atomicSum(0);
long long sum{0};
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

using namespace std;

/*
 * since sum is a shared memory, this function is a critical section
 * here are two options:
 * - make the global variable atomic
 * - protect with mutex
 */
void* counting_thread(void* arg) {
    int offset = *(int*) arg;
    for (size_t i = 0; i < NUM_LOOPS; ++i) {
        pthread_mutex_lock(&mtx);
        sum += offset;
        pthread_mutex_unlock(&mtx);
    }
    pthread_exit(nullptr);
}

int main() {

    // start the threads
    pthread_t id1;
    int offset1 = +1;
    pthread_create(&id1, nullptr, counting_thread, &offset1);
    pthread_t id2;
    int offset2 = -1;
    pthread_create(&id2, nullptr, counting_thread, &offset2);

    // wait for finish
    pthread_join(id1, nullptr);
    pthread_join(id2, nullptr);

    cout << "sum = " << sum << endl;

    return EXIT_SUCCESS;
}
