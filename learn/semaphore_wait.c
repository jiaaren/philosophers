#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
// for const IPC_CREAT
#include <sys/shm.h>
// EXIT_FAILURE
#include <stdlib.h>
// perror()
#include <stdio.h>

// https://www.youtube.com/watch?v=ukM_zzrIeXs

// 1. defining sempahore constants
#define SEM_FORKS "/forks"

int main(void)
{
	// no need unlink
	// sem_unlink(SEM_FORKS);

	// just 2 arguments
	sem_t *sem_forks = sem_open(SEM_FORKS, 0);
	// check for errors
	if (sem_forks == SEM_FAILED) {
		perror("sem_open/forks");
		exit(EXIT_FAILURE);
	}
	// -3
	sem_wait(sem_forks);
	sem_wait(sem_forks);
	sem_wait(sem_forks);

	// make sure to close off semaphores
	sem_close(sem_forks);
	return (0);
}