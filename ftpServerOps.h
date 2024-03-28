void sendfile(int clientfd);
typedef enum operations {GET , CLOSE, WRONG, ERR} operation;
operation recieve_command(int clientfd);
