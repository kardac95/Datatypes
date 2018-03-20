#ifndef _STACK_H_                                                               
#define _STACK_H_                                                               
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>

typedef void (*free_func)(void *n);

typedef struct {
	void* data;
	struct node* next;
} node;

typedef struct {
	node* top;
	unsigned int size;
	pthread_mutex_t lock;
	free_func freefunc;
} stack;	

stack* stack_empty(free_func);

void stack_push(stack*, void*);

void stack_pop(stack*);

int stack_is_empty(stack*);

void* stack_top(stack*);

unsigned int stack_size(stack*);

void stack_free(stack*);

#endif
