#include <stdlib.h>
#include "../inc/queue.h"
#include "../inc/list.h"
#include "../inc/intern_list.h"
#include "../inc/list_itr.h"
#include "../inc/list_functions.h"
#include "../inc/macros.h"
#define MAGICNUMBER 0xFDFDFDFD


static Queue_Result listResToQueueRes(List_Result _res);
typedef void (destoyItem)(void* item);

struct Queue
{
    List* m_list;
    size_t m_magicNumber;
};

Queue* Queue_Create()
{
    Queue* newQueue;

    newQueue = malloc(sizeof(Queue));
    CHECK_EQUAL_RETURN(newQueue,NULL,NULL);

    newQueue->m_list = List_Create();
    if(NULL == newQueue)
    {
        free(newQueue);
        return NULL;
    }

    newQueue->m_magicNumber = MAGICNUMBER;

return newQueue;
}


void Queue_Destory(Queue** _pQueue, void (*_elementDestroy)(void* _item))
{
    if(NULL != _pQueue && NULL != *_pQueue &&  MAGICNUMBER == (*_pQueue)->m_magicNumber )
    {
        List_Destroy(&(*_pQueue)->m_list,_elementDestroy);
        (*_pQueue)->m_magicNumber = 0;
        free(*_pQueue);
        *_pQueue = NULL;
    }

return;
}

Queue_Result Queue_Enqueue(Queue* _pQueue, void* _pItem)
{
    List_Result res;

    CHECK_EQUAL_RETURN(_pQueue,NULL,QUEUE_UNINITIALIZED_ERROR);
    CHECK_EQUAL_RETURN(_pItem,NULL,QUEUE_UNINITIALIZED_ERROR);

    res = List_PushHead(_pQueue->m_list, _pItem);

return listResToQueueRes(res);
}

Queue_Result Queue_Dequeue(Queue* _pQueue, void** _pItem)
{
    List_Result res;

    CHECK_EQUAL_RETURN(_pQueue,NULL,QUEUE_UNINITIALIZED_ERROR);
    CHECK_EQUAL_RETURN(_pItem,NULL,QUEUE_UNINITIALIZED_ERROR);
    CHECK_EQUAL_RETURN(List_Size(_pQueue->m_list),0,QUEUE_UNDERFLOW);

    res = List_PopTail(_pQueue->m_list, _pItem);

return listResToQueueRes(res);
}

Queue_Result Queue_Top(Queue* _pQueue, void** _pItem)
{
    ListItr end;
    CHECK_EQUAL_RETURN(_pQueue,NULL,QUEUE_UNINITIALIZED_ERROR);
    CHECK_EQUAL_RETURN(_pItem,NULL,QUEUE_UNINITIALIZED_ERROR);
    CHECK_EQUAL_RETURN(List_Size(_pQueue->m_list),0,QUEUE_UNDERFLOW);

    end = ListItr_End(_pQueue->m_list);
    end = ListItr_Prev(end);
    CHECK_EQUAL_RETURN(end,NULL,QUEUE_UNINITIALIZED_ERROR);

    *_pItem = ListItr_Get(end);

return QUEUE_SUCCESS;
}


int Queue_isEmptey(Queue* _pQueue)
{
    return List_Size(_pQueue->m_list);
}

static Queue_Result listResToQueueRes(List_Result _res)
{
    switch (_res)
    {

    case LIST_SUCCESS:
        return QUEUE_SUCCESS;

	case LIST_UNINITIALIZED_ERROR:
	    return QUEUE_UNINITIALIZED_ERROR;

	case LIST_ALLOCATION_ERROR:
        return QUEUE_ALLOCATION_ERROR;

	case LIST_NULL_ELEMENT_ERROR:
        return 	QUEUE_NULL_ITEM_ERROR;

	case LIST_UNDERFLOW:
        return QUEUE_UNDERFLOW;
    }

return QUEUE_SUCCESS;
}



