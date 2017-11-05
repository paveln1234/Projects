#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string.h>
#include "../inc/mu_test.h"
#include "../inc/stack.h"
#define LOOP 17
#define RANDOM 99

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
void StDestroy(Student_t* St)
{
	free(St);
}

/**====================================== TESTS =============================================*/
/********************************************************************************/

UNIT(test_Create)

	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	Stack* stack = NULL;
	stack = Stack_Create();
	ASSERT_THAT(stack != NULL);

	Stack_Destroy(&stack,  destroyFunc);
	ASSERT_THAT(NULL == stack);

END_UNIT

/********************************************************************************/

UNIT(test_Destroy)

	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;

	Stack* stack = NULL;
	stack = Stack_Create();

	ASSERT_THAT(stack != NULL);

	Stack_Destroy(&stack,  destroyFunc);
	ASSERT_THAT(NULL == stack);

END_UNIT


/***********************************************************************************************/
UNIT(test_Stack_Insert)

	Stack* stack = NULL;
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;
	Student_t* St= (Student_t*)malloc(1*sizeof(Student_t));

	stack= Stack_Create();
	ASSERT_THAT(Stack_Push(stack,St) == STACK_SUCCESS);
	ASSERT_THAT( Stack_Size (stack)  != 0 );
	Stack_Destroy(&stack,  destroyFunc);
	ASSERT_THAT(NULL == stack);
END_UNIT

/***********************************************************************************************/
UNIT(test_Stack_Insert_Many)

	size_t i;
	Student_t* St;
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;
	Stack* stack = NULL;


	stack= Stack_Create();
	for (i = 0 ; i < 1000 ; ++i)
	{
		St = (Student_t*)malloc(1*sizeof(Student_t));
		ASSERT_THAT(Stack_Push(stack,St) == STACK_SUCCESS);
	}

	ASSERT_THAT( Stack_Size (stack) == 1000 );
	Stack_Destroy(&stack,  destroyFunc);
	ASSERT_THAT(NULL == stack);
	END_UNIT
/***********************************************************************************************/
UNIT(test_Stack_Pop)

	Stack* stack = NULL;
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;
	Student_t* St2 = NULL;
	Student_t* St= (Student_t*)malloc(1*sizeof(Student_t));

	stack= Stack_Create();
	ASSERT_THAT(Stack_Push(stack,St) == STACK_SUCCESS);
	ASSERT_THAT( Stack_Size (stack)  != 0 );
	ASSERT_THAT(Stack_Pop(stack,(void*)&St2) == STACK_SUCCESS);
	ASSERT_THAT(NULL != St2 );
	ASSERT_THAT( Stack_Size (stack)  == 0 );

	Stack_Destroy(&stack,  destroyFunc);
	ASSERT_THAT(NULL == stack);
	free(St2);
END_UNIT

/***********************************************************************************************/

UNIT(test_Push_and_Pop_many)
	size_t i;
	Stack* stack;
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;
	Student_t* St2 = NULL;
	Student_t* St= (Student_t*)malloc(1*sizeof(Student_t));

	stack= Stack_Create();
	for (i = 0 ; i < 1000 ; ++i)
	{
		St = (Student_t*)malloc(1*sizeof(Student_t));
		ASSERT_THAT(Stack_Push(stack,St) == STACK_SUCCESS);
	}

		for (i = 0 ; i < 500 ; ++i)
	{
		ASSERT_THAT(Stack_Pop(stack,(void*)&St2) == STACK_SUCCESS);
		free(St2);
	}
	ASSERT_THAT( Stack_Size (stack)  == 500 );
	Stack_Destroy(&stack,  destroyFunc);
	ASSERT_THAT(NULL == stack);
END_UNIT
/***********************************************************************************************/
UNIT(test_Stack_Pop_from_Empty)
	Stack* stack;
	int* Item;
	stack = Stack_Create ();

	ASSERT_THAT( Stack_Pop ( stack, (void*)&Item ) == STACK_UNDERFLOW );

	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;
	Stack_Destroy(&stack,  destroyFunc);

	ASSERT_THAT(NULL == stack);


END_UNIT

/***********************************************************************************************/
UNIT(test_Stack_Double_Destroy)
	Stack* stack;
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;


	stack = Stack_Create ();

	Stack_Destroy(&stack,  destroyFunc);
	Stack_Destroy(&stack,  destroyFunc);
	ASSERT_THAT( NULL == stack );

END_UNIT


/***********************************************************************************************/

TEST_SUITE (stack test unit)

	TEST (test_Create)
	TEST (test_Destroy)
	TEST (test_Stack_Insert)
	TEST (test_Stack_Insert_Many)
	TEST(test_Stack_Pop)
	TEST (test_Push_and_Pop_many)
	TEST(test_Stack_Pop_from_Empty)
	TEST (test_Stack_Double_Destroy)

END_SUITE



