// This is a client program that join a group chat 

// Incluce libs
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define USERNAMESIZE 10
#define BUFF_SIZE 20

int main(int argc, char **argv) {

    char username[USERNAMESIZE];
    int fds[2];
    char buff[BUFF_SIZE];


    // Check usage
    if (argc!=3) {
        printf("Usage: %s <server in FIFO> <server out FIFO>.\n", argv[0]);
        return -1;
    }
    // Open the FIFO for writing
    char* serverin = &argv[1];
    fds[1] = open(argv[1], O_WRONLY | O_NONBLOCK);
    if (fds[1] == -1) {
        fprintf(stderr, "[Error] Error occured when opening FIFO for writing: %s\n", strerror(errno));
        return -1;
    }
    // Open the FIFO for reading
    fds[0] = open(argv[2], O_RDONLY | O_NONBLOCK);
    if (fds[0] == -1) {
        fprintf(stderr, "[Error] Error occured when opening FIFO for reading: %s\n", strerror(errno));
        return -1;
    }

    // Ask the user their username
    printf("Enter your username: ");
    fflush(stdin);
    scanf("%s", username);
    printf("Connecting to the server with username \"%s\"...\n", username);

    // Write a request to serverin FIFO
    strcpy(buff, "REQUEST");
    if (write(fds[1], buff, BUFF_SIZE) == -1) {
        fprintf(stderr, "[Error] Error occured when opening FIFO for writing: %s\n", strerror(errno));
        return -1;
    } else fprintf(stdout, "Writed request sucessfully.");
    

    // Then wait for response of the server
        // response = read(serverout);
    // If response is don't accepted the connection then print error and exit
        // printf("Connection error.");
        // return -1;
    // If the response if accepted the connection
        // Create a new FIFO with the name CLIENT + getpid()
        // 
}
