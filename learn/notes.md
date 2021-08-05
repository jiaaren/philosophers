Functions to learn
<ins>Mandatory</ins>
1. memset, 
2. printf, 
3. malloc, 
4. free, 
5. write,
6. usleep, 
7. gettimeofday, 
8. pthread_create, 				// make threads
9. pthread_detach, 
10. pthread_join,  				// make sure threads are still running after other code in main ended
11. pthread_mutex_init,       // ok
12. pthread_mutex_destroy,    // ok
13. pthread_mutex_lock,       // ok
14. pthread_mutex_unlock      // ok

<ins>Bonus</ins>
1. memset, printf, malloc, free, write, 
2. fork, 
3. kill,
4. exit, 
5. waitpid
6. pthread_create, pthread_detach, pthread_join, usleep, gettimeofday, 
7. sem_open, sem_close, sem_post, sem_wait, sem_unlink

<ins>What?</ins>
1. Avoid philisophers duplicating forks - protect fork state with **mutex**?
2. Semaphore

<ins>Others</ins>
1. [Dining Philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
2. [Dining Philosophers](https://www.youtube.com/watch?v=NbwbQQB7xNQ)
	1. Deadlock
		1. Spiralled fork
	2. Resource Starvation
3. [Pthread playlist](https://www.youtube.com/watch?v=uA8X5zNOGw8&list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM)
4. [Threads Codevault](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
5. [Dining Philosophers with threading and mutex](https://pages.mtu.edu/~shene/NSF-3/e-Book/MUTEX/TM-example-philos-1.html)

### Threads
#### Threads & Forks
- Fork (concurrency & isolation)
- Threads (concurrency w/o isolation)

#### Posix threads (pthreads)
- When compiling, need to add `-pthread`