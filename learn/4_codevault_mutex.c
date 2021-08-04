#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Mutex - https://www.youtube.com/watch?v=oq29KUy29iQ

/*
	Following from race conditions
	- Use mutex (i.e. a lock in a section of code)
	- visualise that we have a lock between our incrementing, i.e. 'mails++' below
		- check if lock is unlocked
		- before execution of increment, 'lock' our lock by changing value to 1
		- unlock once done incrementing
	- mutex essentially replaces the locking functionality

	Mutex considerations
	- provides certainty of execution
	- not required if program is not required and tracking of certainty of exeution is not required
	- If speed is important, mutex may not be the best because it will take long
		- if we comment out pthread_mutex_lock & pthread_mutex_unlock, program will run significantly faster

	Single and multi core processors
	- If we have single core, we'll never encounter race conditions
	- Only if we have multi-core does race conditions occur, but 99% of CPUs are multicore nowadays anyway
*/

// 1. Declare mutex
// need to be global variable i guess?
pthread_mutex_t mutex;

int mails = 0;

void *routine(void *arg)
{
	for (int i = 0; i < 1000000; i++)
	{
		// 3. Lock mutex
		pthread_mutex_lock(&mutex);
		mails++;
		// 4. Unlock mutex
		pthread_mutex_unlock(&mutex);
	}
}

// make sure to handle errors for pthreads too
int main(void)
{
	pthread_t t1, t2, t3, t4;

	// 2. Initialize mutex
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&t1, NULL, routine, NULL);
	pthread_create(&t2, NULL, routine, NULL);

	// can have more than 2 threads 
	pthread_create(&t3, NULL, routine, NULL);
	pthread_create(&t4, NULL, routine, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	// can have more than 2 threads
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	printf("No of mail: %i\n", mails);
	// 5. Destroying mutex
	pthread_mutex_destroy(&mutex);
	return (0);
}