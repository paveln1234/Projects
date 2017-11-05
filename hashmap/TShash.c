#include <stdlib.h> /* for malloc */
#include <math.h> /* TSHashMap_Create, for finding next prime number */
#include <stdio.h>
#include <pthread.h>

#include "list_functions.h"
#include "TSHashMap.h"

#define ALIVE_MAGIC_NUMBER 0xbeefbeef
#define FALSE 0
#define TRUE 1

#define CHECK_KEY(i) if(!i) return MAP_KEY_NULL_ERROR;
#define CHECK_MAP if(!_map || 0xbeefbeef != _map->m_magicNumber) return MAP_UNINITIALIZED_ERROR;
#define NDEBUG
 
typedef struct Item Item;
typedef struct IsEqualContext IsEqualContext;
typedef struct DestroyContext DestroyContext;
typedef void (*voidAction)(void*);
void DestroyMutexes(pthread_mutex_t* _mutexes, size_t _size);

static int ItemDestroy(void* _element, void* _context);
static size_t FindNextPrime(size_t _num);
static int IsPrime(size_t _num);
static int IsItemFound(TSHashMap* _map, const void* _key, ListItr* _lastPlace);
static size_t GetIndex(TSHashMap* _map, const void* _key);
static Item* Item_Create(const void* _key, const void* _value);
static int IsKeyEqual(void *_element, void* _context);
/*=====================================================================================================================================================================================================*/

struct TSHashMap
{
	size_t			m_magicNumber;
	size_t 			m_originalSize;
	size_t 			m_nBuckets;
	List** 			m_map;
	pthread_mutex_t*	m_mutexes;
	size_t			m_nSections; /* section is a range of indexes protected by one mutex */
	size_t			m_sectionSize; /* determined by requested number of mutexes */
	HashFunction 		m_hashFunc;
	EqualityFunction	m_equal;
};

struct Item
{
	void* m_key;
	void* m_value;
};

struct IsEqualContext
{
	void*			m_key;
	EqualityFunction	m_equal;
};

struct DestroyContext
{
	voidAction m_keyDestroy;
	voidAction m_valueDestroy;
};

/*=====================================================================================================================================================================================================*/

void TSHashMap_Destroy(TSHashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	TSHashMap map = **_map;
	size_t i, lists;
	ListItr begin, end;
	DestroyContext cont;
	
	if(!_map || !*_map)
	{
		return;
	}
	
	lists = map.m_nBuckets;
	cont.m_keyDestroy = _keyDestroy;
	cont.m_valueDestroy = _valDestroy;
	for(i = 0; i < lists; ++i)
	{
		if(map.m_map[i])
		{
			begin = ListItr_Begin(map.m_map[i]);
			end = ListItr_End(map.m_map[i]);
			ListItr_ForEach(begin, end, ItemDestroy, &cont);
			List_Destroy(&map.m_map[i], NULL);
		}
	}
	DestroyMutexes(map.m_mutexes, map.m_nSections);	
	free((*_map)->m_map);
	free(*_map);
	*_map = NULL;
}
/*=====================================================================================================================================================================================================*/

void DestroyMutexes(pthread_mutex_t* _mutexes, size_t _size)
{
	size_t i;
	for(i = 0; i < _size; ++i)
	{
		pthread_mutex_destroy(&_mutexes[i]);	
	}
	free(_mutexes);
}

/*=====================================================================================================================================================================================================*/
pthread_mutex_t* InitializeMutexes(size_t _size)
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

/*=====================================================================================================================================================================================================*/

TSHashMap* TSHashMap_Create(size_t _capacity, size_t _nMutexes, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	size_t actualSize;
	TSHashMap* hash;
	
	if(!_capacity || !_hashFunc || !_keysEqualFunc)
	{
		return NULL;
	}
	
	hash = (TSHashMap*)malloc(sizeof(TSHashMap));
	if(!hash) 
	{
		return NULL;
	}

	actualSize = FindNextPrime(_capacity + 1);
	hash->m_map = (List**)calloc(actualSize, sizeof(List*));
	if(!hash->m_map)
	{
		free(hash);
		return NULL;
	}

	hash->m_mutexes = InitializeMutexes(_nMutexes);
	if(!hash->m_mutexes)
	{
		free(hash->m_map);
		free(hash);
		return NULL;
	}
	
	hash->m_nSections = _nMutexes;
	hash->m_sectionSize = ceil((double)actualSize / _nMutexes);
	hash->m_originalSize = _capacity;
	hash->m_nBuckets = actualSize;
	hash->m_magicNumber = ALIVE_MAGIC_NUMBER;
	hash->m_hashFunc = _hashFunc;
	hash->m_equal = _keysEqualFunc;
	
	return hash;
}

/*=====================================================================================================================================================================================================*/
 
static size_t FindNextPrime(size_t _num)
{
	while(!IsPrime(_num))
	{
		++_num;
	}
	return _num;
}

/*=====================================================================================================================================================================================================*/

static int IsPrime(size_t _num)
{
	size_t i;
	
	for(i = 2; i<=sqrt(_num); ++i)
	{
		if(0 == _num % i)
		{	
			return FALSE;
		}
	}
	return TRUE;
}
/*=====================================================================================================================================================================================================*/

size_t GetSection(TSHashMap* _map, size_t _index)
{
	return _index / _map->m_sectionSize;	
}

/*=====================================================================================================================================================================================================*/

int static LockSection(TSHashMap* _map, size_t _index)
{
	size_t section = GetSection(_map, _index);
	pthread_mutex_lock(&_map->m_mutexes[section]);
	return 0;
}

/*=====================================================================================================================================================================================================*/

int TSHashMap_LockItem(TSHashMap* _map, const void* _key)
{
	size_t index = GetIndex(_map, _key);
	size_t section = GetSection(_map, index);
	pthread_mutex_lock(&_map->m_mutexes[section]);
	return 0;
}

/*=====================================================================================================================================================================================================*/

int TSHashMap_UnlockItem(TSHashMap* _map, const void* _key)
{
	size_t index = GetIndex(_map, _key);
	size_t section = GetSection(_map, index);
	pthread_mutex_unlock(&_map->m_mutexes[section]);
	return 0;
}

/*=====================================================================================================================================================================================================*/

int static UnlockSection(TSHashMap* _map, size_t _index)
{
	size_t section = GetSection(_map, _index);
	pthread_mutex_unlock(&_map->m_mutexes[section]);
	return 0;
}


/*=====================================================================================================================================================================================================*/

Map_Result TSHashMap_Insert(TSHashMap* _map, const void* _key, const void* _value)
{
	size_t index; 
	int isFound;
	List** bucket;
	ListItr lastPlace;
	Item* newItem;
	
	CHECK_MAP
	CHECK_KEY(_key)
		
	index = GetIndex(_map, _key);
/*	LockSection(_map, index);*/
/*	printf("key %u index %u \n", *(int*)_key, index);*/
	bucket = &_map->m_map[index]; 

	if(*bucket) /* check if list exists */
	{
		isFound = IsItemFound(_map, _key, &lastPlace);
		if(TRUE == isFound)
		{
			UnlockSection(_map, index);
			return MAP_KEY_DUPLICATE_ERROR;
		}
	}
	else
	{
		*bucket = List_Create();
		lastPlace =  ListItr_Begin(*bucket);
	}
	
	newItem = Item_Create(_key, _value);
	ListItr_InsertBefore(lastPlace, newItem);
/*	UnlockSection(_map, index);*/
	return MAP_SUCCESS;
}

/*=====================================================================================================================================================================================================*/

static size_t GetIndex(TSHashMap* _map, const void* _key)
{
	return _map->m_hashFunc(_key)%_map->m_nBuckets;
}

/*=====================================================================================================================================================================================================*/
static int IsItemFound(TSHashMap* _map, const void* _key, ListItr* _lastPlace)
{
	size_t index;
	List* bucket;  
	ListItr begin, end, result;
	IsEqualContext cont;
	
	index = GetIndex(_map, _key);
	bucket = _map->m_map[index];

	if(!bucket)
	{
		return FALSE;
	}
	
	begin = ListItr_Begin(bucket);
	end = ListItr_End(bucket);

	cont.m_key = (void*)_key;
	cont.m_equal = _map->m_equal;
	result = ListItr_FindFirst(begin, end, IsKeyEqual, &cont);

	*_lastPlace = result;	
	if(ListItr_Equals(result, end))
	{ 
		return FALSE;	
	}else{
		return TRUE;
	}
}
/*=====================================================================================================================================================================================================*/
void* TSHashMap_Update(TSHashMap* _map, const void* _key, UpdateFunction _action, void* _context)
{
	int isFound;
	ListItr itr;
	Item* item;
	void* value;
	void* ret;

	TSHashMap_LockItem(_map, _key);
	isFound = IsItemFound((TSHashMap*)_map, _key, &itr);
	if(TRUE == isFound)
	{
		item = ListItr_Get(itr);
		value = item->m_value;
		ret = _action(value, _context);
	}else{
		ret = NULL;
	}
	TSHashMap_UnlockItem(_map, _key);
	return ret;
}
/*=====================================================================================================================================================================================================*/

size_t TSHashMap_Size(const TSHashMap* _map)
{
	size_t i, nBuckets;
	size_t counter = 0;
	
	if(!_map)
	{
		return 0;
	}
	nBuckets = _map->m_nBuckets;

	for(i = 0; i < nBuckets; ++i)
	{
		counter += List_Size(_map->m_map[i]);
	}
	return counter;
}
/*=====================================================================================================================================================================================================*/

static int IsKeyEqual(void *_element, void* _context)
{
	IsEqualContext* cont = _context;
	void* currentKey = ((Item*)_element) -> m_key;
	return cont->m_equal(currentKey, cont->m_key);
}

/*=====================================================================================================================================================================================================*/
static Item* Item_Create(const void* _key, const void* _value)
{	
	Item* newItem = (Item*)malloc(sizeof(Item));
	newItem->m_key = (void*)_key;
	newItem->m_value = (void*)_value;

	return newItem;
} 

/*=====================================================================================================================================================================================================*/
Map_Result TSHashMap_Remove(TSHashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	ListItr itr;
	int isFound;
	Item* removed;
	
	CHECK_KEY(_searchKey)
	CHECK_MAP
	if(!_pKey || !_pValue)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	isFound = IsItemFound(_map, _searchKey, &itr);
	if(FALSE == isFound)	
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	removed = ListItr_Remove(itr);
	*_pKey = removed->m_key;
	*_pValue = removed->m_value;
	free(removed);
	return MAP_SUCCESS;
}
/*=====================================================================================================================================================================================================*/
static int ItemDestroy(void* _element, void* _context)
{
	Item* removed = _element;
	DestroyContext* cont = _context;
	if(cont->m_keyDestroy)
	{
		cont->m_keyDestroy(removed->m_key);
	}
	
	if(cont->m_valueDestroy)
	{
		cont->m_valueDestroy(removed->m_value);
	}
	
	free(removed);
	
	#ifndef NDEBUG
		printf("item freed \n");
	#endif
	return TRUE;
}

/*=====================================================================================================================================================================================================*/
	
size_t TSHashMap_ForEach(const TSHashMap* _map, KeyValueActionFunction _action, void* _context)
{
	size_t lists, i;
	ListItr itr, end;
	List** map;
	Item temp;
	size_t counter = 0;
	int status;
	
	if(!_map || 0xbeefbeef != _map->m_magicNumber)
	{
		return 0;
	}
	
	lists = _map->m_nBuckets; 
	map = _map->m_map;
	
	for(i = 0; i < lists; ++i)
	{
		LockSection((TSHashMap*)_map, i);
		itr = ListItr_Begin(map[i]);
		end = ListItr_End(map[i]);
		#ifndef NDEBUG
				printf("we are in list number %lu \n", i);
		#endif
		while(itr != end)
		{
			temp = *(Item*)(ListItr_Get(itr));
			status = _action(temp.m_key, temp.m_value, _context);
			counter++;
			if(0 == status)
			{
				return counter;
			}
			itr = ListItr_Next(itr);
		}
		UnlockSection((TSHashMap*)_map, i);
	}
	return counter;
}

/*=====================================================================================================================================================================================================*/

Map_Result TSHashMap_Rehash(TSHashMap* _map, size_t _newCapacity)
{
	size_t i, lists, itemIndex, size;
	Item** items;
	Item temp;
	List** newListArray;
	ListItr begin, end, next;
	itemIndex = 0;

				
	CHECK_MAP	
	if(!_map || !_newCapacity)
	{
		return MAP_UNINITIALIZED_ERROR;
	}

	newListArray = realloc(_map->m_map, _newCapacity * sizeof(List*));
	if(!newListArray)
	{
		return MAP_ALLOCATION_ERROR;
	}
		
	size = TSHashMap_Size(_map);
	lists = _map->m_nBuckets;
	items = (Item**)malloc(size * sizeof(Item*));
	for(i = 0; i < lists; ++i)
	{
		begin = ListItr_Begin(_map->m_map[i]);
		end = ListItr_End(_map->m_map[i]);
		while(!ListItr_Equals(begin, end) )
		{
			next = ListItr_Next(begin);
			items[itemIndex++] = ListItr_Remove(begin);
			begin = next;
		}
	}
	
	_map->m_map = newListArray;
	_map->m_nBuckets = _newCapacity;
	for(i = 0; i < size; ++i)
	{
		temp = *items[i];
		TSHashMap_Insert(_map, temp.m_key, temp.m_value);
		free(items[i]);
	}

	free(items);
	return MAP_SUCCESS;	
}

/*=====================================================================================================================================================================================================*/
Map_Result TSHashMap_Find(const TSHashMap* _map, const void* _searchKey, void** _ppValue)
{
	int isFound;
	ListItr itr;
	Item* item;
	
	CHECK_KEY(_searchKey)
	CHECK_MAP
	if(!_ppValue)
	{
		return MAP_UNINITIALIZED_ERROR;
	}	
	
	isFound = IsItemFound((TSHashMap*)_map, _searchKey, &itr);
	if(TRUE == isFound)
	{
		item = ListItr_Get(itr);
		*_ppValue = item->m_value;
		return MAP_SUCCESS;
	}
	else
	{
		return MAP_KEY_NOT_FOUND_ERROR;	
	} 
}
