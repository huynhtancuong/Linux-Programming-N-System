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
 * Assignment 1:
 * Tạo file filesystem.txt và ghi một đoạn dữ liệu bất kì. 
 * Thực hiện ghi ra màn hình các thông tin: 
 *  - Loại file, 
 *  - Tên file, 
 *  - thời gian chỉnh sửa file lần cuối, 
 *  - kích thước.
*/

void print_file_type(struct stat st) {
    if (S_ISDIR(st.st_mode)) {
        printf("[Info] File is directory\n");
    } else if (S_ISREG(st.st_mode)) {
        printf("[Info] File is regular file\n");
    } else if (S_ISCHR(st.st_mode)) {
        printf("[Info] File is character device\n");
    } else if (S_ISBLK(st.st_mode)) {
        printf("[Info] File is block device\n");
    } else if (S_ISFIFO(st.st_mode)) {
        printf("[Info] File is FIFO\n");
    } else if (S_ISLNK(st.st_mode)) {
        printf("[Info] File is symlink\n");
    } else if (S_ISSOCK(st.st_mode)) {
        printf("[Info] File is socket\n");
    }
}

int main() {

    // Define variables
    char filename[] = "filesystemt.txt";

    // Open the file
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        printf("[Error] Failed to open file\n");
        return 1;
    }

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


    // Print the info of the file
    // https://en.wikipedia.org/wiki/Stat_(system_call)
    struct stat st;
    if (fstat(fd, &st) == -1) {
        printf("[Error] Failed to get file info\n");
        return 1;
    }
    printf("[Info] File name:\t %s\n", filename);
    print_file_type(st);
    printf("[Info] Last modified:\t %s\n", ctime(&st.st_mtime));
    printf("[Info] File size:\t %ld\n", st.st_size);

    // Close the file
    close(fd);
    return 0;

}