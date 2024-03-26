#include "csapp.h"
#include "ftpClientOps.h"
#include <string.h>
void recieve_file(char* filename, int clientfd){



    int filename_size = strlen(filename);
    if ((rio_writen(clientfd,&filename_size,sizeof(int)))<=0){
        perror("Client writing filename_size error");
    }
    printf("%d\n",filename_size);


    if ((rio_writen(clientfd,filename,filename_size))<=0){
        perror("Client writing filename error");
    }



    int filesize;
    if(rio_readn(clientfd,&filesize, sizeof(int))<=0){
        perror("Client reading filesize Error");
    }
    printf("file recieved size  : %d\n",filesize);


    char* file_buffer = malloc(filesize);
    if(rio_readn(clientfd,file_buffer,filesize)<=0){
        perror("Client Reading File Error");
    }

    char *newfilename = malloc(strlen(filename) + strlen("_ClientCopy") + 1);
    
    strcat(newfilename, "clientCopy_");
    strcpy(newfilename, filename);

    int fd =Open(newfilename,O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR);
    if((rio_writen(fd, file_buffer, filesize))<=0){
        perror("Client writing file error");
    }
    printf("file %s was recieved in %s",filename,newfilename);
    Close(fd);
}