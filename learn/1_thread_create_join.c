#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// no thread
void	myturn()
{
	while (1)
	{
		sleep(1);
		printf("My Turn\n");
	}
}

void	yourturn()
{
	while (1)
	{
		sleep(2);
		printf("Your Turn\n");
	}
}

int	main1(void)
{
	myturn();
	yourturn();
	return (0);
}

// using thread
void	*myturn2(void *arg)
{
	while (1)
	{
		sleep(1);
		printf("My Turn\n");
	}
	return (NULL);
}

void	yourturn2()
{
	while (1)
	{
		sleep(2);
		printf("Your Turn\n");
	}
}

int	main2(void)
{
	pthread_t newthread;

	pthread_create(&newthread, NULL, myturn2, NULL);
	yourturn2();
	return (0);
}

// pthread_join
void	*myturn3(void *arg)
{
	for (int i = 0; i < 8; i++)
	{
		sleep(1);
		printf("%i: My Turn\n", i);
	}
	return (NULL);
}

void	yourturn3()
{
	for (int i = 0; i < 5; i++)
	{
		sleep(1);
		printf("%i: Your Turn\n", i);
	}
}

int	main3(void)
{
	pthread_t newthread;

	pthread_create(&newthread, NULL, myturn3, NULL);
	yourturn3();
	// pthread_join accepts pthread_t, not pointer
	pthread_join(newthread, NULL);
	return (0);
}

int main(void)
{
	// no threads used, only print out myturn once
	// main1();

	// threads used for myturn2
	// main2();

	// threads for loop, thread terminates when main ends
	// pthread_join accepts pthread_t, not pointer
	main3();

	return (0);
}