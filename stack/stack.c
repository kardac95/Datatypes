#include "stack.h"

stack* stack_empty(free_func ff) {
	stack *s;
	if(!(s =(stack*)calloc(1, sizeof(stack))))
		return NULL;
	pthread_mutex_init(&(s->lock), NULL);
	pthread_mutex_init(&(s->lock2), NULL);
	s->freefunc = ff;
	s->top = NULL;
	s->size = 0;
	return s;
}

void stack_push(stack* s, void* data) {
	pthread_mutex_lock(&(s->lock));
	node* new = (node*)calloc(1,sizeof(node));
	new->data = data;
	new->next = (struct node*)s->top;
	s->top = new;
	s->size++;
	pthread_mutex_unlock(&(s->lock));
}

void stack_pop(stack* s) {
	pthread_mutex_lock(&(s->lock));
	if(stack_is_empty(s)) {
		fprintf(stderr, "Pop on empty stack, exiting program!\n");
		pthread_mutex_unlock(&(s->lock));
		exit(1);
	} else {
		node* tmp = s->top;
		s->top = (node*)s->top->next;
		if(s->freefunc)
			s->freefunc(tmp->data);
		free(tmp);
		s->size--;
	}
	pthread_mutex_unlock(&(s->lock));
}

int stack_is_empty(stack* s) {
	pthread_mutex_lock(&(s->lock));
	return s->size == 0;
	pthread_mutex_unlock(&(s->lock));
}

void* stack_top(stack* s) {
	pthread_mutex_lock(&(s->lock));
	return s->top->data;
	pthread_mutex_unlock(&(s->lock));
}

unsigned int stack_size(stack* s) {
	pthread_mutex_lock(&(s->lock));
	unsigned int size = s->size;
	pthread_mutex_unlock(&(s->lock));
	return size;
}

void stack_free(stack* s) {
	if(s) {
		while(s->top)
			stack_pop(s);
		pthread_mutex_destroy(&(s->lock));
		free(s);
	}
}

