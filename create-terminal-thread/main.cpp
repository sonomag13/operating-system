#include <iostream>
#include <thread>

using namespace std;

static bool finished = false;

void printSomething();

int main() {

    cout << "thread id of main = " << this_thread::get_id() << endl;

    thread worker(printSomething);

    cin.get();          // get a key interrupt

    finished = true;    // set the finished sign to be true

    worker.join();

    return EXIT_SUCCESS;

}

void printSomething() {
    using namespace chrono_literals;
    cout << "thread id of worker = " << this_thread::get_id() << endl;
    while(!finished) {
        cout << "hello world~!" << endl;
        this_thread::sleep_for(1s);
    }
}