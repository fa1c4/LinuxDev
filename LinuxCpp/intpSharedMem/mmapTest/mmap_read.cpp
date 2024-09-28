#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    struct stat fileStatus;
    if (argc != 2) {
        std::cout << "Usage: mmap_read <filename>" << std::endl;
        exit(-1);
    }

    int fd = open(argv[1], O_RDONLY);
    fstat(fd, &fileStatus);
    size_t fsize = fileStatus.st_size;
    std::cout << "File: " << argv[1] << " <- size: " << fsize << std::endl;

    void *addr = mmap(NULL, fsize, PROT_READ, MAP_SHARED, fd, 0);
    std::cout << (char*)addr << std::endl;
    
    // unmmap
    munmap(addr, fsize);
    close(fd);

    return EXIT_SUCCESS;
}
