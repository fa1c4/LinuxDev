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
    struct mq_attr attr;
    mqd_t mqdes;
    char buf[QUEUE_MSGSIZE + 1];
    unsigned int prio;
    memset(buf, '\0', sizeof(buf));

    // step1: setup the attribute structure
    attr.mq_maxmsg = QUEUE_MAXMSG;
    attr.mq_msgsize = QUEUE_MSGSIZE;
    attr.mq_curmsgs = 0;
    attr.mq_flags = 0;

    // step2: open a queue with the attribute structure
    // mqdes = mq_open(QUEUE_NAME, O_RDONLY, QUEUE_PERMS, &attr);
    mqdes = mq_open(QUEUE_NAME, O_RDONLY, QUEUE_PERMS, &attr);
    if (mqdes < 0) {
        perror("mq_open()");
        exit(-1);
    }

    while (true) {
        memset(buf, '\0', sizeof(buf));
        ssize_t bytes_read = mq_receive(mqdes, buf, QUEUE_MSGSIZE, &prio);
        if (bytes_read > 0) {
            buf[bytes_read] = '\0';
            printf("Byte received: %zd: %s\n", bytes_read, buf); 
        }

        if (bytes_read == 3 && !strcmp(buf, "end")) 
            break;
    }

    // step3: close queue
    mq_close(mqdes);

    return 0;
}
