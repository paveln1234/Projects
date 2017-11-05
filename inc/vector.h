/* This library file includes Generic Vector functions */

#ifndef __GENVECTOR_H__
#define __GENVECTOR_H__

#include <stddef.h>
typedef enum Vector_Result {

	VECTOR_SUCCESS,
	VECTOR_UNINITIALIZED_ERROR,
	VECTOR_ALLOCATION_ERROR,
	VECTOR_INDEX_OUT_OF_BOUNDS_ERROR,
	VECTOR_OVERFLOW,
	VECTOR_UNDERFLOW

}Vector_Result;


/*
 * Create a Generic Vector data type
 * that stores pointer to user provided elements of generic type
 * The Vector is heap allocated and can grow and shrink on demand.
*/



#define TRUE 1
#define FALSE 0

typedef struct Vector Vector_t;
typedef int (*VectorElementAction) (void* _element, size_t _index, void* _context);
typedef void (*DestroyAction)(void* _element);

/*
 *		Dynamically create a new vector object of given capacity and
 *
 *		_initialCapacity - initial capacity, number of elements that can be stored initially
 *		_blockSize - the vector will grow or shrink on demand by this size
 *
 *		return- Vector * on success / NULL on fail
 *
 * 		warning- if _blockSize is 0 the vector will be of fixed size.
 *		if both _initialCapacity and _blockSize are zero function will return NULL.
 */

Vector_t* Vector_Create(size_t _initialSize, size_t _extensionBlockSize);

/*
 *		Dynamically deallocate a previously allocated vector
 *
 *		_vector - Vector to be deallocated.
 *		_elementDestroy : A function pointer to be used to destroy all elements in the vector
 *             or a null if no such destroy is required
 */
void Vector_Destroy (Vector_t** _vector, DestroyAction _elementDestroy);

/*
 *		Add an Item to the back of the Vector.
 *
 *		_vector - Vector to append integer to.
 *		_item - Item to add.
 *
 *		return success or error code
 *		retval VECTOR_SUCCESS on success
 *		retval VECTOR_UNINITIALIZED_ERROR if _vec is NULL
 *		retval VECTOR_OVERFLOW if _blockSize=0
 *		retval VECTOR_ALLOCATION_ERROR when allocation fails
 */
Vector_Result Vector_Append (Vector_t* _vector, void* _item);

/*
 *		Delete an Element from the back of the Vector.
 *
 *		_vector - Vector to delete integer from.
 *		_pValue - pointer to variable that will receive deleted item value
 *
 *		return success or error code
 *		retval VECTOR_SUCCESS on success
 *		retval VECTOR_UNINITIALIZED_ERROR if _vec is NULL
 *		retval VECTOR_UNDERFLOW if _numOfElements=0
 *		retval VECTOR_ALLOCATION_ERROR when allocation fails
 *
 *		warning	- _pValue can't be NULL
 */
Vector_Result Vector_Remove (Vector_t* _vector, void** _pValue);

/*
 *		Get value of item at specific index from the the Vector
 *
 *		_vector - Vector to use.
 *		_index - index of item to get value from. the index of first elemnt is 1
 *
 *		_pValue - pointer to variable that will recieve the item's value.
 *
 *		return success or error code
 *		retval VECTOR_SUCCESS on success
 *		retval VECTOR_UNINITIALIZED_ERROR if _vec is NULL
 *		retval VECTOR_INDEX_OUT_OF_BOUNDS_ERROR if _index is 0 or bigger than _numOfElements
 *
 *		warning - Index starts from 1.
 */
Vector_Result Vector_Get (const Vector_t* _vector, size_t _index, void** _pValue);

/*
 *		Set an item at specific index to a new value.
 *
 *		_vector - Vector to use.
 *		_index - index of an existing item.
 *		_value - new value to set.
 *
 *		return success or error code
 *		retval VECTOR_SUCCESS on success
 *		retval VECTOR_UNINITIALIZED_ERROR if _vec is NULL
 *		retval VECTOR_INDEX_OUT_OF_BOUNDS_ERROR if _index is 0 or bigger than _numOfElements
 *
 *		warning - Index starts from 1.
 */
Vector_Result Vector_Set(Vector_t* _vector, size_t _index, void** _pValue);

/*
 *		Get the number of actual items currently in the vector.
 *
 *		_vector - Vector to use.
 *
 *		return  number of items on success 0 if vector is empty or invalid
 */
size_t Vector_Size (Vector_t* _vector);

/*
 *		Get the current capacity of the  vector.
 *
 *		_vector - Vector to use.
 *
 *		return  capacity of vector
 */
size_t Vector_Capacity (Vector_t* _vector);

/*
 *		Iterate over all elements in the vector.
 *		The user provided _action function will be called for each element
 *      if _action return a zero for an element the iteration will stop.
 *
 *		_vector - vector to iterate over.
 *		_action - User provided function pointer to be invoked for each element
 *		_context - User provided context, will be sent to _action
 *
 *		returns number of times the user functions was invoked
 */
size_t Vector_ForEeach (const Vector_t* _vector,VectorElementAction _action, void* _context);


/*--- unit test ---*/
/*
void Vector_Print (Vector_t*_vector, VectorElementAction _elementPrint);

void DestroyElement (void* _element);

int PrintElement (void* _element, size_t _index, void* _context);

void InitializeArr(int _arr[], size_t _size);
*/
#endif /* __GENVECTOR_H__ */


