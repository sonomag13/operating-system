/*
    1115. Print FooBar Alternately
    Medium

    Suppose you are given the following code:

    class FooBar {
    public void foo() {
        for (int i = 0; i < n; i++) {
        print("foo");
        }
    }

    public void bar() {
        for (int i = 0; i < n; i++) {
        print("bar");
        }
    }
    }
    The same instance of FooBar will be passed to two different threads. Thread A will call foo() 
    while thread B will call bar().  Modify the given program to output "foobar" n times.
    
    Example 1:
    Input: n = 1
    Output: "foobar"
    Explanation: There are two threads being fired asynchronously. One of them calls foo(), 
    while the other calls bar(). "foobar" is being output 1 time.
    
    Example 2:
    Input: n = 2
    Output: "foobarfoobar"
    Explanation: "foobar" is being output 2 times.
 */

#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std; 

class FooBar {
public:

FooBar(int n) {
    this->n = n;    
}

~FooBar = default; 

void foo(function<void()> printFoo) {            
    for (int i = 0; i < n; i++) {      
        // lock the mutex and check if it is ready to print                      
        unique_lock<mutex> uniqlk(mut);   
        cond.wait(uniqlk, [this] () {return state == ready4Foo;});        
        // critical session starts        
        printFoo();
        // critical session ends
        state = ready4Bar; // set ready to print bar
        cond.notify_all(); // release the mutex
    }
}

void bar(function<void()> printBar) {           
    for (int i = 0; i < n; i++) {
        // lock the mutex and check if it is ready to print
        unique_lock<mutex> uniqlk(mut);         
        cond.wait(uniqlk, [this] () {return state == ready4Bar;});
        // critical session starts
        printBar();
        // critical session ends
        state = ready4Foo; // set ready to print foo
        cond.notify_all(); // release the mutex
    }
}
    
private:
int n;
mutex mut; 
condition_variable cond; 
int ready4Bar{0}, ready4Foo{1}; 
int state{ready4Foo};

};