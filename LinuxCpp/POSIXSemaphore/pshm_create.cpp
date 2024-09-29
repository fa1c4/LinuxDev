#include <string.h>
#include <iostream>
#include <ctype.h>
#include "pshm.h"


int main(int argc, char* argv[]) {
    char opt[32];
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    if (argc != 2) {
        std::cerr << "Usage: pshm_create <name>" << std::endl;
        exit(EXIT_FAILURE);
    }

    char *shmpath = argv[1];
    int fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        std::cerr << "Failed to open POSIX shared memory objects" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (ftruncate(fd, sizeof(struct shmbuf)) == -1) {
        std::cerr << "Failed to set shared memory objects size" << std::endl;
        exit(EXIT_FAILURE);
    }

    void* addr = mmap(NULL, sizeof(struct shmbuf), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    struct shmbuf* shmp = static_cast<struct shmbuf*>(addr);
    
    if (sem_init(&shmp->sem1, 1, 0) == -1) errExit("sem_init-sem1");
    if (sem_init(&shmp->sem2, 1, 0) == -1) errExit("sem_init-sem2");
    show_sem_value(shmp);

    while (true) {
        std::cout << "Select Option (get | wait1 | wait2 | post1 | post2 | read | write | exit): ";
        memset(opt, 0, sizeof(opt));
        std::cin.getline(opt, sizeof(opt));

        if (!strcmp(opt, "wait1")) {
            if (sem_wait(&shmp->sem1) == -1) errExit("sem_wait1");
            show_sem_value(shmp);
        } else if (!strcmp(opt, "wait2")) {
            if (sem_wait(&shmp->sem2) == -1) errExit("sem_wait2");
            show_sem_value(shmp);
        } else if (!strcmp(opt, "post1")) {
            if (sem_post(&shmp->sem1) == -1) errExit("sem_post1");
            show_sem_value(shmp);
        } else if (!strcmp(opt, "post2")) {
            if (sem_post(&shmp->sem2) == -1) errExit("sem_post2");
            show_sem_value(shmp);
        } else if (!strcmp(opt, "read")) {
            std::cout << shmp->buf << std::endl;
        } else if (!strcmp(opt, "write")) {
            std::cout << " -> Shared Memory: ";
            memset(buffer, 0, sizeof(buffer));
            std::cin.getline(buffer, sizeof(buffer));
            memset(shmp->buf, 0, 1024);
            memcpy(shmp->buf, buffer, strlen(buffer));
        } else if (!strcmp(opt, "get")) {
            show_sem_value(shmp);
        } else {
            break;
        }
    }

    // unlink the shared memory object
    shm_unlink(shmpath);
    exit(EXIT_SUCCESS);
}
