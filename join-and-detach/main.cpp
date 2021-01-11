#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

void run(int count) {

    cout << "the thread job starts" << endl;
    while (count-- > 0) {
        char str[1024];
        sprintf(str, "count = %d", count);
        cout << str << endl;
        this_thread::sleep_for(0.1s);
    }
    cout << "the thread job ends" << endl;
}

int main() {

    int num{5};

    // the case where the thread will join
    cout << "join section starts" << endl;
    thread t1(run, num);
    if (t1.joinable()) {
        t1.join();
        cout << "join the thread" << endl;
    }
    cout << "join section ends" << endl;

    // the case where the thread is detached
    cout << "\n\ndetach section starts" << endl;
    thread t2(run, num);
    t2.detach();
    if (t2.joinable()) {
        t2.join();
        cout << "join the thread" << endl;
    }
    /**
     * if we ask the main thread to sleep for 1 second,
     * there will be sufficient time to complete run(...)
     * In case the sleeping time is 0.2sec, the run will
     * print approximately 2 times
     *
     * Without the sleeping time in the main thread, it is
     * very likely that the main thread ends before t2
     * complete running run(...)
     **/
    this_thread::sleep_for(1s);
    cout << "detach section ends" << endl;

    return 0;
}
