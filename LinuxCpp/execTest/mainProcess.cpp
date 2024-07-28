#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main() {
    cout << "beginning of main process, pid is: " << getpid() << endl;

    if (fork() == 0) {
        // child process execution
        ::execl("./subProcess.elf", "Hi", "from", "Baili", NULL);
        exit(0);
    } else {
        // parent process execution
        pid_t cpid = wait(NULL);
        cout << "Executing Parent Process"<< endl;
    }

    cout << "ending of main process, pid is: " << getpid() << endl;

    return 0;
}
