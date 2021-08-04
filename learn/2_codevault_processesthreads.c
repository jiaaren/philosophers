#include <unistd.h>
#include <stdio.h>
// getpid, fork
#include <sys/types.h>
// wait
#include <sys/wait.h>
// thread
#include <pthread.h>
// exit
#include <stdlib.h>

// Video reference  - https://www.youtube.com/watch?v=IKG1P4rgm54&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&index=2

int main_process_id(void)
{
	int pid = fork();
	int num = 0;
	if (pid == -1)
		return (-1);
	if (pid == 0)
		num++;
	printf("Process id: %i, num is %i\n", getpid(), num);
	// wait for child process
	if (pid != 0)
		wait(NULL);

	// need to call exit here or else child will execute thread function in main()
	if (pid == 0)
		exit(0);
	return (0);
}


int x = 2;

void *thread2 (void *arg)
{
	// increment x here because this thread runs first
	x++;
	printf("Process ID: %i\n", getpid());
}

void *thread3 (void *arg)
{
	printf("Process ID: %i\n", getpid());
}

int main_thread_id(void)
{
	pthread_t t1;
	pthread_t t2;

	if (pthread_create(&t1, NULL, thread2, NULL) != 0) 
		return 1;
	if (pthread_create(&t2, NULL, thread3, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	return (0);
}

int main(void)
{	
	printf("<--Processes-->\n");
	// Processes using fork() 
	// - They have difference process IDs
	// - Memory is copied and duplicated
	main_process_id();

	printf("\n<--Threads-->\n");
	// Threads using pthread library 
	// - They will have same process IDs
	// - They share the same memory
	main_thread_id();
}