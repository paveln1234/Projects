#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>/*mutex*/
#include "mu_test.h"
#include "safeThreadQueue.h"
#define SIZE 4
#define ALIVE 1;
#define DEAD 0;
#define NUMBER 200

typedef struct Rect
{
	size_t m_height;
	size_t m_length;
} Rect_t;

void RectDestroy(Rect_t* _rect)
{
	free(_rect);
}

void* threadFunc(void* _context)
{
	int i;
	int num;
	STQueueu_t* _queue =(STQueueu_t*)_context;

	for(i = 0; i < 100000; ++i)
	{
		num = rand() % 1000;
		SafeTreadQueue_Enqueue(_queue, &num);
	}

return NULL;
}

void*  ExtractionThread(void* _context)
{
	int i;
	int* num;
	STQueueu_t* _queue =(STQueueu_t*)_context;
	for(i = 0; i < 100000; ++i)
	{
		SafeTreadQueue_Dequeue(_queue, (void**)&num);
	}
return NULL;
}

UNIT(insert_and_remove)
	int i;
	Rect_t rects[1000];
	Rect_t* rect;
	STQueueu_t* queue;
	queue = SafeThreadQueue_Create(1000);
	for(i = 0; i < 1000; ++i)
	{
		rects[i].m_height = i;
		rects[i].m_length = i;
		ASSERT_THAT(SafeTreadQueue_Enqueue(queue, &rects[i])==SAFE_TREAD_QUEUE_SUCCESS);
	}
	for(i = 0; i < 1000; ++i)
	{
		ASSERT_THAT(SafeTreadQueue_Dequeue(queue, (void**)&rect) ==SAFE_TREAD_QUEUE_SUCCESS);
		ASSERT_THAT(rect->m_height == i);
	}
	SafeTreadQueue_Destroy(queue, NULL);
END_UNIT

UNIT(creationANDdesroy)
	STQueueu_t* queue;
	int i;
	void* junk;
	pthread_t threads[200];
	ASSERT_THAT(NULL !=(queue =SafeThreadQueue_Create(1000000000)));
	for(i = 0; i < 200; ++i)
	{
		pthread_create(&threads[i], NULL, threadFunc, queue);
	}

	for(i = 0; i < 200; ++i)
	{
		pthread_join(threads[i], &junk);
	}

	for(i = 0; i < 200 * 100000; ++i)
	{
		ASSERT_THAT(SafeTreadQueue_Dequeue(queue, &junk) == SAFE_TREAD_QUEUE_SUCCESS);
	}
END_UNIT

UNIT(creationANDdesroy2)
	STQueueu_t* queue;
	int i;
	void* junk;
	pthread_t threads[200];
	ASSERT_THAT(NULL !=(queue =SafeThreadQueue_Create(1000000000)));
	for(i = 0; i < 200; ++i)
	{
		pthread_create(&threads[i], NULL, threadFunc, queue);
	}
	for(i = 0; i < 200; ++i)
	{
		pthread_join(threads[i], &junk);
	}

	for(i = 0; i < 200; ++i)
	{
		pthread_create(&threads[i], NULL, ExtractionThread, queue);
	}
	for(i = 0; i < 200; ++i)
	{
		pthread_join(threads[i], &junk);
	}

END_UNIT


TEST_SUITE(SafeThreadQueue_test)
	TEST(insert_and_remove)
	TEST(creationANDdesroy)
	TEST(creationANDdesroy2)

END_SUITE
