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
 * (Lưu ý: Dùng tối đa 10 thread để ghi)
 * 
 * Answer:
 * - Dùng nhiều thread chậm hơn là dùng 1 thread để ghi file
*/

int fd; // File descriptor
char *str = "A";
pthread_t tid[10];

void write_to_file() {
    // Write to file
    pthread_t tid = pthread_self();
    for (int i = 0; i < 10000; i++) {
        // lseek(fd, 0, SEEK_END);
        write(fd, str, strlen(str));
    }
    printf("[Thread %ld] Finished writing\n", tid);
    pthread_exit(NULL);
}

int main() {

    // Define variables
    char filename[] = "file.txt";

    // Open the file
    fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        printf("[Error] Failed to open file\n");
        return 1;
    }

    // Create 10 threads to write to file
    time_t start_time = time(NULL);
    for (int i = 0; i < 10; i++) {
        int ret = pthread_create(&tid[i], NULL, &write_to_file, NULL); // Create thread
        if (ret != 0) {
            printf("[Error] Failed to create thread. Error number=%d\n", ret);
        }
    }
    // Wait for all threads to finish
    for (int i = 0; i < 10; i++) {
        pthread_join(tid[i], NULL);
    }
    time_t end_time = time(NULL);
    printf("Time: %ld\n", end_time - start_time);
    
    return 0;

}
