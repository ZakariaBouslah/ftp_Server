#include "csapp.h"
#include "ftpClientOps.h"
void recieve_file(char* filename, int clientfd){
    Rio_writen(clientfd,filename,sizeof(filename));
    size_t filesize;
    if(rio_readn(clientfd,&filesize, MAXBUF)<=0){
        perror("Size Error");
    }
    char* file_buffer = malloc(filesize);
    if(rio_readn(clientfd,&file_buffer, filesize)<=0){
        perror("Client Reading Error");
    }
    int fd =Open(filename,O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR);
    Rio_writen(fd, file_buffer, filesize);
}