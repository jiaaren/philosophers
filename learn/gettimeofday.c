#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main1(void)
{
	struct timeval _timeval;
	int gettime;

	while (1)
	{
		gettime = gettimeofday(&_timeval, NULL);
		printf("%li\n", _timeval.tv_sec);
		// 1 second = 1000000 microseconds
		// 1 second = 1000 miliseconds
		usleep(1000000);
	}
	return (0);
}

int main2(void)
{
	struct timeval _timeval;
	int gettime;

	while (1)
	{
		gettime = gettimeofday(&_timeval, NULL);
		printf("%li\n", (_timeval.tv_sec * (__uint64_t)1000 + (_timeval.tv_usec / 1000)));
		// 1 second = 1000000 microseconds
		// 1 second = 1000 miliseconds
		usleep(1000);
	}
	return (0);
}

int main(void)
{
	// main1();
	// return (0);

	main2();
}