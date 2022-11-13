#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<errno.h>
#include<pthread.h>
#include<time.h> 

void *f(void* serialNewThread);
int currentThread=-1;
int N;

void main(int argc, char* argv[])
{	
	int i,j,ans;
	pthread_t* threads;
	int* serials;
	if(argc!=2)
		{
		printf("Illegal Parameters!!\n");
		exit(0);
		}
	N=atoi(argv[1]);
	threads=(pthread_t*)malloc(N*sizeof(pthread_t));
	serials=(int*)malloc(N*sizeof(int));
	if(threads == NULL || serials == NULL)
		{
		printf("Allocated failed!!\n");
		exit(0);
		}
	for (i = 0; i < N; i++)
	{
	serials[i]=i+1;
	ans=pthread_create(&threads[i],NULL,f,(void*)&serials[i]);
	if(ans)
		{
		printf("Can't create thread");
		exit(0);
		}
	}
	sleep(1);
	free(threads);
	free(serials);
}

void *f(void* serialNewThread){
double elapsedTime;
struct timeval t1, t2;
while(1)
	{
	// start timer
    currentThread = *(int *)serialNewThread;
	gettimeofday(&t1, NULL);
	//while it's the same thread
	while(currentThread==*(int*)serialNewThread){
    			gettimeofday(&t2, NULL);
			}
	// compute and print the elapsed time in millisec
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
	printf("Time slice for thread %d = %lf  ms.\n",currentThread,elapsedTime) ;
	currentThread = *(int*)serialNewThread;
	}
}

