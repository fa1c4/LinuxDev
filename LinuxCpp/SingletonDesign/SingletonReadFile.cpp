#include <iostream>
#include <fstream>
#include <chrono>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <future>
#include <mutex>
#include "SingletonFile.h"

#define MAX_THREADS 4
std::mutex mtx;

SingletonFile* SingletonFile::instance = nullptr;
std::ifstream* SingletonFile::pFile = nullptr;


int SingletonReadFile(int t_id) {
    std::string line;
    SingletonFile* tsf = SingletonFile::getInstance();

    for (int i = 0; i < 20; ++i) {
        mtx.lock();
        line = tsf->ReadLine();
        std::cout << "thread:" << t_id << " loop: " << i << " -> " << line << std::endl;
        mtx.unlock();
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

    SingletonFile *sf = SingletonFile::getInstance();
    sf->OpenFile(argv[1]);
    if (!sf->Ready()) {
        std::cout << " Failed Open File " << argv[1] << std::endl;
        exit(1);
    }

    try {
        // init threads
        for (j = 0; j < MAX_THREADS; ++j) {
            rc[j] = std::async(SingletonReadFile, j);
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
