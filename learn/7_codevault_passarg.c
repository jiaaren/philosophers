// value of i changes in for loops
// include sleep
// simple solution - dynamically allocate memory, need to make sure sequence of malloc and free

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// https://www.youtube.com/watch?v=HDohXvS6UIk

/*
	Objective - to have each of the 10 threads print unique prime numbers in the prime array

	Important considerations
	- remember that we are passing in addresses into pthread_join, instead of actual values
	- if INTEGRITY of values within the memory address are important, need to make sure they are unchanged
	- using for loop to loop through passing in values adds a risk that values are changed
	- i.e. threads may be using the changed values intended for other threads since 
			sequence of execution of main and the (void *)function cannot be guaranteed
	- one way to guarantee information is used is to make sure memory unchanged, e.g. malloc memory
		- if memory is malloc'ed, sequencing of freeing is also important
		- e.g. risk of freeing memory too quickly in main function instead of our (void *)function
		- sometimes need to free memory in free function instead
*/
int prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *print_prime(void *arg)
{
	int index = *(int *)arg;
	printf("%i ", prime[index]);
}

int main1(void)
{
	pthread_t th[10];

	for (int i = 0; i < 10; i++)
	{
		pthread_create(th + i, NULL, print_prime, (void *)&i);	
	}
	for (int i = 0; i < 10; i++)
	{
		pthread_join(th[i], NULL);
	}
	return (0);
}

// incorporated malloc and memory freeing
void *print_prime2(void *arg)
{
	int index = *(int *)arg;
	printf("%i ", prime[index]);

	// remember to free
	free(arg);
}

int main2(void)
{
	pthread_t th[10];

	for (int i = 0; i < 10; i++)
	{
		// instead of passing in pointer of increment of for loop, 
		// malloc'ed and passed in address of tmp
		int *tmp = malloc(sizeof(int));
		*tmp = i;

		pthread_create(th + i, NULL, print_prime2, (void *)tmp);	
	}
	for (int i = 0; i < 10; i++)
	{
		pthread_join(th[i], NULL);
	}
	return (0);
}

int main(void)
{
	// running this returns bad result
	// main1();

	// running this now works
	main2(); 
	return (0);
}