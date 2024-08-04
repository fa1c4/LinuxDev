#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    int sockfd;
    if (argc != 3) {
        std::cout << "Usage:updClient <server port> <Message>" << std::endl;
        exit(-1);
    }

    char bufferSend[512];
    char bufferRecv[512];
    memset(bufferSend, '\0', sizeof(bufferSend));
    memset(bufferRecv, '\0', sizeof(bufferRecv));
    memcpy(bufferSend, argv[2], strlen(argv[2]));

    // step1: create the socket
    // int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cout << "cannot create socket" << std::endl;
        exit(-2);
    }

    // step2: Identify the socket
    struct sockaddr_in servAddr, cliAddr;
    socklen_t sLen = sizeof(servAddr);
    socklen_t cLen = sizeof(cliAddr);

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(std::stoi(argv[1]));
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // step3: send a message through client
    ssize_t sByte = sendto(sockfd, bufferSend, sizeof(bufferSend), 0, (struct sockaddr*)&servAddr, sLen);
    std::cout << "[" << sByte << "] Bytes Sent: " << bufferSend << std::endl;

    // step4: recv a message from server
    ssize_t rByte = recvfrom(sockfd, bufferRecv, sizeof(bufferRecv), 0, (struct sockaddr*)&cliAddr, &cLen);
    std::cout << "[" << rByte << "] Bytes Rcvd: " << bufferRecv << std::endl;

    // step5: close the socket
    close(sockfd);
    exit(0);
}
