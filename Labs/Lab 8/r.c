#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>

#define SHMKEY 75

int main(int argc, char *argv[])  //expects pid of writer as clarg
{
	int i, *pint, *ppint, *pint1, shmid;
	int pid = atoi(argv[1]);

	shmid = shmget(SHMKEY, 128, 0666);
	pint = (int*) shmat(shmid, 0, 0);
	ppint = pint;

	/*busy wait until writer sets the flag to indicate writer finished writing*/
	while(*pint != -1); 
	
        *ppint++; 
	for(i = 0; i < 10; i++) 
		printf("%d\n", *ppint++); /* display sh. mem */
	
	
	*pint = 0;
	
	kill(pid, 10);

	ppint = pint;
	
	/*busy wait until writer sets the flag to indicate it has finished writing*/
	while(*pint != -1); 
				
        *ppint++; 
	for(i = 0; i < 10; i++) 
		printf("%d\n", *ppint++); /* display sh. mem */
	
        system("ipcs -m");
	
	kill(pid, 11); /* send signal to shwrite that's OK to remove shmem */
}
