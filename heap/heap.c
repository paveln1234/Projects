#include <stdlib.h>
#include <stdio.h>
#include "../inc/heap.h"
#include "../inc/macros.h"
#define MAGICNUMBER 0xCAFEFEED
#define FATHER_INDEX(index)   (index/2)
#define LEFT_SON_INDEX(index)   (index*2)
#define RIGHT_SON_INDEX(index)   ((index*2)+1)
#define LAST_FATHER_INDEX(heap)   (heap->m_heapSize)



/**intrenal function **/
static void VectorSwap(Vector_t* _vec, size_t _indexA, size_t _indexB, void* _itemA, void* _itemB);
static void Heap_Sort(Heap* _heap);
static void Heap_Heapify(Heap* _heap, size_t _index);
static void Heap_BubbleUp(Heap* _heap, size_t _index);


struct Heap
{
    Vector_t* m_vec;
    LessThanComparator m_lessFunc;
    size_t m_magicNumber;
    size_t m_heapSize;
};


Heap* Heap_Build(Vector_t* _vector, LessThanComparator _pfLess)
{
    Heap* newHeap;

    CHECK_EQUAL_RETURN(NULL,_vector,NULL);
	CHECK_EQUAL_RETURN(NULL,_pfLess,NULL);

    newHeap = (Heap*)malloc(sizeof(Heap));
    CHECK_EQUAL_RETURN(NULL,newHeap,NULL);

    newHeap->m_vec = _vector;
    newHeap->m_lessFunc = _pfLess;
    newHeap->m_magicNumber = MAGICNUMBER;
	newHeap->m_heapSize = Vector_Size(_vector);

    Heap_Sort(newHeap);

return newHeap;
}

Vector_t* Heap_Destroy(Heap** _heap)
{
	Vector_t* vector = NULL;

	CHECK_EQUAL_RETURN(NULL,_heap,NULL);
	CHECK_EQUAL_RETURN(NULL,*_heap,NULL);
	CHECK_NOTEQUAL_RETURN(MAGICNUMBER, (*_heap)->m_magicNumber,NULL);
    vector = (*_heap)->m_vec;
    (*_heap)->m_magicNumber = 0;
    free(*_heap);
    *_heap = NULL;

return vector;
}

Heap_ResultCode Heap_Insert(Heap* _heap, void* _element)
{

	CHECK_EQUAL_RETURN(NULL,_heap,HEAP_NOT_INITIALIZED);
	CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_heap->m_magicNumber,HEAP_NOT_INITIALIZED);
	CHECK_EQUAL_RETURN(NULL,_element,HEAP_NOT_INITIALIZED);

	/* set element to vector*/
	CHECK_NOTEQUAL_RETURN(VECTOR_SUCCESS,Vector_Append(_heap->m_vec, _element),VECTOR_ERROR);

	++(_heap->m_heapSize);
	if (_heap->m_heapSize > 1 )
	{
		Heap_BubbleUp(_heap, LAST_FATHER_INDEX(_heap));
	}

return HEAP_SUCCESS;
}


 void* Heap_Peek(const Heap* _heap)
{
	void* returningItem ;
	CHECK_EQUAL_RETURN(NULL,_heap,NULL);
	CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_heap->m_magicNumber,NULL);

	Vector_Get(_heap->m_vec, 1, &returningItem);

	return returningItem;
}

void* Heap_Extract(Heap* _heap)
{
    void* returningItem = NULL;
	void* temp = NULL;

	CHECK_EQUAL_RETURN(NULL,_heap,NULL);
	CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_heap->m_magicNumber,NULL);

	/*get the first element in the vecto if noelements on the vector NULL will return   */
	CHECK_NOTEQUAL_RETURN(VECTOR_SUCCESS,Vector_Get(_heap->m_vec, 1, &returningItem),NULL);

	Vector_Remove(_heap->m_vec, &temp);
	--_heap->m_heapSize;
	Vector_Set(_heap->m_vec,1, &temp);
	Heap_Heapify(_heap, 1);

return returningItem;
}

size_t Heap_Size(const Heap* _heap)
{
	CHECK_EQUAL_RETURN(NULL,_heap,FALSE);
	CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_heap->m_magicNumber,FALSE);

	return _heap->m_heapSize;
}

size_t Heap_ForEach(const Heap* _heap, ActionFunction _action, void* _context)
{
	int i;
	void* itemToAction;

	CHECK_EQUAL_RETURN(NULL,_heap,FALSE);
	CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_heap->m_magicNumber,FALSE);
	CHECK_EQUAL_RETURN(NULL,_action,FALSE);

	/* vector start from 1 */
	for(i = 1;  i < _heap->m_heapSize ; ++i)
	{
		if( (VECTOR_SUCCESS != Vector_Get(_heap->m_vec,i,&itemToAction)) || 0 == _action(itemToAction, _context)   )
		{
			break;
		}
	}

	return i;
}

static void Heap_Sort(Heap* _heap)
{
    size_t i = LAST_FATHER_INDEX(_heap);

    for( ;  0 < i ; --i)
    {
            Heap_Heapify(_heap, i);
    }

return;
}

static void Heap_Heapify(Heap* _heap, size_t _index)
{
	void* rightSon;
	void* leftSon;
	void* fatherItem;

	/* get father*/
	CHECK_NOTEQUAL_VOID_RETURN(VECTOR_SUCCESS,Vector_Get(_heap->m_vec, _index, &fatherItem));
	/*get left son */
	CHECK_NOTEQUAL_VOID_RETURN (VECTOR_SUCCESS,Vector_Get(_heap->m_vec, LEFT_SON_INDEX(_index), &leftSon) );

	/*try to get right son if the result isn't VECTOR_SUCCESS than it means the tree is not full*/
	/*if there are both left and right son, right son is bigger than left son and more then father, swap father item with right son*/
	if((VECTOR_SUCCESS == Vector_Get(_heap->m_vec, RIGHT_SON_INDEX(_index), &rightSon))  &&  _heap->m_lessFunc(leftSon, rightSon)  &&   _heap->m_lessFunc(fatherItem, rightSon))
	{
		VectorSwap(_heap->m_vec, _index,  RIGHT_SON_INDEX(_index), fatherItem, rightSon);
		Heap_Heapify(_heap,  RIGHT_SON_INDEX(_index));
	}

	/*else check if father is less then left son and swap if it is*/
	else if(_heap->m_lessFunc(fatherItem, leftSon))
	{
		VectorSwap(_heap->m_vec, _index, LEFT_SON_INDEX(_index), fatherItem, leftSon);
		Heap_Heapify(_heap, LEFT_SON_INDEX(_index));
	}

return;
}

static void Heap_BubbleUp(Heap* _heap, size_t _index)
{
	void* item;
	void* father;

	/*get and check father  */
	CHECK_NOTEQUAL_VOID_RETURN(VECTOR_SUCCESS,Vector_Get(_heap->m_vec, FATHER_INDEX(_index), &father));

	/*get the corrent item	*/
	CHECK_NOTEQUAL_VOID_RETURN(VECTOR_SUCCESS,Vector_Get(_heap->m_vec, _index, &item));

	/*swap if current item is greater than its father and bubble up*/
	if(_heap->m_lessFunc(father, item))
	{
		VectorSwap(_heap->m_vec, _index, FATHER_INDEX(_index), item, father);
		Heap_BubbleUp(_heap, FATHER_INDEX(_index));
	}

return;
}

static void VectorSwap(Vector_t* _vec, size_t _indexA, size_t _indexB, void* _itemA, void* _itemB)
{
	Vector_Set(_vec, _indexA, &_itemB);
	Vector_Set(_vec, _indexB, &_itemA);
return;
}
