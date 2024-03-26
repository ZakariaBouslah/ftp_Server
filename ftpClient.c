#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include "ftpClientOps.h"
#define PORT 2121
#define MAX_BUF 256 

int main(int argc, char **argv){
    int clientfd;
    char *host;
    rio_t rio;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <host>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    clientfd = Open_clientfd(host, PORT);
    printf("client connected to server OS\n"); 
    char filename[MAX_BUF];
    scanf("%s",filename);
    recieve_file(filename, clientfd);
    Close(clientfd);
}

