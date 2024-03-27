#include "csapp.h"
#include "ftpServerOps.h"
#define MAX_NAME_LEN 256
#define NB_PROC 2
#define PORT 2121
pid_t tableau_fils[NB_PROC];

int listenfd, connfd;


void SIGCHLD_handler(int sig){
    while(waitpid(-1, NULL, 0)>=0){
        sleep(1);
    }
}
void SIGINT_handler(int sig){
    Signal(SIGCHLD,SIG_IGN);
    close(listenfd);
    for (size_t i = 0; i < NB_PROC; i++){
        kill(tableau_fils[i], SIGINT); 
        while(waitpid(tableau_fils[i], NULL, 0)==0)
            sleep(1);   
    }
    printf("\nEverything closed, Goodbye World\n");
    exit(0);
}

void child_SIGINT_handler(int sig){
    close(listenfd);
    if(connfd != -1)
        printf("\nClosing children socket\n");
        connfd = -1;
        close(connfd);
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
            printf("server connected to client\n");
            sendfile(connfd);
            connfd = -1;
        }
    }

    
}
