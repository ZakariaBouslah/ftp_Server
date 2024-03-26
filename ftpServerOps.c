#include "csapp.h"
#include "ftpServerOps.h"
void sendfile(int clientfd){



    int filename_size;
    if((rio_readn(clientfd, &filename_size, sizeof(int))) <=0){
        perror("Server filename_size read error");
    }



    char* filename=malloc(filename_size);
    if((rio_readn(clientfd, filename, filename_size)) <=0){
        perror("Server filename read error");
    }



    int fd = Open(filename,O_RDONLY,S_IRUSR|S_IWUSR);
    struct stat fileinfo;
    fstat(fd, &fileinfo); 
    int filesize = (int) fileinfo.st_size;
    char* file_buffer = malloc(filesize);
    if((rio_writen(clientfd, &filesize,sizeof(int)))<=0){
        perror("Server filesize writing error");
    }
    
    
    if(rio_readn(fd, file_buffer, filesize) <= 0){
        perror("Server reading file Error");
    }
    
    
    if(rio_writen(clientfd, file_buffer, fileinfo.st_size)<=0){
        perror("Server writing file Error");
    }
    Close(fd);
}