#include <iostream>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/vtimes.h>
#include <unistd.h>
#include <ulimit.h>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <future>


int using_memory(int i) {
    char mArray[1024*8];
    memset(mArray, '\0', sizeof(mArray));
    for (size_t j = 0; j < sizeof(mArray); ++j) {
        mArray[j] = 'F';
    }
    return 0;
}

void read_write_files(char* inFileName, char* outFileName) {
    std::vector<std::string> mVec;
    std::string line;
    int i;

    std::ifstream inFile(inFileName);
    if (inFile.is_open()) {
        i = 0;
        while (getline(inFile, line)) {
            mVec.push_back(line);
            ++i;
            if (i == 1 || i == 20000)
                std::cout << line << std::endl;
        }
        std::cout << line << std::endl;
        inFile.close();
    }

    std::ofstream outFile(outFileName);
    if (outFile.is_open()) {
        for (auto it = mVec.begin(); it != mVec.end(); ++it) {
            outFile << *it << std::endl;
        }
        outFile.flush();
        outFile.close();
    }
}


int main(int argc, char* argv[]) {
    struct rusage *pUsg = new struct rusage();
    int ret;

    if (argc != 3) {
        std::cout << "Usage: $0 <in-filename> <out-filename>" << std::endl;
        exit(-1);
    }

    int totThread = 10;
    std::future<int> mTH[totThread];
    for (int i = 0; i < totThread; ++i) {
        mTH[i] = std::async(using_memory, i);
    }

    for (int i = 0; i < totThread; ++i) {
        mTH[i].get();
    }

    // input and output files
    read_write_files(argv[1], argv[2]);

    ret = getrusage(RUSAGE_SELF, pUsg);
    std::cout << "----- RUSAGE_SELF Process Usage -----" << std::endl;
    if (ret == 0) {
        std::cout << "Unshared memory used for stack: " << pUsg->ru_isrss << std::endl;
        std::cout << "Unshared memory used for data: " << pUsg->ru_idrss << std::endl;
        std::cout << "Shared memory with other processes: " << pUsg->ru_ixrss << std::endl;
        std::cout << "Maximum of physical memory used: " << pUsg->ru_maxrss << std::endl;
        std::cout << "Page faults by doing I/O (hard): " << pUsg->ru_majflt << std::endl;
        std::cout << "Page faults by doing I/O (soft): " << pUsg->ru_minflt << std::endl;
        std::cout << "Number of IPC messages received: " << pUsg->ru_msgrcv << std::endl;
        std::cout << "Number of IPC messages sent: " << pUsg->ru_msgsnd << std::endl;
        std::cout << "Swapped entirely out of main memory: " << pUsg->ru_nswap << std::endl;
        std::cout << "Voluntarily context switch: " << pUsg->ru_nvcsw << std::endl;
        std::cout << "Invuluntary context switch: " << pUsg->ru_nivcsw << std::endl;
        std::cout << "Number of signals received: " << pUsg->ru_nsignals << std::endl;
        std::cout << "File system read from the disk: " << pUsg->ru_inblock << std::endl;
        std::cout << "File system write to the disk: " << pUsg->ru_oublock << std::endl;
        std::cout << "User CPU time used: " << pUsg->ru_utime.tv_sec << std::endl;
        std::cout << "System CPU time used: " << pUsg->ru_stime.tv_sec << std::endl;
    } else {
        std::cout << "Failed call getrusage()" << std::endl;
    }

    return ret;
}
