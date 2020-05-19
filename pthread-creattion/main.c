#include <stdio.h>
#include <pthread.h>

const size_t numThread = 2; // # of the thread
void* plusTen(void *arg);   // declare the function

int main() {
    pthread_t pthID[numThread];
    int arrIn[numThread];
    int* arrOut[numThread];
    // assign the value to the threads
    for (size_t i = 0; i < numThread; ++i) {
        arrIn[i] = i;
        pthread_create(&pthID[i], NULL, plusTen, &arrIn[i]);
    }
    // catch the returned value with the pointer array
    for (size_t i = 0; i < numThread; ++i) {
        pthread_join(pthID[i], &arrOut[i]);
        // print the output value and its address
        printf("\n(main) arrOut[%zu] = %p", i, arrOut[i]);
        printf("\n(main) output val = %d", *arrOut[i]);
    }
    return 0;
}

void* plusTen(void* arg) {
    int* ptrVal = (int*) arg;   // ptrVal is a pointer toward an integer
    printf("\n(thread) ptrVal = %p", ptrVal);       // print the address
    printf("\n(thread) input val = %d", *ptrVal);   // print the value by dereference
    *ptrVal += 10;  // add 10
    pthread_exit(ptrVal);
}