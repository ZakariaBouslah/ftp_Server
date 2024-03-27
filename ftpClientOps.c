#include "csapp.h"
#include "ftpClientOps.h"
#include <string.h>
#define CLIENT_DIR "./ftpClientdir/" 
void recieve_file(char* filename, int clientfd){


    printf("SLAY\n");
    int filename_size = strlen(filename);
    if ((rio_writen(clientfd,&filename_size,sizeof(int)))<=0){
        perror("Client writing filename_size error");
        exit(1);
    }
    printf("i send the size of the name,%d\n",filename_size);

    if ((rio_writen(clientfd,filename,filename_size))<=0){
        perror("Client writing filename error");
        exit(1);
    }
    printf("i send the  name,%s\n",filename);

    int exist_flag;
    if (Rio_readn(clientfd, &exist_flag, sizeof(int)) <= 0) {
        perror("Client reading exist_flag Error");
        exit(1);
    }
    printf("i got the exist flag%d\n",exist_flag);

    if (!exist_flag) {
        printf("File requested doesn't exist\n");
        exit(1);
    }

    int filesize;
    if(rio_readn(clientfd,&filesize, sizeof(int))<=0){
        perror("Client reading filesize Error");
        exit(1);
    }
    printf("file size: %d bytes\n",filesize);


    char* file_buffer = malloc(filesize);
    if(rio_readn(clientfd,file_buffer,filesize)<=0){
        perror("Client Reading File Error");
        exit(1);
    }

    char *newfilename = malloc(strlen(filename) + strlen("_ClientCopy") + 1);
    char* absolute_path;
    strcpy(newfilename, "clientCopy_");
    strcat(newfilename, filename);
    strcpy(absolute_path,CLIENT_DIR);
    strcat(absolute_path,newfilename);
    strcpy(newfilename,absolute_path);
    int fd =Open(newfilename,O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR);
    if((rio_writen(fd, file_buffer, filesize))<=0){
        perror("Client writing file error");
        exit(1);
    }
    printf("file %s was recieved in %s\n",filename,newfilename);
    Close(fd);
}