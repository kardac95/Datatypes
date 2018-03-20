#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "queue.h"

void dequeue_test();
void enqueue_test();

int main(void) {	
	dequeue_test();	
	enqueue_test();	
	return 0; 
}

void enqueue_test() {
	queue* q = queue_empty(free);
	char* t1 = malloc(10);
	strcpy(t1, "1234kalle");
	
	enqueue(q, t1);
	if(!queue_is_empty(q)) {
		fprintf(stderr,"Test 1 enqueue: SUCCESS\n");
	}else {
		fprintf(stderr, "Queue is empty faild first test: FAILED\n");
		exit(EXIT_FAILURE);
	}
	
	char* t2 = malloc(10);                                                  
    strcpy(t2, "1234Linux");
	
	//test2: checks if function enqueue override the the already enqueued 
	//data.
	enqueue(q, t2);
	if(!strcmp(t1, (char*)queue_first(q)))
	{
		fprintf(stderr,"Test 2 enqueue: SUCCESS\n");
	}else 
	{
		fprintf(stderr,"Test 2 override: FAILED\n");
	}
	queue_free(q);
}

void dequeue_test()
{
	queue* q = queue_empty(free);
    char* t1 = malloc(10);
    strcpy(t1, "1234kalle");                                          
    
    char* t2 = malloc(10);                                                      
    strcpy(t2, "1234Linux"); 
    enqueue(q, t1);
	enqueue(q, t2);
	dequeue(q);
	
	if(!strcmp(((char*)queue_first(q)) ,t2))
	{
		fprintf(stderr,"Test 1 dequeue: SUCCESS\n");
	}else
	{
		fprintf(stderr,"Test 1 dequeue: FAILED\n");
		exit(EXIT_FAILURE);
	}

	dequeue(q);
	if(queue_is_empty(q))
	{
		fprintf(stderr, "Test 2 dequeue: SUCCESS\n");
	}else
	{
		fprintf(stderr, "Test 2 dequeue: FAILED\n");
		exit(EXIT_FAILURE);
	}
	queue_free(q);
}

