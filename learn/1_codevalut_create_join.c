#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread (void *arg)
{
	printf("Starting thread\n");
}

int main1(void)
{
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1, NULL, thread, NULL);
	pthread_create(&t2, NULL, thread, NULL);
	return (0);
}


int main2(void)
{
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1, NULL, thread, NULL);
	pthread_create(&t2, NULL, thread, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}

void *thread2 (void *arg)
{
	printf("Starting thread\n");
	sleep(2);
	printf("Ending thread\n");
}

int main3(void)
{
	pthread_t t1;
	pthread_t t2;

	if (pthread_create(&t1, NULL, thread2, NULL) != 0) 
		return 1;
	if (pthread_create(&t2, NULL, thread2, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	return (0);
}

int main(void)
{
	// if execute without pthread_join, sequencing is a little bit off, sometimes doens't print properly
	// main1();

	// include pthread_join, now prints output always
	// main2();

	// Demonstrating concurrency and 
	// handling errors for thread functions (thread functions return 0 or 1), 0 is success
	main3();
}