#include <stdio.h>
#include <stdlib.h>/*for malloc*/
#include <math.h> /*for sqrt*/
#include <pthread.h>
#include "vector.h"
#include "safeThreadHashMap.h"
#include "macros.h"
#include "list_functions.h"
#include "list_itr.h"
#include "list.h"

#define MAGICNUMBER 0xDEADBABE
#define TRUE 1
#define FALSE 0
#define DEVIDED_NUMBER_FOR_NUMOFMUTEX  10
typedef void (*removVal)(void* _elemnt);
typedef void (*checkEqultyKey)(EqualityFunction Equality,void* m_key);


/******************************************/

typedef struct elementsRemover
{
	removVal m_destroyKey;
	removVal m_destroyValue;

} elementsRemover;

typedef struct ListItem
{
	void* m_key;
	void* m_value;

} ListItem;

typedef struct searchandkey
{

 EqualityFunction   m_equality;
 void* m_key;

}searchandkey;

struct STHashMap_t
{
    size_t   m_MagicNumber;
    Vector_t* m_vector;
    size_t   m_Size;
    size_t   m_NumberOfElements;
	size_t m_numOfMutexes;
	size_t	m_nSections; /* section is a range of indexes protected by one mutex */
	size_t	m_sectionSize; /* determined by requested number of mutexes */
    HashFunction     m_HashFunc;
    EqualityFunction     m_Equality;
    pthread_mutex_t	m_mainMutexes;
	pthread_mutex_t*	m_mutexes;

};

typedef struct actionandfunction
{
    KeyValueActionFunction action;
    void* contex;

}actionandfunction;

/********************internal function******************************************/
static size_t NextPrimeNumber(size_t _size);
static size_t isPrime(size_t _number);
static void removItemFromList(ListItem* _item,elementsRemover* elementsRemover);
static int searchduplic(List* _list,searchandkey* _searchkey, void** _ppitem,void** _ppListItr);
static size_t GetIndex(const STHashMap_t* _map , const void* _searchKey);
int seperadeKeyFromItem(ListItem* _item,searchandkey* _searchkey);
static Vector_t* MoveItemsFromOldVectorToNewVector(STHashMap_t* _map,size_t oldSize);
static int revVal(ListItem* _item, actionandfunction* _action);
static pthread_mutex_t* InitializeMutexes(size_t _size);
static void DestroyMutexes(pthread_mutex_t* _mutexes, size_t _size);
size_t GetSection(STHashMap_t* _map, size_t _index);
int static LockSection(STHashMap_t* _map, size_t _index);
int static UnlockSection(STHashMap_t* _map, size_t _index);
int HashMap_UnlockItem(STHashMap_t* _map, const void* _key);
int HashMap_LockItem(STHashMap_t* _map, const void* _key);
ListItem* NewItemInit(const void* _key, const void* _value);

STHashMap_t* HashMap_Create(size_t _capacity,HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    STHashMap_t* newSTHash = NULL;
    Vector_t* newVec;
    List* list;
    size_t newSize = 0, i =0, j = 0;


    CHECK_EQUAL_RETURN(0,_capacity,NULL);
    CHECK_EQUAL_RETURN(NULL,_hashFunc,NULL);
    CHECK_EQUAL_RETURN(NULL,_keysEqualFunc,NULL);

    newSTHash = (STHashMap_t*)malloc(sizeof(STHashMap_t));
    CHECK_EQUAL_RETURN(NULL,newSTHash,NULL);

    newSize = NextPrimeNumber(_capacity);
    /*set number of mutexs as devided of the new size*/
    newSTHash->m_numOfMutexes = DEVIDED_NUMBER_FOR_NUMOFMUTEX;
	/*set number of section that all mutex will respons on*/
	newSTHash->m_nSections = newSTHash->m_numOfMutexes;
	/*set  section size*/
	newSTHash->m_sectionSize = ceil((double)newSize / newSTHash->m_numOfMutexes);
	newSTHash->m_mutexes = InitializeMutexes(newSTHash->m_numOfMutexes);
    if(NULL == newSTHash->m_mutexes)
    {
        free(newSTHash);
        return NULL;
    }
    if(pthread_mutex_init(&newSTHash->m_mainMutexes,NULL))
    {
        DestroyMutexes(newSTHash->m_mutexes,newSTHash->m_numOfMutexes);
        free(newSTHash);
        return NULL;
    }
    newVec = Vector_Create(newSize,0);
    if(NULL == newVec)
    {
        pthread_mutex_destroy(&newSTHash->m_mainMutexes);
        DestroyMutexes(newSTHash->m_mutexes,newSTHash->m_numOfMutexes);
        free(newSTHash);
        return NULL;
    }

    /*create all lists from the begin to avoid the creaty and the cheeking in the future */
    for( i = 1; i <= newSize ;++i)
    {
        list = List_Create();
       if(VECTOR_SUCCESS != Vector_Append(newVec,list))
       {
           for(j=i ; j < 0 ; --i)
           {
                Vector_Get(newVec,i,(void*)&list);
                List_Destroy(&list,NULL);
            }
            pthread_mutex_destroy(&newSTHash->m_mainMutexes);
            DestroyMutexes(newSTHash->m_mutexes, i);
            Vector_Destroy(&newVec,NULL);
            free(newSTHash);
            return NULL;
        }
    }

    newSTHash->m_vector = newVec;
    newSTHash->m_Size = newSize;
    newSTHash->m_NumberOfElements = 0;
    newSTHash->m_MagicNumber = MAGICNUMBER;
    newSTHash->m_HashFunc = _hashFunc;
    newSTHash->m_Equality = _keysEqualFunc;

return newSTHash;
}



void HashMap_Destroy(STHashMap_t** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{

    elementsRemover* removingfunction;
    ListItr begin,end;
    size_t i,numberoflists;
    List* list;

    if(NULL != _map && NULL != *_map && MAGICNUMBER == (*_map)->m_MagicNumber)
    {

        removingfunction = calloc(1,sizeof(elementsRemover));
        CHECK_EQUAL_VOID_RETURN(NULL,removingfunction);
        removingfunction->m_destroyKey = _keyDestroy;
        removingfunction->m_destroyValue = _valDestroy;
        numberoflists = Vector_Size((*_map)->m_vector);

        /*cant use vector for each couse give memory to NULL removing function vector start at 1*/
        for(i = 1; i<=numberoflists ; ++i)
        {
            Vector_Get((*_map)->m_vector,i,(void*)&list);

            begin = ListItr_Begin(list);
            end = ListItr_End(list);
            ListItr_ForEach(begin,end,(ListActionFunction)removItemFromList,removingfunction);
            List_Destroy(&list,NULL);
        }
        free(removingfunction);
        pthread_mutex_destroy(&(*_map)->m_mainMutexes);
        DestroyMutexes((*_map)->m_mutexes,(*_map)->m_numOfMutexes);
        (*_map)->m_MagicNumber = 0;
        free(*_map);
        *_map= NULL;
    }

return;
}

Map_Result HashMap_Insert(STHashMap_t* _map, const void* _key, const void* _value)
{
    size_t index;
    List* list;
    ListItem* newitem;
    void* tempitr;
    searchandkey tempsearch;
    List_Result res;
    ListItem* tempitem;

    CHECK_EQUAL_RETURN(NULL,_map,MAP_UNINITIALIZED_ERROR);
    CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_map->m_MagicNumber,MAP_UNINITIALIZED_ERROR);
    CHECK_EQUAL_RETURN(NULL,_key,MAP_KEY_NULL_ERROR);
    CHECK_EQUAL_RETURN(NULL,_value,MAP_KEY_NULL_ERROR);

    index = GetIndex(_map,_key);
    HashMap_LockItem(_map, _key);
        Vector_Get(_map->m_vector,index, (void**)&list);
        tempsearch.m_equality = _map->m_Equality;
        tempsearch.m_key =(void*) _key;
        if(searchduplic(list,&tempsearch,(void*)&tempitem,(void*)&tempitr))
        {
            HashMap_UnlockItem(_map, _key);
            return MAP_KEY_DUPLICATE_ERROR;
        }
        newitem = NewItemInit(_key,_value);
        if(NULL == newitem)
        {
            HashMap_UnlockItem(_map, _key);
            return MAP_ALLOCATION_ERROR;
        }
        res = List_PushHead(list,newitem);
        if(LIST_SUCCESS != res)
        {
            free(newitem);
            HashMap_UnlockItem(_map, _key);
            return MAP_ALLOCATION_ERROR;
        }
        HashMap_UnlockItem(_map, _key);
        pthread_mutex_lock(&_map->m_mainMutexes);
            ++_map->m_NumberOfElements;
        pthread_mutex_unlock(&_map->m_mainMutexes);

return MAP_SUCCESS;
}

Map_Result HashMap_Find( STHashMap_t* _map, const void* _searchKey, KeyValueActionFunction _action ,void** _ppValue, void* _context)
{
    List* list;
    int anser;
    ListItem* tempitem;
    ListItr* tempitr;
    size_t index;
    searchandkey tempsearch;

    CHECK_EQUAL_RETURN(NULL,_map,MAP_UNINITIALIZED_ERROR);
    CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_map->m_MagicNumber,MAP_UNINITIALIZED_ERROR);
    CHECK_EQUAL_RETURN(NULL,_searchKey,MAP_KEY_NULL_ERROR);

    index = GetIndex(_map,_searchKey);
    HashMap_LockItem(_map, _searchKey);
        Vector_Get(_map->m_vector,index,(void*)&list);
        tempsearch.m_equality = _map->m_Equality;
        tempsearch.m_key =(void*) _searchKey;
        anser = searchduplic(list,&tempsearch,(void*)&tempitem,(void*)&tempitr);
        if(!anser)
        {
            HashMap_UnlockItem(_map, _searchKey);
            return MAP_KEY_NOT_FOUND_ERROR;
        }
        if(NULL == _action)
        {
            *_ppValue=tempitem->m_value;
        }
        else
        {
            _action(_searchKey,tempitem->m_value,_context);
        }
    HashMap_UnlockItem(_map, _searchKey);

return MAP_SUCCESS;
}

Map_Result HashMap_Remove(STHashMap_t* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
    List* list;
    size_t index;
    int anser;
    ListItem* itemToDestroy;
    ListItr* itrToRemove;
    searchandkey tempsearch;

    CHECK_EQUAL_RETURN(NULL,_map,MAP_UNINITIALIZED_ERROR);
    CHECK_NOTEQUAL_RETURN(MAGICNUMBER,_map->m_MagicNumber,MAP_UNINITIALIZED_ERROR);
    CHECK_EQUAL_RETURN(NULL,_pKey,MAP_KEY_NULL_ERROR);
    CHECK_EQUAL_RETURN(NULL,_pValue,MAP_KEY_NULL_ERROR);

    index =GetIndex(_map,_searchKey);
    HashMap_LockItem(_map, _searchKey);
        Vector_Get(_map->m_vector,index,(void*)&list);
        tempsearch.m_equality = _map->m_Equality;
        tempsearch.m_key =(void*) _searchKey;

        anser = searchduplic(list,&tempsearch,(void*)&itemToDestroy,(void*)&itrToRemove);
        if(!anser)
        {
            HashMap_UnlockItem(_map, _searchKey);
            return MAP_KEY_NOT_FOUND_ERROR;
        }

        *_pKey = itemToDestroy->m_key;
        *_pValue = itemToDestroy->m_value;
        itemToDestroy = ListItr_Remove(itrToRemove);
    HashMap_UnlockItem(_map, _searchKey);

        pthread_mutex_lock(&_map->m_mainMutexes);
            --_map->m_NumberOfElements;
        pthread_mutex_unlock(&_map->m_mainMutexes);

return MAP_SUCCESS;
}

size_t HashMap_Size( STHashMap_t* _map)
{
    size_t res = 0;
    CHECK_EQUAL_RETURN(NULL,_map,MAP_UNINITIALIZED_ERROR);
    CHECK_NOTEQUAL_RETURN(MAGICNUMBER ,_map->m_MagicNumber,MAP_UNINITIALIZED_ERROR);

    pthread_mutex_lock(&_map->m_mainMutexes);
        res =  _map->m_NumberOfElements;
    pthread_mutex_unlock(&_map->m_mainMutexes);

return res;
}

Map_Result HashMap_Rehash(STHashMap_t *_map, size_t newCapacity)
{
    Vector_t* newVec;
    size_t oldSize;

    CHECK_EQUAL_RETURN(NULL,_map,MAP_UNINITIALIZED_ERROR);
    CHECK_NOTEQUAL_RETURN(MAGICNUMBER ,_map->m_MagicNumber,MAP_UNINITIALIZED_ERROR);

    if(newCapacity <= _map->m_Size)
    {
        return MAP_ALLOCATION_ERROR;/*rename for null map or iligal size*/
    }
    pthread_mutex_lock(&_map->m_mainMutexes);

        /*keep the old size for removing the old vec later*/
        oldSize = _map->m_Size;
        _map->m_Size = NextPrimeNumber( newCapacity);

        newVec = MoveItemsFromOldVectorToNewVector(_map,oldSize);
        CHECK_EQUAL_RETURN(NULL,newVec,MAP_ALLOCATION_ERROR);

        Vector_Destroy(&_map->m_vector,NULL);
        _map->m_vector = newVec;

    pthread_mutex_unlock(&_map->m_mainMutexes);

return MAP_SUCCESS;
}

size_t HashMap_ForEach(const STHashMap_t* _map, KeyValueActionFunction _action, void* _context)
{
    size_t numberoflists,i;

    actionandfunction* action;
    ListItr begin,end;
    List* list;

    CHECK_EQUAL_RETURN(NULL,_map,FALSE);
    CHECK_NOTEQUAL_RETURN(MAGICNUMBER ,_map->m_MagicNumber,FALSE);
    CHECK_EQUAL_RETURN(NULL,_action,FALSE);

    action = malloc(sizeof(actionandfunction));
    CHECK_EQUAL_RETURN(NULL,action,FALSE);

    numberoflists = Vector_Size(_map->m_vector);
    action->action=_action;
    action->contex = _context;

    /*cant use vector for each couse give memory to NULL removing function*/
    for(i = 1; i<=numberoflists ; ++i)
    {
        LockSection((STHashMap_t*)_map,i);
            Vector_Get(_map->m_vector,i,(void*)&list);
            begin = ListItr_Begin(list);
            end = ListItr_End(list);
            ListItr_ForEach(begin,end,(ListActionFunction)revVal,action);
        UnlockSection((STHashMap_t*)_map,i);
    }
    free(action);
return TRUE;
}

#ifndef NDEBUG
Map_Stats* HashMap_GetStatistics(const STHashMap_t* _map)
{

    Map_Stats* newStatMap;
    size_t* numberOfChainLighnt;
    List* list;
    size_t i,maxChainNumber = 0;

    CHECK_EQUAL_RETURN(NULL,_map,NULL);
    CHECK_NOTEQUAL_RETURN(MAGICNUMBER ,_map->m_MagicNumber,NULL);

    newStatMap = malloc(sizeof(Map_Stats));
    CHECK_EQUAL_RETURN(NULL,newStatMap,NULL);

    numberOfChainLighnt = calloc(_map->m_Size,sizeof(int));
    CHECK_EQUAL_RETURN(NULL,numberOfChainLighnt,NULL);

    for(i = 1 ; i < _map->m_Size; ++i)
    {
        Vector_Get(_map->m_vector,i,(void*)&list);
        numberOfChainLighnt[i-1]= List_Size(list);
        if(numberOfChainLighnt[i-1] > maxChainNumber)
        {
            maxChainNumber = numberOfChainLighnt[i-1];
        }
    }

    newStatMap->numberOfBuckets = _map->m_Size;
    newStatMap->numberOfNonEmptyBuckets = _map->m_NumberOfElements;
    newStatMap->maxChainLength = maxChainNumber;
    newStatMap->averageChainLength = (maxChainNumber/_map->m_NumberOfElements);

return newStatMap;
}
#endif /* NDEBUG */

static int revVal(ListItem* _item, actionandfunction* _action)
{
    return ((KeyValueActionFunction)(_action->action)(_item->m_key,_item->m_value ,_action->contex));
}


static Vector_t* MoveItemsFromOldVectorToNewVector(STHashMap_t* _map,size_t oldSize)
{
    size_t i,index;
    Vector_t* newVec;
    ListItem* tempItem;
    List* oldListToremoveFrom;
    List* newListToInsertTo;
    /*List_Result res;*/
    Vector_Result res;
    ListItr* begin;
    ListItr* end;

    newVec = Vector_Create( _map->m_Size,0);
    CHECK_EQUAL_RETURN(NULL,newVec,NULL);

    /*creaty new ve and new lists ---- dose malloc check neads??*/
    for( i = 1; i <= _map->m_Size ;++i)
    {
        newListToInsertTo = List_Create();
        res = Vector_Append(newVec,newListToInsertTo);
        CHECK_NOTEQUAL_RETURN(VECTOR_SUCCESS ,res,NULL);

    }

    for(i = 1;i <= oldSize; ++i)
    {
        Vector_Get(_map->m_vector,i, (void**)&oldListToremoveFrom);
        begin = ListItr_Begin(oldListToremoveFrom);
        end = ListItr_End(oldListToremoveFrom);
        while (begin != end)
        {
            tempItem = ListItr_Get(begin);

            index = GetIndex(_map,tempItem->m_key);
            Vector_Get(newVec,index, (void**)&newListToInsertTo);/*get the list for new location for item*/
            res = List_PushHead(newListToInsertTo,tempItem); /* set the item in the new location*/

            begin = ListItr_Next(begin);
        }
        List_Destroy(&oldListToremoveFrom,NULL);
    }

return newVec;
}

static size_t GetIndex(const STHashMap_t* _map , const void* _searchKey)
{
    size_t index;
    index = _map->m_HashFunc(_searchKey);
    index = 1 + (index%_map->m_Size);

return index;

}
/* the function search duplicate items on the list*/
static int searchduplic(List* _list,searchandkey* _searchkey, void** _ppitem,void** _ppListItr)
{
    ListItr begin;
    ListItr end;
    begin = ListItr_Begin(_list);
    end = ListItr_End(_list);

    /*getting the item from the list and send to separed function */
    begin = ListItr_FindFirst(begin,end,(PredicateFunction)seperadeKeyFromItem,_searchkey);

    if(begin != end)
    {
        *_ppitem = ListItr_Get(begin);
        *_ppListItr=begin;
        return TRUE;
    }

return FALSE;
}

/* the function separed the key from struction and send to user equlty function*/
int seperadeKeyFromItem(ListItem* _item,searchandkey* _searchkey)
{
    return _searchkey->m_equality(_item->m_key,_searchkey->m_key);
}

static size_t NextPrimeNumber(size_t _size)
{
    while(!isPrime(_size))
    {
        ++_size;
    }
return  _size;
}

static size_t isPrime(size_t _number)
{
    size_t i;
    for(i=2; i < sqrt(_number);++i)
    {
        if( _number % i == 0)
        {
            return 0;
        }
    }
return 1;
}


/* removing items from list --- the function check for null pointers */
static void removItemFromList(ListItem* _item,elementsRemover* elementsRemover)
{

    if(NULL != *elementsRemover->m_destroyKey)
    {
        elementsRemover->m_destroyKey(_item->m_key);
    }

    if(NULL != *elementsRemover->m_destroyValue)
    {
       elementsRemover->m_destroyValue(_item->m_value);
    }

    free(_item);

return;
}

/*****************************************************/
static void DestroyMutexes(pthread_mutex_t* _mutexes, size_t _size)
{
	size_t i;
	for(i = 0; i < _size; ++i)
	{
		pthread_mutex_destroy(&_mutexes[i]);
	}
	free(_mutexes);

return;
}
/*****************************************************/
static pthread_mutex_t* InitializeMutexes(size_t _size)
{
	size_t i;
	int status;
	pthread_mutex_t* mutexes = (pthread_mutex_t*)malloc(_size * sizeof(pthread_mutex_t));

	if(!mutexes)
	{
		return NULL;
	}

	for(i = 0; i < _size; ++i)
	{
		status = pthread_mutex_init(&mutexes[i], NULL);
		if(status)
		{
			DestroyMutexes(mutexes, i);
			return NULL;
		}
	}

return mutexes;
}
/*******************************************************/
size_t GetSection(STHashMap_t* _map, size_t _index)
{
	return _index / _map->m_sectionSize;
}

/*********************************************************/
int static LockSection(STHashMap_t* _map, size_t _index)
{
	size_t section = GetSection(_map, _index);
	pthread_mutex_lock(&_map->m_mutexes[section]);
	return 0;
}

/*********************************************************/
int HashMap_LockItem(STHashMap_t* _map, const void* _key)
{
	size_t index = GetIndex(_map, _key);
	size_t section = GetSection(_map, index);
	pthread_mutex_lock(&_map->m_mutexes[section]);
	return 0;
}

/*********************************************************/
int HashMap_UnlockItem(STHashMap_t* _map, const void* _key)
{
	size_t index = GetIndex(_map, _key);
	size_t section = GetSection(_map, index);
	pthread_mutex_unlock(&_map->m_mutexes[section]);

return 0;
}

/*********************************************************/
int static UnlockSection(STHashMap_t* _map, size_t _index)
{
	size_t section = GetSection(_map, _index);
	pthread_mutex_unlock(&_map->m_mutexes[section]);

return 0;
}
/*********************************************************/
ListItem* NewItemInit(const void* _key,const void* _value)
{
    ListItem* newItem;

    newItem = (ListItem*)malloc(sizeof(ListItem));
    if(NULL == newItem)
    {
            return NULL;
    }

    newItem->m_key =(void*) _key;
    newItem->m_value =(void*) _value;

return newItem;
}
