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
 * Từ kiến thức đã học, sử dụng SIGCHLD để ngăn ngừa việc hình thành zombie process.
 * Khi một child process kết thúc, nó sẽ gửi signal nào tới parent? signal value bằng bao nhiêu?
 * 
 * Answer:
 * - Khi một child process kết thúc, nó sẽ gửi signal SIGCHLD tới parent process. Signal này có giá trị bằng 17.
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
    sleep(1);
    printf("[Child] Terminated\n");
    exit(1);
}

void wait_for_child_callback(int signum) {
    int child_exit_status;
    if (wait(&child_exit_status) == -1) {
        printf("[Error] Failed to wait\n");
    }
    printf("[Parent] PID = %d, CHILD_EXIT_STATUS = %d, signum = %d\n", getpid(), child_exit_status, signum);
}

void parent_process() {
    signal(SIGCHLD, wait_for_child_callback);
    for (int i = 0; i < 10; i++) {
        printf("[Parent] Counting: %d\n", i);
        sleep(1);
    }
}