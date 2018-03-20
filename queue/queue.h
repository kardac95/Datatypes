#ifndef _QUEUE_H_                                                               
#define _QUEUE_H_                                                               
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
//freefunction
typedef void (*queueFreeFunc)(void *n);

typedef struct node
{
    void* data;
    struct node* next;
}node;

typedef struct queue
{
	//first element of the queue
    node* head;
	//last element of the queue
	node* tail;
	//the size of the queue
    unsigned int size;
	//mutex lock for the queue
	pthread_mutex_t mutex;
	//the freefunc used becuse the queue don't know what type of data
	//to remove.
	queueFreeFunc freeFunc;
}queue;

//decleare the queue and set free func.
queue* queue_empty(queueFreeFunc freeFunc);

//adds a new element to the queue
void enqueue(queue* q, void* data);

//Removes an element of the queue
void dequeue(queue* q);

//Returns the first element of the queue
void* queue_first(queue* q);

//returns the size of the queue
int queue_size(queue* q);

//check if the queue is empty
int queue_is_empty(queue* q);

//frees all elements in the queue
void queue_free(queue *q);
#endif 
