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
 * Viết một chương trình A tạo ra một tiến trình con B, in ra PID và PPID của chúng. 
 * Sử dụng system waitpid() để lấy được trạng thái kết thúc của tiến con B.
*/

void child_process();
void parent_process();

int main() {

    pid_t pid;

    pid = fork();
    switch (pid)
    {
    case 0:
        child_process();
        break;
    case -1:
        printf("[Error] Failed to fork\n");
        break;
    default:
        parent_process();
        break;
    }
    
    return 0;

}

void child_process() {
    printf("[Child] PID = %d, PPID = %d\n", getpid(), getppid());
    sleep(2);
    printf("[Child] Terminated\n");
    exit(1);
}

void parent_process() {
    int child_exit_status;
    if (wait(&child_exit_status) == -1) {
        printf("[Error] Failed to wait\n");
    }
    printf("[Parent] PID = %d, CHILD_EXIT_STATUS = %d\n", getpid(), child_exit_status);
}