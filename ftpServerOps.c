#include "csapp.h"
#include "ftpServerOps.h"
#include <string.h>
#define SERVER_DIR "./ftpServerdir/"

operation recieve_command(int clientfd){
    operation op;
    if((rio_readn(clientfd, &op, sizeof(int)))<=0){
        fprintf(stderr,"Client disconnected unexpectedly\n");
        return ERR;
    }
    return op;
}

void sendfile(int clientfd){


    char* filename=NULL;
    char* file_buffer=NULL;

    int filename_size;
    if((rio_readn(clientfd, &filename_size, sizeof(int))) <=0){
        perror("Server filename_size read error");
        goto error;
    }

    filename = malloc(filename_size);
    if((rio_readn(clientfd, filename, filename_size)) <=0){
        perror("Server filename read error");
        goto error;
    }
    filename[filename_size]='\0';
    char* absolute_filename=malloc(strlen(SERVER_DIR)+filename_size);
    strcpy(absolute_filename, SERVER_DIR);
    strcat(absolute_filename, filename);
    printf("the client requested file: %s of namesize %d\n",absolute_filename,filename_size);

    int fd;
    int exist_flag;
    if( (fd = open(absolute_filename,O_RDONLY,S_IRUSR|S_IWUSR))<=0){
        perror("No such file in directory");
        exist_flag = 0;
        Rio_writen(clientfd, &exist_flag, sizeof(int));
        goto error;
    }
    exist_flag = 1;
    Rio_writen(clientfd, &exist_flag, sizeof(int));
    
    struct stat fileinfo;
    fstat(fd,&fileinfo);

    int filesize = (int) fileinfo.st_size;

    printf("file size:%d\n",filesize);
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
    if(filename)
        free(filename);
    if(file_buffer)
        free(file_buffer);
    if(absolute_filename)
        free(absolute_filename);
    return;
}