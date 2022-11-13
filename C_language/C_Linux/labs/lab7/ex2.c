#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<errno.h>
#include<pthread.h>
#include<time.h> 

void *f(void* serialNewThread);
void *print(void *arg);
int currentThread=-1;
int N;
int* counters;
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
	threads=(pthread_t*)malloc((N+1)*sizeof(pthread_t));
	serials=(int*)malloc(N*sizeof(int));
	counters=(int*)malloc(N*sizeof(int));
	if(threads == NULL || serials == NULL)
		{
		printf("Allocated failed!!\n");
		exit(0);
		}
	for (i = 0; i < N+1; i++)
				counters[i]=0;
	for (i = 0; i < N; i++)
	{
	serials[i]=i;;
	ans=pthread_create(&threads[i],NULL,f,(void*)&serials[i]);
	if(ans)
		{
		printf("Can't create thread");
		exit(0);
		}
	}
	//print_Thread
	ans=pthread_create(&threads[N],NULL,print,NULL);
	if(ans)
		{
		printf("Can't create thread");
		exit(0);
		}
	sleep(20);
	free(threads);
	free(serials);
}

void *f(void* serialNewThread){
while(1)
	{
	// start
    currentThread = *(int *)serialNewThread;
	counters[currentThread]++;
	//while it's the same thread
	while(currentThread==*(int*)serialNewThread)
		{}
	currentThread = *(int*)serialNewThread;
	}
}
void *print(void *arg){
	int i;
	int second=0;
	while(1){
		second+=2;
		printf("<<< After %d Seconds >>>\n",second);
		for(i=0;i<N;i++)
			printf("Thread %d counted : %d\n",i+1,counters[i]);
		printf("\n");
		sleep(2);
	}
}

