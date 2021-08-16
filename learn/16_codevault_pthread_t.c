// https://www.youtube.com/watch?v=4VQmuj1RrCk

/*
	can try printing pthread_t as unsigned long

	manual - do not assume unsinged long
	- pthread_t is an opaque data type
	- so shouldn't work with values themselves, e.g. printf("ul")

	pthread_self();

	Software hierarchy
	- Software/Program
	- Pthread API		(pthread functions exist here)
	- Operating system  (SYS_gettid)
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/syscall.h>

#define THREAD_NUM 2

void* routine(void* args) {
    pthread_t th = pthread_self();
	// Don't do this
    printf("Printing thread integer: %lu\n", th);
	// Do this instead
    printf("Printing thread ID: %d\n", (pid_t) syscall(SYS_gettid));
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
        }
        // printf("%ul\n", th[i]);
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    return 0;
}