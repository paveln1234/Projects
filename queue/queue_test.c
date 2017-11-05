#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/queue.h"
#include "../inc/mu_test.h"
#define SIZE 10

void DestroyItem(void* _item)
{
	free(_item);

return;
}

UNIT(creation)
	Queue* qu;

	qu = Queue_Create(SIZE);
	ASSERT_THAT(NULL != qu);
	Queue_Destory(&qu,DestroyItem);
    ASSERT_THAT(NULL == qu);
    qu = Queue_Create(0);
	ASSERT_THAT(NULL == qu);
    Queue_Destory(&qu,DestroyItem);
END_UNIT

UNIT(destruction)
	Queue* qu;

	qu = Queue_Create(SIZE);
	ASSERT_THAT(NULL != qu);
	Queue_Destory(&qu,DestroyItem);
    ASSERT_THAT(NULL == qu);

    qu = Queue_Create(SIZE);
	ASSERT_THAT(NULL != qu);
	Queue_Destory(&qu,NULL);
    ASSERT_THAT(NULL == qu);

    qu = Queue_Create(SIZE);
	ASSERT_THAT(NULL != qu);
	Queue_Destory(&qu,NULL);
    ASSERT_THAT(NULL == qu);

    qu = Queue_Create(SIZE);
	ASSERT_THAT(NULL != qu);
	Queue_Destory(NULL,NULL);
    ASSERT_THAT(NULL != qu);

    Queue_Destory(&qu,NULL);
    ASSERT_THAT(NULL == qu);

END_UNIT



UNIT(insert)
	Queue* qu;
    int* number;
    int i;


	qu = Queue_Create(SIZE);
	for (i = 0; i< SIZE ;++i )
    {
        number = malloc(sizeof(int));
        ASSERT_THAT(Queue_Enqueue(qu,number) == QUEUE_SUCCESS);
    }
    ASSERT_THAT(Queue_Enqueue(NULL,number) == QUEUE_UNINITIALIZED_ERROR);
    ASSERT_THAT(Queue_Enqueue(qu,NULL) == QUEUE_UNINITIALIZED_ERROR);

    Queue_Destory(&qu,DestroyItem);
END_UNIT

UNIT(inserttest2)
	Queue* qu;
    int* number;
    int i;

	qu = Queue_Create(SIZE);
	for (i = 0; i< SIZE ;++i )
    {
        number = malloc(sizeof(int));
        ASSERT_THAT(Queue_Enqueue(qu,number) == QUEUE_SUCCESS);
    }

    ASSERT_THAT(Queue_Enqueue(NULL,number) == QUEUE_UNINITIALIZED_ERROR);
    ASSERT_THAT(Queue_Enqueue(qu,NULL) == QUEUE_UNINITIALIZED_ERROR);

    Queue_Destory(&qu,DestroyItem);
END_UNIT


UNIT(removeItem)
	Queue* qu;
    char* res;

	qu = Queue_Create(SIZE);
    ASSERT_THAT(Queue_Enqueue(qu,"pavel") == QUEUE_SUCCESS);
	ASSERT_THAT(Queue_Enqueue(qu,"gilat") == QUEUE_SUCCESS);
	ASSERT_THAT(Queue_Enqueue(qu,"nadav") == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Dequeue(qu,(void*)&res) == QUEUE_SUCCESS);
    ASSERT_THAT(strcmp(res,"pavel")== 0 );
    ASSERT_THAT(Queue_Dequeue(qu,(void*)&res) == QUEUE_SUCCESS);
    ASSERT_THAT(strcmp(res,"gilat")== 0 );
    ASSERT_THAT(Queue_Dequeue(qu,(void*)&res) == QUEUE_SUCCESS);
    ASSERT_THAT(strcmp(res,"nadav")== 0 );

    Queue_Destory(&qu,NULL);

END_UNIT

UNIT(removeItemunderflow)
	Queue* qu;
    char* res;

	qu = Queue_Create(SIZE);
    ASSERT_THAT(Queue_Enqueue(qu,"pavel") == QUEUE_SUCCESS);
	ASSERT_THAT(Queue_Enqueue(qu,"gilat") == QUEUE_SUCCESS);
	ASSERT_THAT(Queue_Enqueue(qu,"nadav") == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Dequeue(qu,(void*)&res) == QUEUE_SUCCESS);
    ASSERT_THAT(strcmp(res,"pavel")== 0 );
    ASSERT_THAT(Queue_Dequeue(qu,(void*)&res) == QUEUE_SUCCESS);
    ASSERT_THAT(strcmp(res,"gilat")== 0 );
    ASSERT_THAT(Queue_Dequeue(qu,(void*)&res) == QUEUE_SUCCESS);
    ASSERT_THAT(strcmp(res,"nadav")== 0 );
    ASSERT_THAT(Queue_Dequeue(qu,(void*)&res) == QUEUE_UNDERFLOW);
    Queue_Destory(&qu,NULL);

END_UNIT

UNIT(popItem)
	Queue* qu;
    char* res;

	qu = Queue_Create(SIZE);
    ASSERT_THAT(Queue_Enqueue(qu,"pavel") == QUEUE_SUCCESS);
	ASSERT_THAT(Queue_Enqueue(qu,"gilat") == QUEUE_SUCCESS);
	ASSERT_THAT(Queue_Enqueue(qu,"nadav") == QUEUE_SUCCESS);
    ASSERT_THAT(Queue_Top(qu,(void*)&res) == QUEUE_SUCCESS);
    ASSERT_THAT(strcmp(res,"pavel")== 0 );
    ASSERT_THAT(Queue_Dequeue(qu,(void*)&res) == QUEUE_SUCCESS);
    ASSERT_THAT(strcmp(res,"pavel")== 0 );
    ASSERT_THAT(Queue_Dequeue(qu,(void*)&res) == QUEUE_SUCCESS);
    ASSERT_THAT(strcmp(res,"gilat")== 0 );
    Queue_Destory(&qu,NULL);

END_UNIT



TEST_SUITE(Generic HashMap Tests)
	TEST(creation)
	TEST(destruction)
	TEST(insert)
	TEST(inserttest2)
	TEST(removeItem)
	TEST(removeItemunderflow)
    TEST(popItem)
END_SUITE

