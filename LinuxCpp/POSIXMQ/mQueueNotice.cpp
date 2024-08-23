#include <iostream>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


#define QUEUE_NAME  "/tmpqueue" /* Queue name. */
#define QUEUE_PERMS ((int)(0644))
#define QUEUE_MAXMSG  16 /* Maximum number of messages. */
#define QUEUE_MSGSIZE 1024 /* Length of message. */
#define QUEUE_ATTR_INITIALIZER ((struct mq_attr){0, QUEUE_MAXMSG, QUEUE_MSGSIZE, 0, {0}})

#define QUEUE_POLL_CONSUMER ((struct timespec){2, 500000000})
#define QUEUE_POLL_PUBLISHER ((struct timespec){5, 0})

#define QUEUE_MAX_PRIO ((int)(9))

#define handle_error(msg) do {perror(msg); exit(EXIT_FAILURE);} while (0)

// thread start function
static void thread_func(union sigval sv) {
    struct mq_attr attr;
    ssize_t nr;
    void *buf;
    mqd_t mqdes = *((mqd_t*) sv.sival_ptr);

    // determine max mag size then allocate buffer to receive msg
    std::cout << "Thread trigged ..." << std::endl;

    if (mq_getattr(mqdes, &attr) == -1) 
        handle_error("mq_getattr");
    
    buf = malloc(attr.mq_msgsize);
    if (buf == NULL) handle_error("malloc");

    while (true) {
        memset(buf, '\0', attr.mq_msgsize);
        nr = mq_receive(mqdes, (char*)buf, attr.mq_msgsize, NULL);
        if (nr == -1) handle_error("mq_receive");
        printf("Read %zd bytes from MQ: %s\n", nr, (char*)buf);
        if (nr == 3 && !strcmp((char*)buf, "end")) break;
    }

    free(buf);
    exit(EXIT_SUCCESS);
}


int main(int argc, char* argv[]) {
    mqd_t mqdes;
    struct sigevent sev;
    struct mq_attr attr;

    attr.mq_maxmsg = QUEUE_MAXMSG;
    attr.mq_msgsize = QUEUE_MSGSIZE;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    mqdes = mq_open(QUEUE_NAME, O_RDONLY, QUEUE_PERMS, &attr);
    if (mqdes == -1) handle_error("mq_open");

    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = thread_func;
    sev.sigev_notify_attributes = NULL;
    sev.sigev_value.sival_ptr = &mqdes;
    if (mq_notify(mqdes, &sev) == -1)
        handle_error("mq_notify");

    std::cout << "Pausing (waitting) ..." << std::endl;
    pause();
    std::cout << "After Pausing (waitting) ..." <<std::endl;
    exit(EXIT_SUCCESS);
}
