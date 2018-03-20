#include "queue.h"                                                              

/*
*	Description:	Declare a queue and freefunc
*	Input:			the address of the freefunction
*	Output:			queue*
*/                                                                                
queue* queue_empty(queueFreeFunc freeFunc) {
	queue *q;
	if(!(q = (queue*)malloc(sizeof(queue)))) {                                                                           
		return NULL;
    }
	pthread_mutex_init(&(q->mutex), NULL);
	q->freeFunc = freeFunc;
	q->tail = NULL;
	q->head = NULL;
	q->size = 0;                                                              
	return q; 
}

/*
*	Description:	Takes in a queue pointer then 
*					return its head(the first element)
*	Input:			queue*
*	Output:			void pointer
*/
void* queue_first(queue* q) {
	pthread_mutex_lock(&(q->mutex));
	void *data = q->head->data;
	pthread_mutex_unlock(&(q->mutex));
	return data;
}

/*
*	Description:	Put a new element to the last place in the queue
*	Input:			queue*, void*
*	Output:			Non
*/
void enqueue(queue* q, void* data) {
	pthread_mutex_lock(&(q->mutex));
	node* new = (node*)malloc(sizeof(node));
	new->data = data;
	new->next = NULL;
	
	if(!q->head) {                                                                           
		q->head = new;
    } else {
		q->tail->next = new;
	}                                                                           
	q->tail = new;
	q->size++;
	pthread_mutex_unlock(&(q->mutex));
} 
/*
*	Description:	removes the first element of the queue.
*	Input:			queue*
*	Output:			non
*/
void dequeue(queue* q) {
	pthread_mutex_lock(&(q->mutex));
	//declare a temporary node that points to the head.
	node* n = q->head;
	//points the head to the element that is second in the queue
	q->head = q->head->next;
	//to free the data that the node points to.
	q->freeFunc(n->data);
	//removes the node
	free(n);
	q->size--;
	pthread_mutex_unlock(&(q->mutex));
}                                                                               

/*
*	Description:	return the size of the queue (nr of elements) 
*	Input: 			queue*
*	Output:			int, the size of the queue
*/                                                                                
int queue_size(queue* q) {
	pthread_mutex_lock(&(q->mutex));
	int size = q->size;
	pthread_mutex_unlock(&(q->mutex));
	return size;                                                             
}                                                                               
/*
*	Description:	Check if queue is empty
*	Input:			
*	Output:			returns 0, if it contains elements, 
*					returns 1, if the queue is 0
*/                                                                                
int queue_is_empty(queue* q) {
	pthread_mutex_lock(&(q->mutex));
	int size = q->size;
	pthread_mutex_unlock(&(q->mutex));
	if(size > 0)
		return 0;                                                                   
	return 1;
}	

/*
*	Description:	Loops through the whole queue and free each element
*	Input:			queue*
*	Output:			Non
*/
void queue_free(queue *q) {
	if(q->freeFunc != NULL) {
		while(q->head) {
			dequeue(q);
		}
		pthread_mutex_destroy(&(q->mutex));
	}
	free(q);
}
