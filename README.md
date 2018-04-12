#include <pthread.h>		//Create POSIX threads.
#include <time.h>		//Wait for a random time.
#include <unistd.h>		//Thread calls sleep for specified number of seconds.
#include <semaphore.h>	//To create semaphores
#include <stdlib.h>			
#include <stdio.h>		//Input Output
pthread_t *Students;		//N threads running as Students.
pthread_t TA;			//Separate Thread for TA.
int ChairsCount = 0;
int CurrentIndex = 0;

//Declaration of Semaphores and Mutex Lock.
sem_t TA_Sleep;
sem_t Student_Sem;
sem_t ChairsSem[3];
pthread_mutex_t ChairAccess;

//Declared Functions
void *TA_Activity();
void *Student_Activity(void *threadID);
int main(int argc, char* argv[])
{
int number_of_students;		/*a variable taken from the user to create student threads.	Default        is 5 student threads.*/
	int id;
	srand(time(NULL));

	//Initializing Mutex Lock and Semaphores.
	sem_init(&TA_Sleep, 0, 0);
	sem_init(&Student_Sem, 0, 0);
	for(id = 0; id < 3; ++id)			//Chairs array of 3 semaphores.
		sem_init(&ChairsSem[id], 0, 0);
