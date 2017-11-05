#ifndef _QUEUE_H_
#define _QUEUE_H_

/**
 *  @file queue.h
 *  @brief Queue is Linear  Sequential Access - First-in-First-out
 *
 *  @details   A Queue is a First-In-First-Out (FIFO) abstract data type. Items can only be added at the rear of the queue and 
 * 			the only item that can be removed is the one at the front of the queue.
 *
 *  @author Pavel korolin
 *
 *  @bug No known bugs.
 */

typedef struct Queue Queue;

typedef enum Queue_Result
{

	QUEUE_SUCCESS,
	QUEUE_UNINITIALIZED_ERROR,
	QUEUE_ALLOCATION_ERROR,
	QUEUE_NULL_ITEM_ERROR,
	QUEUE_OVERFLOW,
	QUEUE_UNDERFLOW

}Queue_Result;

/*Creates queue. Returns pointer to the created queue.  Returns NULL on error.*/
Queue* Queue_Create();

/*Destroys queue. Recieves pointer to the queue to be destroyed*/
void Queue_Destory(Queue** _pQueue, void (*_elementDestroy)(void* _item));

/*Inserts value in queue. Recieves queue pointer and value to be inserted. Returns error codes*/
Queue_Result Queue_Enqueue(Queue* _pQueue, void* _pItem);
/*Removes value from the queue and stores it in variable. Recieves queue pointer and pointer to the variable in which the retrieved value to be stored. Returns error codes*/
Queue_Result Queue_Dequeue(Queue* _pQueue, void** _pItem);

/*Returns value in top of the queue*/
Queue_Result Queue_Top(Queue* _pQueue, void** _pItem);

/*Returns 1 if the queue is empty, 0 otherwise*/
int Queue_isEmptey(Queue* _pQueue);

#endif /* _QUEUE_H_*/
