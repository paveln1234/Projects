#ifndef _STUCK_H_
#define _STUCK_H_

/**
 *  @file stack.h
 *  @brief Create a Generic Double Linked List data type
 *
 *  @details Implemented as double linked list using head and tail sentinels.
 *  Nodes are allocated from heap an store pointer to user proveded element.
 *
 *  @author Author MuhammadZ (muhammadz@experis.co.il)
 *
 *  @bug No known bugs.
 */

#include <stddef.h>  /* size_t */



typedef struct Stack Stack;


typedef enum Stack_Result {
	STACK_UNINITIALIZED_ERROR = -1,			/**< Uninitialized list 					 	*/
	STACK_SUCCESS,
	STACK_ALLOCATION_ERROR,				/**< Stack allocation failed due to heap error   */
	STACK_NULL_ELEMENT_ERROR,
	STACK_UNDERFLOW

} Stack_Result;


Stack* Stack_Create(void);

void Stack_Destroy(Stack** _pStack, void (*_elementDestroy)(void* _item));

Stack_Result Stack_Push(Stack* _stack, void*  _pItem);

Stack_Result Stack_Pop(Stack* _stack, void** _pItem);

Stack_Result Stack_Top(Stack* _stack, void** _pItem);

size_t Stack_Size(Stack* _stack);


#endif /* _STUCK_H_ */
