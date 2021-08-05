#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
// For randomizer
#include <time.h>

// https://www.youtube.com/watch?v=ln3el6PR__Q

void *roll_dice()
{
	// randomize
	int value = (rand() % 6) + 1;
	printf("%i\n", value);
	return (void *)&value;
}

int main1(void)
{
	// randomize
	srand(time(NULL));

	int *res;
	pthread_t th;
	pthread_create(&th, NULL, roll_dice, NULL);
	pthread_join(th, (void **)&res);

	printf("Result: %i\n", *res);
	return (0);
}

// mallocing
void *roll_dice2()
{
	// randomize
	int value = (rand() % 6) + 1;

	int *result = malloc(sizeof(int));
	*result = value;
	printf("Pointer value %p\n", result);
	// casting void
	return (void *)result;
}

int main2(void)
{
	// randomize
	srand(time(NULL));

	int *res;
	pthread_t th;
	pthread_create(&th, NULL, roll_dice2, NULL);
	pthread_join(th, (void **)&res);

	printf("Pointer value %p\n", res);
	printf("Result: %i\n", *res);

	// remember to free variable
	free(res);
	return (0);
}

/* 
	Considerations
	1. Local variables vs malloc'ed returned values
	- need to remember return value from pthread_join needs to be malloc'ed 
	2. return value
	- cast to (void *)
	3. main
	- update pthread_join function's 2nd argument, NULL to address of pointer

	Pointer address
	- they'll all have the same address

	Deallocation
	- remember to deallocate

	Caveat - from architectural standpoint
	- ideal to allocate and deallocate in same function 
	- not the greatest idea to free in main
*/

int main(void)
{
	// returning local variable, not going to work, need to allocate
	// main1();

	// returning malloc'ed variable
	main2();
}