#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <atomic>

using namespace std;


std::atomic<std::sig_atomic_t> signaled(0);

void signalHandler(int signum) {
    signaled.store(signum, std::memory_order_relaxed);
}

void* threadFunction(void* t) {
    long tid;
    tid = (long)t;

    std::cout << "Thread with id: " << tid << " is waiting signal ... " << std::endl;
    pause();

    int sigNum = signaled;
    std::cout << "Thread with id: " << tid << " signal (" << sigNum << ") ";
    switch (sigNum) {
        case SIGUSR1:
            std::cout << "SIGUSR1";
            break;
        case SIGUSR2:
            std::cout << "SIGUSR2";
            break;
        default:
            exit(sigNum);
            break;
    }

    std::cout << " received." << std::endl;
    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
    int rc;
    long tid;

    if (argc != 2) {
        std::cout << "Usage: pthreadSignal <number threads> " << std::endl;
        return -1;
    }

    int numThread = std::stoi(argv[1]);
    pthread_t threads[numThread];
    pthread_attr_t attr;
    void* status;

    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (tid = 0; tid < numThread; ++tid) {
        std::cout << "main(): creating thread, " << tid << std::endl;
        rc = pthread_create(&threads[tid], NULL, threadFunction, (void*)tid);
        if (rc) {
            std::cout << "Error: unable to create thread, " << rc << std::endl;
            exit(-1);
        }
    }
    sleep(3);

    for (tid = 0; tid < numThread; ++tid) {
        if (tid % 2 == 0) {
            std::cout << "main(): sending SIGUSR1 (10) signal to thread, " << tid << std::endl;
            pthread_kill(threads[tid], SIGUSR1);
        } else {
            std::cout << "main(): sending SIGUSR2 (12) signal to thread, " << tid << std::endl;
            pthread_kill(threads[tid], SIGUSR2);
        }
    }

    pthread_attr_destroy(&attr);
    for (tid = 0; tid < numThread; ++tid) {
        rc = pthread_join(threads[tid], &status);
        if (rc) {
            std::cout << "Error: unable to join, " << rc << std::endl;
            exit(-2);
        }
    }

    std::cout << "Main: program exiting." << std::endl;
    pthread_exit(NULL);
}
