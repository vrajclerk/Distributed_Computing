#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define MAXLINESIZE 100
#define SERV_PORT 5555

int listensd, clientsd;
char buffer[MAXLINESIZE + 1];
struct sockaddr_in servaddr;

void processClient(int);

int main() {
    if ((listensd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Cannot create socket\n");
        exit(-1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listensd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        fprintf(stderr, "Error in bind\n");
        exit(-1);
    }

    if (listen(listensd, 5) < 0) {
        fprintf(stderr, "Error in listen\n");
        exit(-1);
    }

    for (;;) {
        clientsd = accept(listensd, (struct sockaddr*)NULL, NULL);
        if (fork() == 0) {
            close(listensd);
            processClient(clientsd);
            close(clientsd);
            exit(0);
        }
        close(clientsd);
    }
    return 0;
}

void processClient(int clientsd) {
    int noBytesRead;
    while ((noBytesRead = read(clientsd, buffer, sizeof(buffer))) > 0) {
        write(clientsd, buffer, noBytesRead);
    }
}
