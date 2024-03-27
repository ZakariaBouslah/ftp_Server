#include "csapp.h"
#include "ftpServerOps.h"
#include <string.h>
#define SERV_DIR "./ftpServerdir/"

void sendfile(int clientfd){


    char* filename=NULL;
    char* file_buffer=NULL;

    int filename_size;
    if((rio_readn(clientfd, &filename_size, sizeof(int))) <=0){
        perror("Server filename_size read error");
        goto error;
    }

    char* absolute_path;    
    strcpy(absolute_path,SERV_DIR);
    filename=malloc(filename_size+strlen(absolute_path)+1);
    if((rio_readn(clientfd, filename, filename_size)) <=0){
        perror("Server filename read error");
        goto error;
    }

    printf("the client requested file: %s\n",filename);

    
    printf("%s\n",absolute_path);
    strcat(absolute_path,filename);
    strcpy(filename,absolute_path);
    int fd,exist_flag;
    if( fd = open(filename,O_RDONLY,S_IRUSR|S_IWUSR)<=0){
        perror("No such file in directory");
        exist_flag = 0;
        Rio_writen(clientfd, &exist_flag, sizeof(int));
        goto error;
    }
    exist_flag = 1;
    Rio_writen(clientfd, &exist_flag, sizeof(int));

    struct stat fileinfo;
    

    int filesize = (int) fileinfo.st_size;
    file_buffer = malloc(filesize);
    if((rio_writen(clientfd, &filesize,sizeof(int)))<=0){
        perror("Server filesize writing error");
        goto error;
    }
    
    
    if(rio_readn(fd, file_buffer, filesize) <= 0){
        perror("Server reading file Error");
        goto error;
    }
    
    
    if(rio_writen(clientfd, file_buffer, fileinfo.st_size)<=0){
        perror("Server writing file Error");
        goto error;
    }
    Close(fd);


error:
    Close(clientfd);
    clientfd = -1;
    if(filename)
        free(filename);
    if(file_buffer)
        free(file_buffer);
    return;
}