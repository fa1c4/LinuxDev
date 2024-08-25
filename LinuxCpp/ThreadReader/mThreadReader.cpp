#include <iostream>
#include <fstream>
#include <chrono>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <future>
#include <mutex>

#define MAX_THREADS 4
std::mutex mtx;


int ThreadReadFile(int t_id, char *pFileName) {
    char inFileName[64];
    std::string line;
    int i = 0, initPos = 0;
    memset(inFileName, '\0', sizeof(inFileName));
    memcpy(inFileName, pFileName, strlen(pFileName));

    // open the file to read
    std::ifstream mFile(inFileName);
    if (mFile.is_open()) {
        i = 0;
        mFile.seekg(initPos, std::ios::beg);
        while (getline(mFile, line) && i < 20) {
            ++i;
            mtx.lock();
            std::cout << line << "-> Thread: " << t_id << " : " << i << std::endl;
            mtx.unlock();
        }
        mFile.close();
    } else {
        std::cout << "Error: can not open the file " << inFileName << std::endl; 
    }

    return 0;
}


int main(int argc, char* argv[]) {
    int j, ret = 0;
    std::future<int> rc[MAX_THREADS];

    if (argc != 2) {
        std::cout << "Usage: mThreadReader.elf <file_name>" << std::endl;
        exit(-1);
    }

    try {
        // init threads
        for (j = 0; j < MAX_THREADS; ++j) {
            rc[j] = std::async(ThreadReadFile, j, argv[1]);
        }
        // start thread tasks
        for (j = 0; j < MAX_THREADS; ++j) {
            ret = rc[j].get();
        }
    } catch (std::exception &e) {
        std:: cout << "[Exception] " << e.what() << std::endl;
    }

    return ret;
}
