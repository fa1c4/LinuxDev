#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {
    // if (fork() == 0) {
    //     // child process execution
    //     cout << "Executing Child Process id: " << getpid() << endl << endl;
    //     exit(0);
    // } else {
    //     // parent process execution
    //     pid_t cpid = wait(NULL);
    //     cout << "Executing Parent Process id: " << getpid() << " | ";
    //     cout << "the child process id of it: " << cpid << endl;
    // }

    cout << "beginning of sub process, pid is: " << getpid() << endl;
    if (argc >= 2) {
        for (int i = 0; i < argc; ++i) {
            cout << "arg" << i << ": " << argv[i] << endl;
        }
    }
    cout << "ending of sub process, pid is: " << getpid() << endl;

    return 0;
}
