#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../inc/list.h"
#include "../inc/list_itr.h"
#include "../inc/list_functions.h"
#include "../inc/intern_list.h"
#include "../inc/mu_test.h"

 struct Student
{
	char  name [20];
	size_t age;
	size_t ID;
} ;

typedef struct Student Student_t;



typedef void (*elementDestroy_t)(void*);


/*-------------------------------------------------------------------------------------------*/
void _elementDestroy(Student_t* _student)
{
	free (_student);
return;
}

/*-------------------------------------------------------------------------------------------*/

int MyPredicateFunction(Student_t* _a, void* _context)
{
	return _a->age > 5 ? 1 : 0;
}


int UserLessFunction (Student_t* _a , Student_t* _b)
{
	return _a->age > _b->age ? 1 : 0;
}

int UserEqualsFunc (Student_t* _a , Student_t* _b)
{
	return _a->ID == _b->ID ? 1 : 0;
}

int UserActionFunc(void* _element, void* _context)
{
	return _element == NULL ? 0 : 1;
}

void StDestroy(Student_t* St)
{
	free(St);
}

/***********************************************************************************************/
/********************************************************************************/

UNIT(test_Create)
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;
	List* list = NULL;
	list= List_Create();
	ASSERT_THAT(list != NULL);
	List_Destroy (&list, destroyFunc);
END_UNIT

/***********************************************************************************************/

UNIT(test_Destroy)
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;
	List* list = NULL;
	list= List_Create();
	List_Destroy (&list, destroyFunc);
	ASSERT_THAT(list ==NULL);
END_UNIT

/***********************************************************************************************/

UNIT(test_Push_Head)
	size_t result;
	Student_t* St= (Student_t*)malloc(1*sizeof(Student_t));
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	List* list = NULL;
	list= List_Create();
	List_PushHead(list,St);
	result = List_Size(list);
	ASSERT_THAT(result == 1);
	List_Destroy (&list, destroyFunc);
END_UNIT

/***********************************************************************************************/
UNIT(test_Push_Tail)
	size_t result;
        Student_t* St = (Student_t*)malloc(1*sizeof(Student_t));
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	List* list = NULL;
	list= List_Create();
	List_PushTail(list,St);
	result = List_Size(list);
	ASSERT_THAT(result == 1);
	List_Destroy (&list, destroyFunc);
END_UNIT

/***********************************************************************************************/
UNIT(test_Pop_Tail)
	size_t result;
   	void* St2 ;
	Student_t* St = (Student_t*)malloc(1*sizeof(Student_t));
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	List* list = NULL;
	list= List_Create();
	List_PushTail(list,St);
	List_PopTail(list, &St2);
	result = List_Size(list);
	ASSERT_THAT(result == 0);
	List_Destroy (&list, destroyFunc);
	free(St2);
END_UNIT
/***********************************************************************************************/
UNIT(test_Pop_Head)
	size_t result;
   	void* St2 ;
	Student_t* St = (Student_t*)malloc(1*sizeof(Student_t));
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	List* list = NULL;
	list= List_Create();
	List_PushTail(list,St);
	List_PopHead(list, &St2);
	result = List_Size(list);
	ASSERT_THAT(result == 0);
	List_Destroy (&list, destroyFunc);
	free(St2);
END_UNIT
/***********************************************************************************************/
UNIT(test_Push_and_Pop_many)
	int i;
	size_t result;
	void* St2;
	Student_t* St;
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	List* list = NULL;
	list= List_Create();
	for (i = 0 ; i < 1000 ; ++i)
	{
		St = (Student_t*)malloc(1*sizeof(Student_t));
		List_PushHead(list,St);
	}

		for (i = 0 ; i < 500 ; ++i)
	{
		List_PopHead(list, &St2);
		free(St2);
	}

	result = List_Size(list);
	ASSERT_THAT(result == 500);
	List_Destroy (&list, destroyFunc);


END_UNIT
/***********************************************************************************************/
UNIT(test_Pop_empty)
	List_Result result;
	void* St2;
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	List* list = NULL;
	list= List_Create();
	result = List_PopHead(list, &St2);
	ASSERT_THAT(result == LIST_UNDERFLOW);
	List_Destroy (&list, destroyFunc);
END_UNIT
/***********************************************************************************************/
UNIT(test_Push_without_create)
	List_Result result;
	Student_t* St = (Student_t*)malloc(1*sizeof(Student_t));
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	List* list = NULL;
	result = List_PushTail(list,St);

	ASSERT_THAT(LIST_UNINITIALIZED_ERROR == result);
	List_Destroy (&list, destroyFunc);
	free(St);
END_UNIT
/***********************************************************************************************/
UNIT(test_Push_Head_Push_Tail_and_Pop)
	int i;
	size_t result;
	void* St2;
	Student_t* St;
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	List* list = NULL;
	list= List_Create();
	for (i = 0 ; i < 10 ; ++i)
	{
		St = (Student_t*)malloc(1*sizeof(Student_t));
		List_PushHead(list,St);
	}

	for (i = 0 ; i < 10 ; ++i)
	{
		St = (Student_t*)malloc(1*sizeof(Student_t));
		List_PushTail(list,St);
	}

	for (i = 0 ; i < 15; ++i)
	{
		List_PopTail(list, &St2);
		free(St2);
	}

	result = List_Size(list);
	ASSERT_THAT(result == 5);
	List_Destroy (&list, destroyFunc);
END_UNIT

/***********************************ITR TESTS************************************************************/
UNIT(test_ListItr_Begin)
	int i;
	void* res;
	Student_t* St;
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	List* list = NULL;
	list= List_Create();
	for (i = 0 ; i < 1000 ; ++i)
	{
		St = (Student_t*)malloc(1*sizeof(Student_t));
		List_PushHead(list,St);
	}

	res = ListItr_Begin(list);
	ASSERT_THAT(res != NULL);
	List_Destroy (&list, destroyFunc);
END_UNIT

/***********************************************************************************************/

UNIT(count_items)
	List* list;
	int i;
	size_t num;
	Student_t* St;
	ListItr begin,end;
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	list = List_Create();
	for(i = 0; i < 10; ++i)
	{
		St = (Student_t*)malloc(1*sizeof(Student_t));
		St->age = i;
		St->ID = i;
		List_PushTail(list, St);
	}

	begin = ListItr_Begin(list);
	end = ListItr_End(list);

	num = ListItr_CountIf(begin, end, (PredicateFunction) MyPredicateFunction, NULL);
	ASSERT_THAT(num == 4);
	List_Destroy (&list, destroyFunc);
END_UNIT
/***********************************************************************************************/

UNIT(search_item)
	List* list;
	int i;
	Student_t* St;
	Student_t* St2;
	ListItr begin,end,res;

	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	list = List_Create();
	for(i = 0; i < 10; ++i)
	{
		St = (Student_t*)malloc(1*sizeof(Student_t));
		St->age = i;
		St->ID = i;
		List_PushTail(list, St);
	}

	begin = ListItr_Begin(list);
	end = ListItr_End(list);
	res = ListItr_FindFirst(begin, end, (PredicateFunction) MyPredicateFunction, NULL);
	ASSERT_THAT(NULL != res);
	St2 = ListItr_Get(res);
	ASSERT_THAT(St2->age == 6);

	List_Destroy (&list, destroyFunc);
END_UNIT
/***********************************************************************************************/
UNIT(test_for_each)
	List* list;
	int i;
	Student_t* St;
	Student_t* St2 = NULL;
	ListItr begin,end,res;

	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	list = List_Create();
	for(i = 0; i < 10; ++i)
	{
		St = (Student_t*)malloc(1*sizeof(Student_t));
		St->age = i;
		St->ID = i;
		List_PushTail(list, St);
	}

	begin = ListItr_Begin(list);
	end = ListItr_End(list);

	res = ListItr_ForEach(begin, end, (ListActionFunction) UserActionFunc, NULL);
	St2 = ListItr_Get(res);
	ASSERT_THAT(NULL == St2);
	List_Destroy (&list, destroyFunc);
END_UNIT
/***********************************************************************************************/

UNIT(sort_test)
	List* list;
	int i;
	Student_t* St;
	Student_t* St2 = NULL;
	ListItr begin,end;
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	list = List_Create();
	for(i = 9; i >= 0; --i)
	{
		St = (Student_t*)malloc(1*sizeof(Student_t));
		St->age = i;
		St->ID = i;
		List_PushTail(list, St);
	}

	begin = ListItr_Begin(list);
	end = ListItr_End(list);

	ListItr_Sort(begin,end, (LessFunction) UserLessFunction);
	St2 = ListItr_Get(begin);
	ASSERT_THAT(St2->age == 0);
	List_Destroy (&list, destroyFunc);

END_UNIT

/***********************************************************************************************/
/************************               TEST SUITE               *******************************/
/***********************************************************************************************/


TEST_SUITE (Linked List tests)
	TEST (test_Create)
	TEST (test_Destroy)
	TEST (test_Push_Head)
	TEST (test_Push_Tail)
	TEST (test_Pop_Tail)
	TEST (test_Pop_Head)
	TEST (test_Push_and_Pop_many)
	TEST (test_Pop_empty)
	TEST (test_Push_without_create)
	TEST (test_Push_Head_Push_Tail_and_Pop)

/*Itr Tests*/
	TEST(test_ListItr_Begin)
	TEST (count_items)
	TEST (search_item)
	TEST (test_for_each)
	TEST (sort_test)

END_SUITE
