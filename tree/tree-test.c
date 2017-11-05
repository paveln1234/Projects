#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../inc/tree.h"
#include "../inc/mu_test.h"

typedef  struct Student_t
{
	char  name [20];
	size_t age;
	size_t ID;
} Student_t;

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
	Tree* tree = NULL;
	tree = Tree_Create();

	ASSERT_THAT(NULL != tree);
	Tree_Destroy(tree);
END_UNIT

/***********************************************************************************************/

UNIT(test_Destroy)
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;
	Tree* tree = NULL;

	tree = Tree_Create();
    ASSERT_THAT(NULL != tree);
	Tree_Destroy(tree);
	ASSERT_THAT(NULL == tree);

END_UNIT

/***********************************************************************************************/

UNIT(test_Push_Head)
	elementDestroy_t destroyFunc = (elementDestroy_t) _elementDestroy;
	Tree* tree = NULL;

	tree = Tree_Create();
	Tree_Destroy(tree);
	ASSERT_THAT(NULL == tree);

END_UNIT


/***********************************************************************************************/
/************************               TEST SUITE               *******************************/
/***********************************************************************************************/


TEST_SUITE (Test tests)
	TEST (test_Create)
	TEST (test_Destroy)
	/*TEST (test_Push_Head)*/

END_SUITE
