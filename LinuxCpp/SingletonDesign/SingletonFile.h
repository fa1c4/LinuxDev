#ifndef SINGLETONFILE_H
#define SINGLETONFILE_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <future>
#include <mutex>
#include <string>

class SingletonFile {
public:
    static SingletonFile* getInstance();
    bool Ready();
    void OpenFile(std::string fileName);
    std::string ReadLine();
    ~SingletonFile();

private:
    static SingletonFile *instance;
    static std::ifstream *pFile;
    SingletonFile();
};

#endif // SINGLETONFILE_H
