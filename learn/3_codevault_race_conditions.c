#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// https://www.youtube.com/watch?v=FY9livorrJI

int mails = 0;

void *routine(void *arg)
{
	for (int i = 0; i < 50000; i++)
		mails++;
}

int main(void)
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, routine, NULL);
	pthread_create(&t2, NULL, routine, NULL);

	// need to add pthread_join to wait for threads to end first
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	// expected result would be 2x of execution of routine, i.e. 2x incrementing of mails
	/*
		Understanding mails++ in more detail (behind the scenes)
		1. Read the value in mails
		2. Increment value
		3. Write incremented value back to memory

		Using threads, there is a possibility that sequencing of operations are not guaranteed
		- CPU will stop if multiple threads are accesing the same memory at the same time
		- this will cause outdated values in the register to override updated values

		There 'race conditions' would exist because the operations above will overlap with one another

		Question - Why with lower iterations, there is no overlapping, e.g. 1000 iterations...
		- essentially the first pthread_create will FINISH executing the function before the second pthread_create
	*/
	printf("No of mail: %i\n", mails);
	return (0);
}