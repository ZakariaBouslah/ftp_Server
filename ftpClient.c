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
    char command[4];
    while(1){
        scanf("%s",command);
        printf("command : %s\n",command);
        
        

        if (strcmp(command,"get")==0){
            scanf("%s",filename);
            printf("filename :%s.\n",filename);
            recieve_file(filename, clientfd);
        }
        else if(strcmp(command,"bye")==0){
            printf("client is done\n");
            Close(clientfd);
            break;
        }
        else{
             printf("unknown command\n");
        }
    }
    
    
}

