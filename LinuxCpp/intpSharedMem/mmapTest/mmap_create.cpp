#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PERM 0644


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: mmap_read_write <filename> <message>" << std::endl;
        exit(-1);
    }

    size_t fsize = strlen(argv[2]) + 1;
    int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, PERM);
    std::cout << "File: " << argv[1] << " <- size: " << fsize << std::endl;

    // set the file size
    lseek(fd, fsize-1, SEEK_SET);
    write(fd, "\n", 1);

    // maping
    void *addr = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    memcpy(addr, argv[2], strlen(argv[2]));
    msync(addr, fsize, MS_SYNC);
    
    // unmap
    munmap(addr, fsize);
    close(fd);

    return EXIT_SUCCESS;
}
