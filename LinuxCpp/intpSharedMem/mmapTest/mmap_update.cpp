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
    struct stat fileStatus;
    if (argc != 3) {
        std::cout << "Usage: mmap_read_write <filename> <message>" << std::endl;
        exit(-1);
    }

    size_t length = strlen(argv[2]) + 1;
    int fd = open(argv[1], O_RDWR, PERM);

    // get file size
    fstat(fd, &fileStatus);
    size_t fsize = fileStatus.st_size;
    std::cout << "File: " << argv[1] << " <- size: " << fsize << ": " << length << std::endl;

    // mapping
    void *addr = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    std::cout << "Read: " << (char*)addr << std::endl;

    memcpy(addr, argv[2], strlen(argv[2]));
    std::cout << "After update: " << (char*)addr << std::endl;

    // expanding the file size
    if (fsize < length) {
        ftruncate(fd, length); // Resize the file
        fsize = length; // Update fsize to new length
    }

    msync(addr, fsize, MS_SYNC); // Sync memory to file
    munmap(addr, fsize); // ummapping
    close(fd);

    return EXIT_SUCCESS;
}
