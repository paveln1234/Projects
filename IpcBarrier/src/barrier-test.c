#include <stdio.h>
#include <stdlib.h>/*for malloc*/
#include <unistd.h>
#include <pthread.h> /*for thread and mutex function*/
#include "macros.h"
#include "barrier.h"
typedef struct TestThread_t
{
    int* m_killinOrkNumerPerHero;
    size_t m_threadId;
    size_t m_numerOfItemsInArray;
    Barrier_t* m_barrier;
    int m_nLoop;
}TestThread_t;

void printStatusOnGate(void* _context)
{
    char *str = _context;

    printf("%s\n",str);

return;
}

int HeroKillingDraft(int n)
{
   if ( n == 0 )
      return 0;
   else if ( n == 1 )
      return 1;
   else
      return ( HeroKillingDraft(n-1) + HeroKillingDraft(n-2) );
}


void* PruducerFunc(void* _test)
{
    char str1[] = {"*******************open the outgate****************************\n"};

    TestThread_t* test = _test;
    int i = 0;
    for(i=0; i < test->m_nLoop; ++i)
    {
        printf("round %d Hero number %ld start fight \n",i+1,test->m_threadId);
        test->m_killinOrkNumerPerHero[test->m_threadId] = HeroKillingDraft(test->m_threadId+1);
     /*   printf("Hero number %ld go to arrive to the Black Gate Of Mordor and he waiitnig to his gang  \n",test->m_threadId);*/
        Barrier_Wait(test->m_barrier,printStatusOnGate,(void*)str1);
        printf("Hero number %ld start the attack on Mordor \n",test->m_threadId);
    }

return NULL;
}

void* ConsumerFunc(void* _test)
{
    char str1[] = {"*******************open the outgate****************************\n"};
    size_t i =0 ,z=0;
    size_t counter = 0;
    TestThread_t* test = _test;
    for(i=0; i < test->m_nLoop; ++i)
    {
        printf("Dead counter  go to Black Gate Of Mordor  at %ld time where the action are::: \n",i+1);
        Barrier_Wait(test->m_barrier,printStatusOnGate,(void*)str1);
        printf("Dead counter return from the Gate and start calculate How many Ork died in the fight \n");
        for(z=0; z<test->m_numerOfItemsInArray; ++z)
        {
                counter += test->m_killinOrkNumerPerHero[z];
        }
        printf("the Number Of diad Orks are %ld \n",counter);

    }
return NULL;
}

void setUpTest(TestThread_t* _test,size_t _threadId, Barrier_t* _barrier,size_t _num,int _loop, int* _array)
{
    _test->m_barrier = _barrier;
    _test->m_killinOrkNumerPerHero=_array;
    _test->m_threadId = _threadId;
    _test->m_numerOfItemsInArray = _num;
    _test->m_nLoop = _loop;
return;
}

void ThreadCreateFunc(size_t _numberOfThreadToCreate,int _loop)
{

    size_t i = 0;
    size_t counter = _numberOfThreadToCreate +1;
    pthread_t* threads = calloc(counter,sizeof(pthread_t));
    TestThread_t* newTest = calloc(counter,sizeof(TestThread_t));
    newTest->m_killinOrkNumerPerHero = calloc(counter,sizeof(int));
    newTest->m_barrier = Barrier_Create(counter);
    newTest->m_numerOfItemsInArray = counter;

    for(i = 0; i < _numberOfThreadToCreate ; ++i)
    {

            setUpTest(&newTest[i],i+1,newTest->m_barrier,counter,_loop,newTest->m_killinOrkNumerPerHero);
            pthread_create(&threads[i],NULL,PruducerFunc,&newTest[i]);

    }
    setUpTest(&newTest[i],i+1,newTest->m_barrier,counter,_loop,newTest->m_killinOrkNumerPerHero);
    pthread_create(&threads[i],NULL,ConsumerFunc,&newTest[i]);

    for(i = 0; i<counter ; ++i)
    {
        pthread_join(threads[i],NULL);
    }
    Barrier_Destroy(newTest->m_barrier);

return;
}

int main (int argc, char* argv[])
{
int i = atoi(argv[1]);
int loop = atoi(argv[2]);
#ifndef NDEBUG
    int i = 40;
    int loop = 4;
#endif /* NDEBUG*/
printf("welcome young hobbit \n");
sleep(1);
printf("get ready for the big fight on The Black Gate Of Mordor\n");
sleep(1);
printf("your company is %d members and there will be %d round of fight \n",i,loop);

ThreadCreateFunc(i,loop);


return 1;
}

