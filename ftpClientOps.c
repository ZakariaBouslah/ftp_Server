#include "csapp.h"
#include "ftpClientOps.h"
void recieve_file(char* filename, int clientfd){



    int filename_size = sizeof(filename);
    if ((rio_writen(clientfd,&filename_size,sizeof(int)))<=0){
        perror("Client writing filename_size error");
    }



    if ((rio_writen(clientfd,filename,sizeof(filename)))<=0){
        perror("Client writing filename error");
    }



    int filesize;
    if(rio_readn(clientfd,&filesize, sizeof(int))<=0){
        perror("Client reading filesize Error");
    }



    char* file_buffer = malloc(filesize);
    if(rio_readn(clientfd,&file_buffer, filesize)<=0){
        perror("Client Reading File Error");
    }



    int fd =Open(filename,O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR);
    if((rio_writen(fd, file_buffer, filesize))<=0){
        perror("Client writing file error");
    }

    Close(fd);
}