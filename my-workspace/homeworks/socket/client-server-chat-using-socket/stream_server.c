#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>     //  Chứa cấu trúc cần thiết cho socket. 
#include <netinet/in.h>     //  Thư viện chứa các hằng số, cấu trúc khi sử dụng địa chỉ trên internet
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_BACKLOG 5
#define BUFF_SIZE 256
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)



int main(int argc, char *argv[]) {
    int port_no, len, opt;
    int server_fd, new_socket_fd;
    struct sockaddr_in serv_addr, client_addr;

    /* Read port number from commandline arguments */
    if (argc < 2) {
        printf("Usage: ./server <port number> \n");
        exit(EXIT_FAILURE);
    }
    port_no = atoi(argv[1]);

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    // Create the socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) 
        handle_error("socket()");
    
    // Handle error "address already in use"
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        handle_error("setsockopt()");  
    
    // Create server address 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY; // accept any address 

    // Binding the socket to server address
    if (bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("bind()");
    
    // Set max queue to 5 client
    if (listen(server_fd, LISTEN_BACKLOG) == -1 )
        handle_error("listen()");
    
    // Get the client information
    len = sizeof(client_addr);

    while (1) {
        printf("Server is listening at port: %d \n ... \n", port_no);
        new_socket_fd = accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t *)&len);
        if (new_socket_fd == -1)
            handle_error("accept()");
        
        printf("Client connected.");
        socket_handler(new_socket_fd);
    }
    close(server_fd);
    return 0;
}

void socket_handler(int socket_fd) {
    chat_func(socket_fd);
}

void chat_func(int new_socket_fd)
{       
    int numb_read, numb_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];
	
    while (1) {        
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);

        /* Đọc dữ liệu từ socket */
        /* Hàm read sẽ block cho đến khi đọc được dữ liệu */
        numb_read = read(new_socket_fd, recvbuff, BUFF_SIZE);
        if(numb_read == -1)
            handle_error("read()");
        if (strncmp("exit", recvbuff, 4) == 0) {
            system("clear");
            break;
        }
        printf("\nMessage from Client: %s\n", recvbuff);

        /* Nhập phản hồi từ bàn phím */
        printf("Please respond the message : ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        /* Ghi dữ liệu tới client thông qua hàm write */
        numb_write = write(new_socket_fd, sendbuff, sizeof(sendbuff));
        if (numb_write == -1)
            handle_error("write()");
        
        if (strncmp("exit", sendbuff, 4) == 0) {
            system("clear");
            break;
        }

        sleep(1);
    }
    close(new_socket_fd);
}