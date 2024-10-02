#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

using namespace std;


void signalHandler(int signum) {
    std::cout << "Raise signal (" << signum << ") ";

    switch (signum) {
        case 1:
            std::cout << "SIGHUP";
            break;
        case 2:
            std::cout << "SIGINT";
            break;
        case 10:
            std::cout << "SIGUSR1";
            break;
        case 12:
            std::cout << "SIGUSR2";
            break;
        default:
            exit(signum);
            break;
    }

    std::cout << " received." << std::endl;
}


int main(int argc, char* argv[]) {
    int i = 0;
    char opt[32];

    // register signal SIGINT and signal handler
    signal(SIGHUP, signalHandler);
    signal(SIGINT, signalHandler);
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);

    pid_t mPID = getpid();
    std::cout << "Process: " << mPID << std::endl;
    
    i = 1;
    while (i) {
        memset(opt, 0, sizeof(opt));
        std::cout << "Waiting input signal (1, 2, 10, 12): ";
        std::cin.getline(opt, sizeof(opt));
        i = std::atoi(opt);
        if (i) raise(i);
    }

    return 0;
}
