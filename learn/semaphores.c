#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
// for const IPC_CREAT
#include <sys/shm.h>
// EXIT_FAILURE
#include <stdlib.h>
// perror()
#include <stdio.h>
// sleep
#include <unistd.h>

// https://www.youtube.com/watch?v=ukM_zzrIeXs

// 1. defining sempahore constants
#define SEM_FORKS "/forks"

int main(void)
{
	// 2. semaphore unlink
	sem_unlink(SEM_FORKS);
	// 3 initialise semaphores and access priviledges (similar to files)
	// final argument = sempahore starts out at zero
	sem_t *sem_forks = sem_open(SEM_FORKS, O_CREAT, 0660, 5);
	// check for errors
	if (sem_forks == SEM_FAILED) {
		perror("sem_open/forks");
		exit(EXIT_FAILURE);
	}
	// + 3
	sem_post(sem_forks);
	sem_post(sem_forks);
	sem_post(sem_forks);
	// - 1
	sem_wait(sem_forks);
	sleep(5);
	int num;
	sem_getvalue(sem_forks, &num);
	printf("%i\n", num);
	// 4. make sure to close off semaphores
	sem_close(sem_forks);
	return (0);
}