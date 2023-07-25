#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/**
 * Viết chương trình block tín hiệu SIGINT và sau đó in ra signal mask của process hiện tại.
*/


int main() {
  	sigset_t new_set, old_set;
	
	sigemptyset(&new_set);
	sigemptyset(&old_set);

	sigaddset(&new_set, SIGINT);
 	printf("new_set is %x\n", new_set);
	/**
	 * sigprocmask return value:
	 * A 0 value indicated that the call succeeded.  
	 * A -1 return value indicates an error occurred and
     errno is set to indicated the reason.
	*/
	if (sigprocmask(SIG_SETMASK, &new_set, &old_set) == 0) {
		if (sigismember(&new_set, SIGINT) == 1 ) {
			printf("SIGINT exist\n");
		} else if (sigismember(&new_set, SIGINT) == 0) {
			printf("SIGINT does not exist\n");
		}
	}
	
	return 0;
}
