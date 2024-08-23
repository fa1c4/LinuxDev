#include <iostream>
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>


#define QUEUE_NAME "/tmpqueue"
#define QUEUE_PERMS ((int)(0644))
#define QUEUE_MAXMSG 16
#define QUEUE_MSGSIZE 1024
#define QUEUE_ATTR_INITIALIZER ((struct mq_attr){0, QUEUE_MAXMSG, QUEUE_MSGSIZE, 0, {0}})

// the consumer is faster than the publisher
#define QUEUE_POLL_CONSUMER ((struct timespec){2, 500000000})
#define QUEUE_POLL_PUBLISHER ((struct timespec){5, 0})

#define QUEUE_MAX_PRIO ((int)(9))


int main(int argc, char* argv[]) {
    struct mq_attr attr; // store queue attributes
    mqd_t mqdes; // message queue descriptors
    char buf[QUEUE_MSGSIZE + 1];
    unsigned int prio;
    std::string inMsg;
    memset(buf, '\0', sizeof(buf));

    // step1: setup the attribute structure
    attr.mq_maxmsg = QUEUE_MAXMSG;
    attr.mq_msgsize = QUEUE_MSGSIZE;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;
    prio = 0;

    // step2: open a queue with the attribute structure
    mqdes = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, QUEUE_PERMS, &attr);
    if (mqdes == -1) {
        perror("mq_open()");
        exit(-1);
    }

    while (true) {
        std::cin.getline(buf, sizeof(buf));
        if (!strcmp(buf, "end")) break;
        if (mq_send(mqdes, buf, strlen(buf), prio) == -1)
            perror("mq_send()");
    }

    // step3: close all open message queue descriptors
    if (mq_send(mqdes, buf, strlen(buf), prio) == -1) {
        perror("mq_send()");
    }
    mq_close(mqdes);

    return 0;
}
