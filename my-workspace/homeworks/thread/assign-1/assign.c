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
#include <sys/wait.h>

/**
 * Viết một chương trình ghi 100000 kí tự A vào file test.txt 
 * và tính toán thời gian thực hiện xong công việc này thông qua việc sử dụng lệnh time. 
 * (Lưu ý: chỉ dùng duy nhất main thread)
*/


int main() {

    // Define variables
    char filename[] = "file.txt";

    // Open the file
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        printf("[Error] Failed to open file\n");
        return 1;
    }

    // Write to file
    time_t start_time = time(NULL);
    char *str = "A";
    for (int i = 0; i < 100000; i++) {
        write(fd, str, strlen(str));
    }
    time_t end_time = time(NULL);
    printf("Time: %ld\n", end_time - start_time);
    
    return 0;

}
