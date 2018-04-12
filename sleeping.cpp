#include <pthread.h>		//Create POSIX threads.
#include <time.h>		//Wait for a random time.
#include <unistd.h>		//Thread calls sleep for specified number of seconds.
#include <semaphore.h>	//To create semaphores
#include <stdlib.h>
#include <stdio.h>		//Input Output
pthread_t Students[10];		//N threads running as Students.
pthread_t TA;			//Separate Thread for TA.
int no_of_free_seats = 3;


//Declaration of Semaphores and Mutex Lock.
sem_t TA_ready;
sem_t ChairsSem;
sem_t ChairAccess;

//Declared Functions
void *TA_Activity();
void *Student_Activity(void *threadID);
int main()
{
  int number_of_students;		/*a variable taken from the user to create student threads.	Default        is 5 student threads.*/
	sem_init(&TA_ready, 0, 1);
	sem_init(&ChairsSem, 0, 3);
	sem_init(&ChairAccess, 0,1);
  for(int id = 0; id < 3; ++id)
	sem_wait(&ChairsSem);
  sem_wait(&TA_ready);
	printf("Enter number of students\n");
	scanf("%d",&number_of_students);
	//Creating TA thread and N Student threads.
	pthread_create(&TA, NULL, TA_Activity, NULL);
	for(int id = 0; id < number_of_students; id++)
		pthread_create(&Students[id], NULL, Student_Activity,(void*) (long)id);

	//Waiting for TA thread and N Student threads.
	pthread_join(TA, NULL);
	for(int id = 0; id < number_of_students; id++)
	pthread_join(Students[id], NULL);
	return 0;
}

void *TA_Activity()
{
		printf("~~~~~~~~~~~~~~~~~~~~~TA is currently sleeping~~~~~~~~~~~~~~~~~~~~~\n");
//while(1){
      sem_wait(&ChairsSem);
			sem_wait(&ChairAccess);
			no_of_free_seats++;
      printf("TA is ready to help Student\n");
			printf("Student left his/her chair. Remaining Chairs %d\n",no_of_free_seats);
      sem_post(&TA_ready);
      sem_post(&ChairAccess);
      printf("TA is currently helping the student.\n");

			sleep(10);
//	}
}

void *Student_Activity(void *threadID)
{
	//int ProgrammingTime;


     sleep(4);
    printf("Student %ld needs help from the TA\n", (long)threadID);
    sem_wait(&ChairAccess);
    if(no_of_free_seats>0){

      no_of_free_seats--;
     printf("Student sat on chair.Chairs Remaining: %d\n",no_of_free_seats);
     sem_post(&ChairAccess);
     sem_post(&ChairsSem);
     sem_wait(&TA_ready);
     printf("Student %ld is getting help from the TA. \n", (long)threadID);
     sleep(2);
     printf("Student %ld left TA room.\n",(long)threadID);
    }
    else{
      sem_post(&ChairAccess);
      printf("No Seat Available...Student %ld will return at another time. \n", (long)threadID);
    }

	}
