#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Threads for loop - https://www.youtube.com/watch?v=xoXzp4B8aQk

/*
    Never call pthread_create and pthread_join in the same for loop
    - will have only 1 thread executing at a single time

    Messages printed out
    - relates to how we iterate over the printf, 
    - rather than how each thread finishes its execution
*/

pthread_mutex_t mutex;

int mails = 0;

void *routine(void *arg)
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

int main1(void)
{
    // create array of threads
	pthread_t th[4];

	pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 4; i++)
    {
        // test for execution
        printf("%-15s: %i\n", "Start of thread", i);

        // copy and paste same code as (4), but replace first argument with addrses/indexed array
	    pthread_create(th + i, NULL, routine, NULL);
        pthread_join(th[i], NULL);

        printf("%-15s: %i\n", "End of thread", i);
    }

	printf("No of mail: %i\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}

int main2(void)
{
    // create array of threads
	pthread_t th[4];

	pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 4; i++)
    {
        printf("%-15s: %i\n", "Start of thread", i);
	    pthread_create(th + i, NULL, routine, NULL);
    }
    for (int i = 0; i < 4; i++)
    {
        pthread_join(th[i], NULL);
        printf("%-15s: %i\n", "End of thread", i);
    }

	printf("No of mail: %i\n", mails);
	pthread_mutex_destroy(&mutex);
	return (0);
}

int main(void)
{
    // first example we observe that there is NO multithreading
    // because we have pthread_create and pthread_join in the same for loop
    // observe that NOT ALL start of threads do not execute first
    // main1();

    // split for loops for create and join
    /*
        Not for sequence of messages printed out
        - relates to how we iterate over the printf, 
        - NOT how each thread finishes its execution
    */
    main2();
    return (0);
}