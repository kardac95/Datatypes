#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "queue.h"
typedef struct
{
	char* kalle;
	char* linux;
	char* johnny;
}bm;

void freefunc(void* n);
void dequeue_test();
void enqueue_test();
int main(void)
{
	
	dequeue_test();	
	enqueue_test();

	queue* q = queue_empty(&freefunc);
	for(int i = 0; i < 10; i++)
	{
		bm* kalle = malloc(sizeof(bm));
		if(i % 3)
		{
			kalle->kalle = malloc(10);
            kalle->linux = malloc(10);
            kalle->johnny = malloc(10);
			strcpy(kalle->kalle, "1234kalle");
			strcpy(kalle->linux, "1234linux");
            strcpy(kalle->johnny, "1234jonny");
		}else
		{
			kalle->kalle = malloc(5);
			kalle->linux = malloc(6);
			kalle->johnny = malloc(3);
			strcpy(kalle->kalle, "karl");
			strcpy(kalle->linux, "linus");
			strcpy(kalle->johnny, "JJ");
		}
		enqueue(q, kalle);
		printf("k = %s\n,l = %s\n,j = %s\n,%d\n", ((bm*)queue_first(q))->kalle,
	((bm*)queue_first(q))->linux,((bm*)queue_first(q))->johnny, queue_size(q));
	}
		
	
	for(int i = 0; i < 10; i++)                                                    
    {                                                         
		printf("k = %s\n,l = %s\n,j = %s\n,%d\n", ((bm*)queue_first(q))->kalle, 
    ((bm*)queue_first(q))->linux,((bm*)queue_first(q))->johnny, queue_size(q));
		dequeue(q);
    }	
	//queue_free(q);
	queue_is_empty(q);
	free(q);
	return 0; 
}

void freefunc(void* n)
{
	bm *a = (bm*)n;
	bzero(a, sizeof(bm));
	if(a->kalle)
	{
		printf("%s\n", a->kalle);
		free(a->kalle);                                                           
    }
	if(a->linux)
	{
		printf("%s\n", a->linux);
		free(a->linux);
	}
	if(a->johnny)
	{
		printf("%s\n", a->johnny);
		free(a->johnny);
	}
	free(a);
}

void enqueue_test()
{
	queue* q = queue_empty(&freefunc);
	bm* kalle = malloc(sizeof(bm));
	kalle->kalle = malloc(10);
	strcpy(kalle->kalle, "1234kalle");
	
	enqueue(q,kalle);
	if(!queue_is_empty(q))
	{
		fprintf(stderr,"queue is not empty, first test enqueue: SUCSSEDED\n");
	}else
	{
		fprintf(stderr, "queue is empty faild first test: FAILED\n");
		exit(EXIT_FAILURE);
	}
	
	bm* k = malloc(sizeof(bm));                                             
    k->kalle = malloc(10);                                                  
    strcpy(k->kalle, "1234Linux");
	
	//test2: checks if function enqueue override the the already enqueued 
	//data.
	enqueue(q, k);
	if(!strcmp(kalle->kalle, ((bm*)queue_first(q))->kalle))
	{
		fprintf(stderr,"Test override: SUCCEDED\n");
	}else 
	{
		fprintf(stderr,"Test override: FAILED\n");
	}
	queue_free(q);
}

void dequeue_test()
{
	queue* q = queue_empty(&freefunc);                                          
    bm* kalle = malloc(sizeof(bm));                                             
    kalle->kalle = malloc(10);
    strcpy(kalle->kalle, "1234kalle");                                          
    
	bm* k = malloc(sizeof(bm));                                                 
    k->kalle = malloc(10);                                                      
    strcpy(k->kalle, "1234Linux"); 
    enqueue(q, kalle);
	enqueue(q, k);
	dequeue(q);
	
	if(!strcmp(((bm*)queue_first(q))->kalle ,k->kalle))
	{
		fprintf(stderr,"Test dequeue 1: SUCCESS\n");
	}else
	{
		fprintf(stderr,"Test dequeue 1: SUCCESS\n");
		exit(EXIT_FAILURE);
	}

	dequeue(q);
	if(queue_is_empty(q))
	{
		fprintf(stderr, "Test dequeue 1: SUCCESS\n");
	}else
	{
		fprintf(stderr,"Test dequeue 1: FAILED\n");
		exit(EXIT_FAILURE);
	}
	queue_free(q);
}

