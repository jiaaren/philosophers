#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// https://www.youtube.com/watch?v=Adtrk3PREQI
int prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

/*
    Summary, How to:
    1. Handle memory allocation and freeing within same function
    2. Remember passing in memory via pthread_create and reading return values using pthread_join

    Steps
    1. (MAIN) malloc memory and passing in function thru pthread_create
    2. (FUNC) use memory
    3. (FUNC) return memory
    4. (MAIN) read return'ed memory thur pthread_join
    5. (MAIN) free malloc'ed memory
*/

// start index is pretty
void *sum_prime(void *start_index)
{
    // 2. use (void *) argument
	int index = *(int *)start_index;
    int sum = 0;

    while (index < 10)
    {
        sum += prime[index];
        index++;
    }
    // 3. Store return value in (void *) argument
    *(int *)start_index = sum;
    return (start_index);
}

int main(void)
{
	pthread_t th;

    // 1.   malloc start index of 0
    //      in video, start index is looped through, instead of being initialised
    int *start_index = malloc(sizeof(int));
    *start_index = 0;

	pthread_create(&th, NULL, sum_prime, (void *)start_index);
    // 4. retrieve return value from fucntion above
    pthread_join(th, (void **)&start_index);
    printf("Total sum is %i\n", *start_index);
    // 5. Freeing value passed in
    free(start_index);
	return (0);
}
