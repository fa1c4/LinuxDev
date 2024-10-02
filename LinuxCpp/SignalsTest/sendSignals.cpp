#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

using namespace std;


int main(int argc, char* argv[]) {
    int mSIG = 0;
    char opt[32];
    pid_t mPID;

    if (argc != 2) {
        std::cout << "Usage: sendSignal <process ID>" << std::endl;
        return -1;
    }

    mPID = atoi(argv[1]);
    mSIG = 1;
    while (mSIG) {
        memset(opt, 0, sizeof(opt));
        std::cout << "Waiting input signal (1, 2, 10, 12): ";
        std::cin.getline(opt, sizeof(opt));
        mSIG = std::atoi(opt);
    
        if (mSIG) kill(mPID, mSIG);
    }

    return 0;
}
