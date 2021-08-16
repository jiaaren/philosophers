Functions to learn
<ins>Mandatory</ins>
1. memset, 						?
2. printf, 
3. malloc, 
4. free, 
5. write,
6. usleep, 
7. gettimeofday, 				?
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
6. [Slides](https://www.eecis.udel.edu/~haggerty/teaching/CISC361/09S/slides/Classics.pdf)
7. [Good background information for problem, mutexes, semapores, conditions](https://codecharms.me/posts/operating-system-the-dining-philosophers-problem)
8. [Another good reading, but no fixed sol](https://sites.cs.ucsb.edu/~rich/class/cs170/notes/DiningPhil/index.html)
9. [Testing]
   1. (https://github.com/nesvoboda/socrates)
   2. (https://www.notion.so/philosophers-VM-c60be9c836084edfbcd9c07e29b429c4)

<ins>Random</ins>
1. Once thread is detatched, cannot be joined again
   1. https://stackoverflow.com/questions/39174761/pthreads-can-i-detach-from-a-thread-and-then-join-in-main
   2. XY problem https://xyproblem.info/

2. pthread_detatch vs pthread_join? Whats the exact difference?
   1. https://stackoverflow.com/questions/22427007/difference-between-pthread-exit-pthread-join-and-pthread-detach
   2. detatch allows execution from the thread, while join usually executed from original main function/thread.

3. Need to use detatch or join to clear out resources
	1. https://stackoverflow.com/questions/24816518/not-using-pthread-detach-or-pthread-join-will-not-clean-up-the-resources-for-ot

4. Can i have multiple mutexes?

5. Do childprocesses share the same semaphore? - https://www.google.com/search?q=forking+and+semaphore&oq=forking+and+semaphore&aqs=chrome..69i57j0i22i30.4010j0j7&sourceid=chrome&ie=UTF-8

6. replace sem_init with sem_open

### Threads
#### Threads & Forks
- Fork (concurrency & isolation)
- Threads (concurrency w/o isolation)

#### Posix threads (pthreads)
- When compiling, need to add `-pthread`
