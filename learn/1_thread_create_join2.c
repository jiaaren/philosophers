#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// passing values into pthread_create
void	*myturn(void *arg)
{
	// reading and casting argument passed from pthread_create from (void *)
	int *num = (int *)arg;

	for (int i = 0; i < 8; i++)
	{
		sleep(1);
		printf("%i: My Turn, num is %i\n", i, *num);
		(*num) += 2;
	}
	return (NULL);
}

int	main1(void)
{
	pthread_t newthread;
	int i = 0;

	// pass in values via 4th argument of pthread_create
	pthread_create(&newthread, NULL, myturn, (void *)&i);
	pthread_join(newthread, NULL);
	printf("final num val is: %i\n", i);
	return (0);
}

// reading return values from pthread_join
void	*myturn2(void *arg)
{
	// malloc value, as return value will always be an address
	int *num = malloc(sizeof(int));
	*num = 0;

	for (int i = 0; i < 5; i++)
	{
		sleep(1);
		printf("%i: My Turn, num is %i\n", i, *num);
		(*num) += 2;
	}
	// make sure to update return values of void * function
	// since we are returning address, and not NULL.
	return ((void *)num);
}

int	main2(void)
{
	pthread_t newthread;
	int *i;

	pthread_create(&newthread, NULL, myturn2, NULL);

	// passing in pointer pointer to pthread_join
	pthread_join(newthread, (void **)&i);
	printf("final num val is: %i\n", *i);
	free(i);
	return (0);
}

int main(void)
{
	// integer declared and initialised in main, thread function dereferences and updates value of that integer
	// main1();

	// thread_join also RETURNS value (usually allocated memory)
	// integer 'malloc'ed' and allocated from thread and returned to main via pthread_join
	main2();

	return (0);
}