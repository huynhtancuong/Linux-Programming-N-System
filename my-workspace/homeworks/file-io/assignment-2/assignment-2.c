#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/sysmacros.h>

/**
 * Assignment 2: Viết một chương trình mở một file bất kì và sử dụng cờ O_APPEND, 
 * sau đó thực hiện seek về đầu file rồi ghi một vài dữ  liệu vào file đó. 
 * Dữ liệu sẽ xuất hiện ở vị trí nào của file và tại sao lại như vậy?
 * 
 * Answer:
 * Khi thực hiện mở file bằng Flag APPEND, thì mặc định con trỏ file SEEK_SET sẽ nằm ở cuối file.
 * Vậy nên khi thực hiện việc ghi dữ liệu, thì dữ liệu sẽ được ghi vào cuối file chứ không phải ở đầu file.
*/


int main() {

    // Define variables
    char filename[] = "filesystemt.txt";

    // Open the file
    int fd = open(filename, O_APPEND | O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        printf("[Error] Failed to open file\n");
        return 1;
    }

    // Seek to the begin of the file
    lseek(fd, 0, SEEK_SET);

    // Write to the file
    char str[] = "hello world\n";
    size_t len = strlen(str);
    int write_status = write(fd, str, len);
    if (write_status == -1) {
        printf("[Error] Failed to write to file\n");
        return 1;
    }
    else {
        printf("[Info] Successfully wrote to file\n");
    }



    // Close the file
    close(fd);
    return 0;

}