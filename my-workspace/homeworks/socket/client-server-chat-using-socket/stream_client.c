#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>     //  Chứa cấu trúc cần thiết cho socket. 
#include <netinet/in.h>     //  Thư viện chứa các hằng số, cấu trúc khi sử dụng địa chỉ trên internet
#include <arpa/inet.h>
#include <unistd.h>

#define BUFF_SIZE 256
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]) {
    int portno; // port number
    int server_fd; // file description of the server
    struct sockaddr_in serv_addr; // create a socket
    memset(&serv_addr, '0', sizeof(serv_addr));

    /* Read port number from argument */
    if (argc <3) {
        printf("Usage: ./client <server address> <port number>\n");
        exit(1);
    }
    portno = atoi(argv[2]);

    // Initialize server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(portno); // convert host to network the port number
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == -1 ) // convert server ip from string to binary format
        handle_error("inet_pton()");

    // Initialize socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) 
        handle_error("socket()");
    
    // Connect to server
    if (connect(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("connect()");
    
    // Handle the socket
    socket_handler(server_fd);

    return 0;

}

void socket_handler(int server_fd) {
    chat_function(server_fd);
}

void chat_function(int server_fd) {
    int numb_write, numb_read;
    char recvbuff[BUFF_SIZE], sendbuff[BUFF_SIZE]; // buffer for receiving and sending
    int status = 1; // 1 for running, 0 for stopping
    while (status) {
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);
        printf("Please enter the message: ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        // Send message to server using the write function
        if (write(server_fd, sendbuff, sizeof(sendbuff)) == -1 ) {
            handle_error("write()");
        }
        if (strncmp("exit", sendbuff, 4) == 0) { // check if client want to exit
            printf("Client exit...\n");
            status = 0;
            break;
        }

        // Receiving message from the server using read function
        if (read(server_fd, recvbuff, sizeof(recvbuff)) == -1) {
            handle_error("read()");
        }
        if (strncmp("exit", recvbuff, 4) == 0) { // check if server want to exit
            printf("Server exit...\n");
            status = 0;
            break;
        }
        printf("Message from server: %s\n", recvbuff);
    }
    close(server_fd);
}