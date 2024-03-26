#include "csapp.h"
#include "ftpServerOps.h"
#define MAX_NAME_LEN 256
#define NB_PROC 10
#define PORT 2121
pid_t tableau_fils[NB_PROC];

int listenfd, connfd;


void SIGCHLD_handler(int sig){
    while(waitpid(-1, NULL, 0)>=0){
        sleep(1);
    }
}
void SIGINT_handler(int sig){
    for (size_t i = 0; i < NB_PROC; i++){
        kill(tableau_fils[i], SIGINT);    
    }
    while(waitpid(-1, NULL, 0)>=0){
        sleep(1);
    }
    Close(listenfd);
    printf("\nEverything closed, Goodbye World\n");
    exit(0);
}

void child_SIGINT_handler(int sig){
    Close(listenfd);
    if(connfd != -1)
        Close(connfd);
    exit(0);
}


void creer_fils(){
    pid_t pidfils;
    for (size_t i = 0; i < NB_PROC; i++){
        if((pidfils = Fork())==0){
            break;
        }
        else{
            tableau_fils[i] = pidfils;
        }
    }
    
}



/* 
 * Note that this code only works with IPv4 addresses
 * (IPv6 is not supported)
 */
int main(int argc, char **argv)
{
    socklen_t clientlen;
    struct sockaddr_in clientaddr;
    char client_ip_string[INET_ADDRSTRLEN];
    char client_hostname[MAX_NAME_LEN];
    
    
    listenfd = Open_listenfd((PORT));
    
    pid_t pid_pere = getpid();

    
    creer_fils();
    
    if(getpid()==pid_pere){
        Signal(SIGCHLD, SIGCHLD_handler);
        Signal(SIGINT, SIGINT_handler);
        pause();
        
    }
    else{
        
        Signal(SIGINT, child_SIGINT_handler);
        while (1) {

            
            while((connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen))<0);
            
            /* determine the name of the client */
            Getnameinfo((SA *) &clientaddr, clientlen,client_hostname, MAX_NAME_LEN, 0, 0, 0);
            
            /* determine the textual representation of the client's IP address */
            Inet_ntop(AF_INET, &clientaddr.sin_addr, client_ip_string,INET_ADDRSTRLEN);
            
            printf("server connected to %s (%s)\n", client_hostname,
                client_ip_string);
            sendfile(connfd);
            Close(connfd);
        }
    }

    
}
