#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/**
 * share memory and mutex in the global scope
 * the mutex present the situation where the shared memory to be modified
 * by multiple thread simultaneously.
 * That said, only one thread is allowed to
 **/
int amount{0};
mutex mut;

void addAmount(int increment) {
    /**
     * this function uses mutex to ensure only one thread is allowed
     * to modify the amount
     **/
    mut.lock();
    // critical session starts
    char str[1024];
    sprintf(str, "amount = %d and increment = %d", amount, increment);
    cout << str << endl;
    amount += increment;
    // critical session ends
    mut.unlock();
}

int main() {

    // there is no guarantee which thread will first lock the mutex
    thread t1(addAmount, 20);
    thread t2(addAmount, 10);

    t1.join();
    t2.join();

    return 0;
}
