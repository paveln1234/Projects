#include <stdio.h>/*calloc maloc*/
#include <stdlib.h>/*size_t */
#include <pthread.h>/*mutex*/
#include "safeThreadQueue.h"
#include "queue.h"
#define MAGICNUMBER 0xDEADBEAB

/* Define Struct safeThreadQueue*/
struct STQueueu_t
{
    size_t m_magicNumber;
    Queue* m_queue;
    pthread_mutex_t m_mutex;
    pthread_cond_t m_isFull;
    pthread_cond_t m_isEmpty;
    size_t m_numOfItems;
    size_t m_isFullQueue;
    size_t m_isEmptyQueue;
};


/* create new safeThread  Thread Queue */
STQueueu_t* SafeThreadQueue_Create(size_t  _numOfSlots)
{
    STQueueu_t* newSqueue;

    if(0 == _numOfSlots)
    {
        return NULL;
    }
    newSqueue = (STQueueu_t*) malloc(sizeof(STQueueu_t));
    if(NULL == newSqueue)
    {
        return NULL;
    }

    /*set gen_queue*/
    newSqueue->m_queue = Queue_Create();
    if(NULL == newSqueue->m_queue)
    {
        free(newSqueue);
        return NULL;
    }
    /*set mutex variables*/
    if(pthread_mutex_init(&newSqueue->m_mutex,NULL))
    {
        Queue_Destory(&newSqueue->m_queue,NULL);
        free(newSqueue);
        return NULL;
    }

    if(pthread_cond_init(&newSqueue->m_isFull,NULL))
    {
        pthread_mutex_destroy(&newSqueue->m_mutex);
        Queue_Destory(&newSqueue->m_queue,NULL);
        free(newSqueue);
        return NULL;
    }

    if(pthread_cond_init(&newSqueue->m_isEmpty,NULL))
    {
        pthread_cond_destroy(&newSqueue->m_isFull);
        pthread_mutex_destroy(&newSqueue->m_mutex);
        Queue_Destory(&newSqueue->m_queue,NULL);
        free(newSqueue);
        return NULL;
    }

    newSqueue->m_numOfItems =0;
    newSqueue->m_isFullQueue= 0;
    newSqueue->m_isEmptyQueue = _numOfSlots;
    newSqueue->m_magicNumber = MAGICNUMBER;

return newSqueue;
}

/*Destroy Safe Tread Queue function*/
STQueueu_Result SafeTreadQueue_Destroy(STQueueu_t*  _sQueue, destroyFuncion _destroyFuncion)
{

    if(NULL ==_sQueue || MAGICNUMBER != _sQueue->m_magicNumber )
    {
        return SAFE_TREAD_QUEUE_UNINITIALIZED_ERROR;
    }
    if(NULL != _destroyFuncion)
    {
            Queue_Destory(&(_sQueue)->m_queue,_destroyFuncion);
    }

    pthread_cond_destroy(&_sQueue->m_isEmpty);
    pthread_cond_destroy(&_sQueue->m_isFull);
    pthread_mutex_destroy(&_sQueue->m_mutex);
    _sQueue->m_magicNumber = 0;
    free(_sQueue);
return SAFE_TREAD_QUEUE_SUCCESS;
}


STQueueu_Result SafeTreadQueue_Enqueue(STQueueu_t* _sQueue, void* _item)
{
    if(NULL == _sQueue || MAGICNUMBER != _sQueue->m_magicNumber)
    {
        return SAFE_TREAD_QUEUE_UNINITIALIZED_ERROR;
    }

    if(NULL == _item)
    {
        return SAFE_TREAD_QUEUE_ITEM_ERROR;
    }

    /*lock the insert mutex*/
    pthread_mutex_lock(&_sQueue->m_mutex);
    /* check if there have free slot if not  wait */
    while(_sQueue->m_isEmptyQueue == 0)
    {
        pthread_cond_wait(&_sQueue->m_isFull,&_sQueue->m_mutex);
    }
    --_sQueue->m_isEmptyQueue;
    ++_sQueue->m_isFullQueue;
    ++_sQueue->m_numOfItems;
    Queue_Enqueue(_sQueue->m_queue,_item);

    /*unlock the mutext and signal to one thread in the dequeue to waik up*/
    pthread_mutex_unlock(&_sQueue->m_mutex);
    pthread_cond_broadcast(&_sQueue->m_isEmpty);

return SAFE_TREAD_QUEUE_SUCCESS;
}

/************************************************************/
STQueueu_Result SafeTreadQueue_Dequeue(STQueueu_t* _sQueue,void** _pItem)
{
    if(NULL == _sQueue || MAGICNUMBER != _sQueue->m_magicNumber)
    {
        return SAFE_TREAD_QUEUE_UNINITIALIZED_ERROR;
    }

    if(NULL == _pItem)
    {
        return SAFE_TREAD_QUEUE_ITEM_ERROR;
    }

    /*lock the insert mutex*/
    pthread_mutex_lock(&_sQueue->m_mutex);
    /* wait if no items to remove */
    while(_sQueue->m_isFullQueue == 0)
    {
        pthread_cond_wait(&_sQueue->m_isEmpty,&_sQueue->m_mutex);
    }
    ++_sQueue->m_isEmptyQueue;
    -- _sQueue->m_isFullQueue;
    --_sQueue->m_numOfItems;
    Queue_Dequeue(_sQueue->m_queue,_pItem);

    /*unlock the mutext and signal to one thread in the enqueue to waik up*/
    pthread_mutex_unlock(&_sQueue->m_mutex);
    pthread_cond_broadcast(&_sQueue->m_isFull);

return SAFE_TREAD_QUEUE_SUCCESS;
}
/************************************************************/
size_t SafeTreadQueue_NumOfItemsInQueue(STQueueu_t* _sQueue)
{
    size_t size = 0;

    if(NULL !=_sQueue && MAGICNUMBER == _sQueue->m_magicNumber )
    {
        pthread_mutex_lock(&_sQueue->m_mutex);
        size = _sQueue->m_numOfItems;
        pthread_mutex_unlock(&_sQueue->m_mutex);
    }

return size;
}

