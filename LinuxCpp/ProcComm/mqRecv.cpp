#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#define PERMS 0644
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
    key_t key;

    // need msgq.txt before start mqRecv.elf
    if ((key = ftok("msgq.txt", 'B')) == -1) {
        std::cout << "ftok - error" << std::endl;
        exit(-1);
    }

    if ((msqid = msgget(key, PERMS)) == -1) {
        std::cout << "msgget - error" << std::endl;
        exit(-2);
    }

    std::cout << "message queue: ready to receive messages." << std::endl;
    while (true) {
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            std::cout << "msgrcv - error" << std::endl;
            exit(-2);
        }

        std::cout << "received: " << buf.mtext << std::endl;
        if (!strcmp(buf.mtext, "^D")) break;
    }

    std::cout << "message queue: done receiving messages" << std::endl;
    system("rm msgq.txt");
    return 0;
}
