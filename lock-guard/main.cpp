/**
 * Ref.: https://www.youtube.com/watch?v=ACoYnEzjEz4&list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp&index=9
 **/

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex mut;

void taskWithLock(const string& strIn, int num) {
    // this function uses the conventional lock and unlock
    mut.lock();
    // critical session starts
    for (int i = 0; i < num; ++i) {
        char str2print[1024];
        sprintf(str2print, "[%d]: %s", i, strIn.c_str());
        cout << str2print << endl;
    }
    // critical session ends
    mut.unlock();
}

void taskWithLockGuard(const string& strIn, int num) {
    /**
     * this function uses lock guard
     * - no need to explicitly code lock and unlock
     * - lock the mutex when enter the scope and unlock it when exiting
     **/
    lock_guard<mutex> lock(mut);
    // critical session starts
    for (int i = 0; i < num; ++i) {
        char str2print[1024];
        sprintf(str2print, "[%d]: %s", i, strIn.c_str());
        cout << str2print << endl;
    }
    // critical session ends
}


int main() {

    cout << "using conventional way to lock and unlock the mutex" << endl;
    thread t1(taskWithLock, "t1", 5);
    thread t2(taskWithLock, "t2", 3);
    t1.join();
    t2.join();

    cout << "\n\nusing lock guard" << endl;
    thread t3(taskWithLock, "t3", 5);
    thread t4(taskWithLock, "t4", 3);
    t3.join();
    t4.join();

    return 0;
}
