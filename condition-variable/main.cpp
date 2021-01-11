#include <chrono>
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

queue<int> q;
mutex mtx;
condition_variable cond;

// data producer
void function_1() {
    int count = 10;
    while (count > 0) {
        std::unique_lock<mutex> locker(mtx);
        q.push(count);
        locker.unlock();
        cond.notify_one();
        count--;
    }
}

// data consumer
void function_2() {
    int data = 0;
    while (data != 1) {
        std::unique_lock<std::mutex> locker(mtx);

        // use a lambda function to check if the queue is empty
        auto check_q = []() {
            return !q.empty();
        };

        /**
         * Ref.: https://en.cppreference.com/w/cpp/thread/condition_variable/wait
         *
         * A possible bug here is so called spurious wake, i.e. function 2 is NOT waked up by cond.notify() in function
         * 1, but being wake up by itself. In this case, without the lambda function check_q, function 2 will go to
         * sleep after cond.wait WITH the mutex, it will block other thread to access the shared memory.
         *
         * This is why it is necessary to check if the queue is empty, and the result of the checking is the second
         * argument of wait() in the format of std::predicted. If false, the wait will continue. That said, if the queue
         * is not empty, the return is true, then the function stops waiting
         */
        cond.wait(locker, check_q);
        data = q.front();
        q.pop();
        locker.unlock();
        cout << "t2 got a value from t1: " << data << endl;
    }

}

// It is hard to set the sleep time.
int main() {

    thread t1(function_1);
    thread t2(function_2);

    t1.join();
    t2.join();

    return 0;
}