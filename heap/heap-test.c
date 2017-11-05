#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "../inc/heap.h"
#include "../inc/mu_test.h"
#include "../inc/vector.h"

#define LOOP 20

typedef struct Rect
{
	size_t m_length;
	size_t m_height;
} Rect;

typedef void(*DestroyFunc_t)(void*);

int MyLess(Rect* _a, Rect* _b)
{
	return (_a->m_length < _b->m_length ? 1 : 0);
}


void MyDysroy(Rect* _item)
{
	free(_item);
return ;
}

int RectPrint(Rect* _rect,void* _context)
{
	printf("\nRect : Length - %lu, Heigth - %lu\n", _rect->m_length, _rect->m_height);
return 1;
}

/*======================================= TESTS ==============================================*/

UNIT(test_Create_and_Destroy)
	Vector_t* vector = NULL;
	Vector_t*temp;
	Heap* heap = NULL;
	vector = Vector_Create(20,10);
	heap = Heap_Build(vector , (LessThanComparator)MyLess);

	ASSERT_THAT(heap!= NULL);
	temp = Heap_Destroy(&heap);
	ASSERT_THAT(heap == NULL);
	ASSERT_THAT(temp == vector);
	Vector_Destroy(&vector,NULL);
	ASSERT_THAT(NULL == vector);

END_UNIT

/***********************************************************************************************/
/***********************************************************************************************/

UNIT(test_Heap_Insert)
	int i;
	Vector_t* vec = Vector_Create(100, 100);
	Rect* rects;
	Heap* heap = Heap_Build(vec, (LessThanComparator)MyLess);
	rects = calloc(12,sizeof(Rect));

	rects[0].m_length = 5;
	rects[0].m_height = 5;
	rects[1].m_length = 8;
	rects[1].m_height = 8;
	rects[2].m_length = 11;
	rects[2].m_height = 11;
	rects[3].m_length = 12;
	rects[3].m_height = 12;
	rects[4].m_length = 18;
	rects[4].m_height = 18;
	rects[5].m_length = 10;
	rects[5].m_height = 10;
	rects[6].m_length = 15;
	rects[6].m_height = 15;
	rects[7].m_length = 25;
	rects[7].m_height = 25;
	rects[8].m_length = 21;
	rects[8].m_height = 21;
	rects[9].m_length = 20;
	rects[9].m_height = 20;
	rects[10].m_length = 30;
	rects[10].m_height = 30;
	rects[11].m_length = 50;
	rects[11].m_height = 50;

	for(i = 0; i < 12; ++i)
	{
		ASSERT_THAT(Heap_Insert(heap, &rects[i])== HEAP_SUCCESS);
	}

	ASSERT_THAT(Heap_Size(heap) == 12 );
	ASSERT_THAT (12 == (Heap_ForEach(heap, (ActionFunction)RectPrint, NULL)));
	vec =Heap_Destroy(&heap);
	Vector_Destroy(&vec,NULL);
	free(rects);
END_UNIT

/***********************************************************************************************/

UNIT(add_and_extract)

	DestroyFunc_t destroyFunc = (DestroyFunc_t) MyDysroy;
	size_t  i;
	Rect* rects;
	Rect* res;
	Vector_t* vec = Vector_Create(100, 100);
	Heap* heap = Heap_Build(vec, (LessThanComparator)MyLess);

	for (i=0; i<11; ++i)
	{
		rects = calloc(1,sizeof(Rect));
		rects->m_length = i;
		rects->m_height = i;
		Heap_Insert ( heap, (void*)rects);
	}

	/*ASSERT_THAT (11 == (Heap_ForEach(heap, (ActionFunction)RectPrint, NULL)));*/

	 res = Heap_Extract(heap);
	ASSERT_THAT(res->m_length == 10);
	/*ASSERT_THAT(num == (LOOP-1) );*/
	vec =Heap_Destroy(&heap);
	Vector_Destroy(&vec,destroyFunc);
	free(res);

END_UNIT


/***********************************************************************************************/
UNIT(sorting_vector)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) MyDysroy;
	size_t max = 0, i;
	Rect* rects;
	Rect* res;

	Vector_t* vec = Vector_Create(100, 100);
	Heap* heap ;

	for (i=0; i<12; ++i)
	{
		rects = calloc(1,sizeof(Rect));
		rects->m_length = i;
		if(rects->m_length>max)
		{
			max = rects->m_length;
		}
		rects->m_height = i;
		Vector_Append(  vec, (void*)rects);
	}
	heap= Heap_Build(vec, (LessThanComparator)MyLess);
	 res = Heap_Extract(heap);
	ASSERT_THAT(res->m_length == max);

	vec =Heap_Destroy(&heap);
	Vector_Destroy(&vec,destroyFunc);

	free(res);

END_UNIT

/***********************************************************************************************/
UNIT(add_and_extrat_and_comper)

	size_t i;
	Rect* rects;
	Rect* res;
	DestroyFunc_t destroyFunc = (DestroyFunc_t) MyDysroy;

	Vector_t* vec = Vector_Create(100, 100);
	Heap* heap = Heap_Build(vec, (LessThanComparator)MyLess);

	for (i=0; i<11; ++i)
	{
		rects = calloc(1,sizeof(Rect));
		rects->m_length = i;
		rects->m_height = i;
		Heap_Insert ( heap, (void*)rects);
	}
	for (i=0; i<11; ++i)
	{
		rects = Heap_Peek(heap);
		res = Heap_Extract(heap);
		ASSERT_THAT(MyLess(rects,res)!= 1);
		free(res);
	}
	vec =Heap_Destroy(&heap);
	Vector_Destroy(&vec,destroyFunc);
END_UNIT

/***********************************************************************************************/

TEST_SUITE (Generic Heap Tests)
	TEST (test_Create_and_Destroy)
	TEST (test_Heap_Insert)
	TEST (add_and_extract)
	TEST (sorting_vector)
	TEST (add_and_extrat_and_comper)
END_SUITE



