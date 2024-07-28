#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main() {
    if (fork() == 0) {
        // child process execution
        cout << "Executing Child Process id: " << getpid() << endl << endl;
        exit(0);
    } else {
        // parent process execution
        pid_t cpid = wait(NULL);
        cout << "Executing Parent Process id: " << getpid() << " | ";
        cout << "the child process id of it: " << cpid << endl;
    }

    return 0;
}
