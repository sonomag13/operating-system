/**
    1114. Print in Order
    Easy
    
    Suppose we have a class:

    public class Foo {
    public void first() { print("first"); }
    public void second() { print("second"); }
    public void third() { print("third"); }
    }
    The same instance of Foo will be passed to three different threads. Thread A will call first(), 
    thread B will call second(), and thread C will call third(). Design a mechanism and modify the 
    program to ensure that second() is executed after first(), and third() is executed after second().

    

    Example 1:
    Input: [1,2,3]
    Output: "firstsecondthird"
    Explanation: There are three threads being fired asynchronously. The input [1,2,3] means thread A calls first(), 
    thread B calls second(), and thread C calls third(). "firstsecondthird" is the correct output.

    Example 2:
    Input: [1,3,2]
    Output: "firstsecondthird"
    Explanation: The input [1,3,2] means thread A calls first(), thread B calls third(), and thread C calls second(). 
    "firstsecondthird" is the correct output.
    **/

#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std; 

class Foo {

public:
Foo() {
    // initialize the status of the status if first and second job are completed
    firstCompleted = false; 
    secondCompleted = false; 
}

~Foo() = default; 

void first(function<void()> printFirst) {
    // printFirst does not need to wait for any job to complete priori
    lock_guard<mutex> lk(mtx);     // lock the mutex    
    printFirst();                   // critical session
    firstCompleted = true;          // reset the flag
    condPrintFirst.notify_all();    // broadcase to other thread that the mutex is ready to release
}

void second(function<void()> printSecond) {
    
    /**
     * printSecond is bloked here until printFirst is completed
     * lambda function to get the status if the first job is done
     **/ 
    auto printFirstCompleted = [this] () {
        return firstCompleted; 
    };         
    unique_lock<mutex> lk(mtx); 
    condPrintFirst.wait(lk, printFirstCompleted);
    
    // critical session starts    
    printSecond();                   
    secondCompleted = true;     // reset the status of the second print
    // critical session ends
    
    condPrintSecond.notify_all();
  }

void third(function<void()> printThird) {
    
    // wait until printSecond is completed
    auto printSecondCompleted = [this] () {
        return secondCompleted;
    }; 
    unique_lock<mutex> lk(mtx);
    
    // critical session starts
    condPrintSecond.wait(lk, printSecondCompleted);    
    printThird();
    // critical session ends
}
    
private: 
    bool firstCompleted{false};     // if the first print is completed
    bool secondCompleted{false};    // if the second print is completed
    mutex mtx;  // mutex
    condition_variable condPrintFirst;  // conditional varialbe of the first print
    condition_variable condPrintSecond; // conditional varialbe of the second print
    
};