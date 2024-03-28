void recieve_file(char* filename, int clientfd);
typedef enum operations {GET , CLOSE, WRONG, ERR} operation;
operation read_command();
void send_command(operation op, int clientfd);
