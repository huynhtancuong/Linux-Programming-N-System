#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 100
#define SOCK_PATH "./sock_dgram"
#define EXIT_FAILURE 1

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* Chức năng chat */
void chat_func(int server_fd, struct sockaddr_un server_address)
{
    int numb_write, numb_read;
    char recvbuff[BUF_SIZE];
    char sendbuff[BUF_SIZE];
    while (1) {
        memset(sendbuff, '0', BUF_SIZE);
        memset(recvbuff, '0', BUF_SIZE);
        printf("Please enter the message : ");
        fgets(sendbuff, BUF_SIZE, stdin);

        /* Gửi thông điệp tới server bằng hàm write */
        numb_write = sendto(server_fd, sendbuff, sizeof(sendbuff), 0, (struct sockaddr *)&server_address, sizeof(struct sockaddr_un));
        if (numb_write == -1)     
            handle_error("write()");
        if (strncmp("exit", sendbuff, 4) == 0) {
            printf("Client exit ...\n");
            break;
        }
		
        /* Nhận thông điệp từ server bằng hàm read */
        numb_read = recvfrom(server_fd, recvbuff, BUF_SIZE, 0, NULL, NULL);
        if (numb_read < 0) 
            handle_error("read()");
        if (strncmp("exit", recvbuff, 4) == 0) {
            printf("Server exit ...\n");
            break;
        }

        printf("\nMessage from Server: %s\n",recvbuff);   
    }
    close(server_fd); /*close*/ 
}

int main(int argc, char *argv[])
{    
	struct sockaddr_un server_address;
	int fd, optval; // file description
	size_t msgLen;
	ssize_t numBytes;
	char message[1000];
	// char response[BUF_SIZE];

	fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (fd == -1) 
		handle_error("Failed to create socket.\n");
	
	// clear the memory
	memset(&server_address, 0, sizeof(struct sockaddr_un));
	server_address.sun_family = AF_UNIX;
	strncpy(server_address.sun_path, SOCK_PATH, sizeof(server_address.sun_path)-1);

	optval = 1; // what is it?
	setsockopt(fd, SOL_SOCKET, SO_PASSCRED, &optval, sizeof(optval));

	chat_func(fd, server_address);

	// msgLen = strlen(message);
	// if (sendto(fd, message, msgLen, 0, (struct sockaddr *)&server_address, sizeof(struct sockaddr_un)) != msgLen)
	// 	handle_error("Failed to send message.\n");
	// numBytes = recvfrom(fd, response, BUF_SIZE, 0, NULL, NULL);
	// if (numBytes == -1)
	// 	handle_error("Failed to receive response.\n");
	// else
	// 	printf("Response: %s\n", response);

	return 0;

}
