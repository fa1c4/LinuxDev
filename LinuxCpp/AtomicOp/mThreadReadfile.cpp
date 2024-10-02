#include <iostream>
#include <fstream>
#include <chrono>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <atomic>

using namespace std;
#define MAX_THREADS 8

std::atomic_flag lock_cout = ATOMIC_FLAG_INIT;
struct threadParam {
    int t_id;
    char t_FileName[32];
};

void* ReadFile(void* tParam) {
    struct threadParam* mData;
    mData = (struct threadParam*) tParam;
    std::string line;
    int i, initPos;
    initPos = mData->t_id;

    ifstream mFile(mData->t_FileName);
    if (mFile.is_open()) {
        i = 0;
        mFile.seekg(initPos, ios::beg);
        while (getline(mFile, line) && i < 1) {
            ++i;
            // untill lock then starts operating 
            while (lock_cout.test_and_set()) {}
            std::cout << "Thread " << mData->t_id << ": " << line << std::endl;
            lock_cout.clear();
        }
        mFile.close();
    } else {
        std::cout << "Can not open file test.txt for reading" << std::endl;
    }

    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
    pthread_t threads[MAX_THREADS];
    struct threadParam mTD[MAX_THREADS];
    int j, rc;

    if (argc != 2) {
        std::cout << "Usage: mThreadReadfile <filename>" << std::endl;
        return -1;
    }

    for (j = 0; j < MAX_THREADS; ++j) {
        mTD[j].t_id = j;
        memset(mTD[j].t_FileName, 0, sizeof(mTD[j].t_FileName));
        memcpy(mTD[j].t_FileName, argv[1], strlen(argv[1]));
        rc = pthread_create(&threads[j], NULL, ReadFile, (void*)&mTD[j]);
        if (rc) {
            std::cout << "Error: unable to create thread, " << rc << std::endl;
            exit(-1);
        }
    }

    pthread_exit(NULL);
}
