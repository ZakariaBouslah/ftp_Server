#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include "ftpClientOps.h"
#define PORT 2120
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
    while(1){
        operation op;
        op = read_command();
        send_command(op,clientfd);
        switch (op){
        case GET:
            fflush(stdin);
            scanf("%s",filename);

            printf("filename :%s.\n",filename);
            recieve_file(filename, clientfd);
            filename[0]='\0';
            break;
        case CLOSE:
            Close(clientfd);
            exit(0);
            break;
        default:
            printf("Unknown command\n");
            break;
        }
    }
    
    
}

