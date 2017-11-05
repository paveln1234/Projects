#include <stdio.h>
#include <stdlib.h>/*for malloc*/
#include <pthread.h> /*for thread and mutex function*/
#include "macros.h"
#include "barrier.h"
#define MAGICNUMBER 0xDEADBEBE
#define CLOSE 0
#define OPEN 1


struct Barrier_t
{
    size_t m_magicNumber;
    size_t m_outCounter;
    size_t m_inCounter;
    size_t m_initCapacity;
    short int m_blackGateOfMordor;
    pthread_mutex_t m_mutex; /*mutext*/
    pthread_cond_t m_inGate; /*condition for barrier */
    pthread_cond_t m_outGate; /*condition for barrier */
};

Barrier_t* Barrier_Create(size_t _capacity)
{
    Barrier_t* newBarrier;

    newBarrier = (Barrier_t*) malloc(sizeof(Barrier_t));
    CHECK_EQUAL_RETURN(NULL, newBarrier, NULL);
    if(pthread_mutex_init(&newBarrier->m_mutex,NULL))
    {
        free(newBarrier);
        return NULL;
    }

    if((pthread_cond_init(&newBarrier->m_outGate,NULL))||(pthread_cond_init(&newBarrier->m_inGate,NULL)))
    {
        pthread_mutex_destroy(&newBarrier->m_mutex);
        free(newBarrier);
        return NULL;
    }

    newBarrier->m_initCapacity = _capacity;
    newBarrier->m_outCounter = _capacity;
    newBarrier->m_inCounter = 0;
    newBarrier->m_blackGateOfMordor = OPEN;
    newBarrier->m_magicNumber = MAGICNUMBER;

return newBarrier;
}

void Barrier_Destroy(Barrier_t* _barrier)
{
    if(NULL != _barrier && MAGICNUMBER == _barrier->m_magicNumber)
    {
       if(pthread_cond_destroy(&_barrier->m_outGate))
        {
                pthread_cond_broadcast(&_barrier->m_outGate);
                pthread_cond_destroy(&_barrier->m_outGate);
        }
        pthread_mutex_destroy(&_barrier->m_mutex);
        _barrier->m_magicNumber = 0;
        free(_barrier);
    }

return;
}

int Barrier_Wait(Barrier_t* _barrier ,actionFunc _action, void* _context)
{
    pthread_mutex_lock(&_barrier->m_mutex);
    while(_barrier->m_blackGateOfMordor == CLOSE)
    {
        pthread_cond_wait(&_barrier->m_inGate,&_barrier->m_mutex);
    }
    ++_barrier->m_inCounter;
    if(_barrier->m_inCounter == _barrier->m_initCapacity)
    {
       if(_action) _action(_context);
        _barrier->m_inCounter = 0;
        _barrier->m_blackGateOfMordor = CLOSE;
        pthread_cond_broadcast(&_barrier->m_outGate);
    }
    else
   {
       while(_barrier->m_blackGateOfMordor == OPEN)
       {
           pthread_cond_wait(&_barrier->m_outGate,&_barrier->m_mutex);
       }
   }
   --_barrier->m_outCounter;
   if(_barrier->m_outCounter == 0)
   {
        _barrier->m_outCounter = _barrier->m_initCapacity;
       _barrier->m_blackGateOfMordor = OPEN;
        pthread_cond_broadcast(&_barrier->m_inGate);
   }
    pthread_mutex_unlock(&_barrier->m_mutex);

return 0;
}
