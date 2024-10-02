#include <iostream>
#include <fstream>
#include <chrono>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <atomic>

using namespace std;
std::atomic<long> prgTotal(0);

void* mCalculator(void* id) {
    long subTot = 0;
    long tid;
    tid = (long)id;

    for (int i = 0; i < 100; ++i) {
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        subTot += i;
        prgTotal.fetch_add(i, std::memory_order_relaxed);
    }

    std::cout << "Thread " << tid << " Sub-Total: " << subTot << std::endl;
    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: mThreadCalculate <number threads>" << std::endl;
        return -1;
    }

    int numThread = std::stoi(argv[1]);
    pthread_t threads[numThread];
    pthread_attr_t attr;
    long j;
    int rc;
    void* status;

    prgTotal.store(10, std::memory_order_relaxed);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (j = 0; j < numThread; ++j) {
        rc = pthread_create(&threads[j], NULL, mCalculator, (void*)j);
        if (rc) {
            std::cout << "Error: unable to create thread, " << rc << std::endl;
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);
    for (j = 0; j < numThread; ++j) {
        rc = pthread_join(threads[j], &status);
        if (rc) {
            std::cout << "Error: unable to thread join " << rc << std::endl;
            exit(-2);
        }
    }

    long mTot = prgTotal;
    std::cout << "Program Total: " << mTot << std::endl;
    pthread_exit(NULL);
}
