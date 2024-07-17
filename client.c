#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include this header for read and write

#define MAXLINESIZE 100
#define SERV_PORT 5555

int main(int argc, char** argv) {
    int connectsd;
    char sendBuffer[MAXLINESIZE + 1];
    char recvBuffer[MAXLINESIZE + 1];
    struct sockaddr_in servaddr;
    int noBytesRead = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s IP-Address\n", argv[0]);
        exit(-1);
    }

    if ((connectsd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Cannot create socket\n");
        exit(-1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        fprintf(stderr, "Error in inet_pton\n");
        exit(-1);
    }

    if (connect(connectsd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        fprintf(stderr, "Error in connect\n");
        exit(-1);
    }

    while (fgets(sendBuffer, MAXLINESIZE, stdin) != NULL) {
        write(connectsd, sendBuffer, strlen(sendBuffer));
        if ((noBytesRead = read(connectsd, recvBuffer, sizeof(recvBuffer) - 1)) < 0) {
            fprintf(stderr, "Error in read\n");
            exit(-1);
        }
        recvBuffer[noBytesRead] = '\0';
        fprintf(stdout, "%s\n", recvBuffer);
    }
    return 0;
}

// run server:  gcc -o server server.c
// 						./server
            
// run client : gcc -0 client client.c
// 							./client 127.0.0.1