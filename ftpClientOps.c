#include "csapp.h"
#include "ftpClientOps.h"
#include <string.h>
#define CLIENT_DIR "./ftpClientdir/" 
#define BLOCK_SIZE 4096 



void send_command(operation op, int clientfd){
    if ((rio_writen(clientfd,&op,sizeof(int)))<=0){
        perror("Client Error while sending command");
    }
    
}

operation read_command(){
    char command[4];
    scanf("%4s",command);
    fflush(stdin);
   
        printf("command : %s\n",command);
        if (strcmp(command,"get")==0){
            return GET;
        }
        else if(strcmp(command,"bye")==0){
            return CLOSE;
        }
    return WRONG;
}


void recieve_file(char* filename, int clientfd){


    int filename_size = strlen(filename);
    if ((rio_writen(clientfd,&filename_size,sizeof(int)))<=0){
        perror("Client writing filename_size error");
        return;
    }

    if ((rio_writen(clientfd,filename,filename_size))<=0){
        perror("Client writing filename error");
        return;
    }


   int exist_flag;
    if (Rio_readn(clientfd, &exist_flag, sizeof(int)) <= 0) {
        perror("Client reading exist_flag Error");
        return;
    }


    if (!exist_flag) {
        printf("File requested doesn't exist\n");
        return;
    }

    int filesize;
    if(rio_readn(clientfd,&filesize, sizeof(int))<=0){
        perror("Client reading filesize Error");
        return;
    }
    printf("file size: %d bytes\n",filesize);


    char *newfilename = malloc(strlen(filename) + strlen("clientCopy_") + strlen(CLIENT_DIR) + 1);
    strcpy(newfilename, CLIENT_DIR);
    strcat(newfilename,"clientCopy_");
    strcat(newfilename, filename);
    

    int fd =Open(newfilename,O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR);

    char buffer[BLOCK_SIZE];
    int bytes_received;
    int total_bytes_received = 0;
    while (total_bytes_received < filesize) {
        int bytes_to_receive = BLOCK_SIZE < (filesize - total_bytes_received) ? BLOCK_SIZE : (filesize - total_bytes_received);        bytes_received = rio_readn(clientfd, buffer, bytes_to_receive);
        if (bytes_received <= 0) {
            perror("Client reading file error");
            Close(fd);
            return;
        }
        if (rio_writen(fd, buffer, bytes_received) <= 0){
            perror("Client writing file error");
            Close(fd);
            return;
        }
        total_bytes_received += bytes_received;
    }
    printf("file %s was recieved in %s\n",filename,newfilename);
    Close(fd);
}