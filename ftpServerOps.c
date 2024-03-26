#include "csapp.h"
#include "ftpServerOps.h"
void sendfile(int clientfd){
    char* filename;
    Rio_readn(clientfd, filename, MAXBUF);
    int fd = Open(filename,O_RDONLY,S_IRUSR|S_IWUSR);
    struct stat fileinfo;
    fstat(fd, &fileinfo); 
    char* file_buffer = malloc(fileinfo.st_size);
    Rio_writen(clientfd, &fileinfo.st_size,sizeof(fileinfo.st_size));
    if(rio_readn(fd, file_buffer, fileinfo.st_size) <= 0){
        perror("Reading Error");
    }
    if(rio_writen(clientfd, file_buffer, fileinfo.st_size)<=0){
        perror("Writing Error");
    }

}