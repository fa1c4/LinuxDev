#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#define PERMS 0644 // ownership and permissions
enum {max_length = 1024};
struct mMsgBuf {
    long mtype;
    char mtext[max_length];

    mMsgBuf(): mtype(0) {
        memset(mtext, '\0', sizeof(mtext) + 1);
    }
};


int main(int argc, char *argv[]) {
    struct mMsgBuf buf;
    int msqid;
    int len;
    key_t key;

    system("touch msgq.txt");

    // ftok - convert a pathname and a project identifier to a System V IPC key
    if ((key = ftok("msgq.txt", 'B')) == -1) {
        std::cout << "ftok - error" << std::endl;
        exit(-1);
    }

    // connect or create queue if not exit
    if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
        std::cout << "msgget - error" << std::endl;
        exit(-2);
    }

    std::cout << "message queue: ready to send messages" << std::endl;
    std::cout << "Enter lines of text (use ^D to quit):" << std::endl;
    buf.mtype = 1;

    while (true) {
        std::cin.getline(buf.mtext, sizeof(buf.mtext));
        len = strlen(buf.mtext);
        // remove newline at end, if it exists
        if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
        if (msgsnd(msqid, &buf, len+1, 0) == -1)
            std::cout << "msgsnd - error" << std::endl;
        
        if (!strcmp(buf.mtext, "^D")) break;
    }

    strcpy(buf.mtext, "end");
    len = strlen(buf.mtext);
    if (msgsnd(msqid, &buf, len+1, 0) == -1)
        std::cout << "msgsnd - error" << std::endl;
    
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        std::cout << "msgctl - error" << std::endl;
        exit(-1);
    }

    std::cout << "message queue: done sending messages." << std::endl;
    return 0;
}
