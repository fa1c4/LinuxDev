#ifndef PSHM_H
#define PSHM_H

#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg) do {perror(msg); exit(EXIT_FAILURE);} while (0)
#define BUFF_SIZE 1024

struct shmbuf {
    sem_t sem1;
    sem_t sem2;
    char buf[BUFF_SIZE];
};

void show_sem_value(struct shmbuf *shmBuff) {
    int val1, val2;
    ::sem_getvalue(&shmBuff->sem1, &val1);
    ::sem_getvalue(&shmBuff->sem2, &val2);
    std::cout << "shmp->sem1: " << val1 << " shmp->sem2: " << val2 << std::endl; 
}

#endif
