//Q2 Answer:
/*Here myglobal is being shared by two threads.
But global variable can only be accessed once per process and it needs to be protected 
from continuous access.In this case myglobal is being modified by two threads
which results in a switch between j=myglobal and j=j+1. Therefore, myglobal is not 40.
*/
//Q3 Answer:
/*The variable myglobal would be 40 if the switch is done outside of the loop so that
the thread is not interrupted.
For example before or after executing the loop. Then myglobal would be 40.
*/

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>

/*
Purpose: Use 2 threads to increment myglobal exactly 40 times in total.
Compile: using -pthread option
 */

sem_t semaphoreVariable;
int myglobal = 0;

 void *thread_function(void *arg) 
 {
	int i,j;
	
	for (i = 0; i < 20; i++) 
	{
                sem_wait(&semaphoreVariable);
                myglobal = myglobal + 1;
                sem_post(&semaphoreVariable);
		printf(".");
		fflush(stdout);
		sleep(0.2);
	}
	
	return NULL;
        
        
}

int main(void) 
{
	pthread_t mythread;
        sem_init(&semaphoreVariable, 0, 1); 
	int i;

	if (pthread_create(&mythread, NULL, thread_function, NULL)) {
		printf("error creating thread.");
		abort();
	}

	for (i = 0; i < 20; i++) 
	{
                sem_wait(&semaphoreVariable);
		myglobal = myglobal + 1;
                sem_post(&semaphoreVariable);
		printf("o");
		fflush(stdout);
		sleep(0.21);
	}

	if (pthread_join(mythread, NULL)) {
		printf("error joining thread.");
		abort();
	}

	printf("\nmyglobal equals %d\n", myglobal);

        sem_destroy(&semaphoreVariable);
        
	exit(0);
}
 

