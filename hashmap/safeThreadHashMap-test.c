#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "mu_test.h"
#include "safeThreadHashMap.h"
#define SIZE 100

typedef void (*elementDestroy_t)(void*);

int success ;
int failed;
/*-------------------------------------------------------------------------------------------*/

int NumEqFunc(int* _num1, int* _num2)
{
	return (*_num1 == *_num2);
}

size_t hashfunc(char* _str)
{
    size_t hash = 5381;
    size_t i = 0;
    size_t len = strlen(_str);
    for(i = 0; i < len; _str++, i++)
    {
        hash = ((hash << 5) + hash) + (*_str);
    }

    return hash;
}

int IsEqual(char* _firstKey,char* _secondKey)
{
	return (strcmp(_firstKey,_secondKey) == 0 ? 1 : 0);
}

void DestroyItem(void* _item)
{
	free(_item);

return;
}


int reversValeu(char* _key, char* _str, void* _context)
{
	char* p1;
	char* p2;
	char temp;
	for (p1 = _str, p2 = _str + strlen(_str) - 1; p2 > p1; ++p1, --p2)
    {
		temp = *p1;
		*p1 = *p2;
		*p2 = temp;
	}
    return 1;
}


void* threadFunc(void* _context)
{
	int i;
    int* key;
	int* value;

	STHashMap_t* hm =(STHashMap_t*)_context;

	for(i = 0; i < 100; ++i)
	{
		key = malloc(sizeof(int));
		value = malloc(sizeof(int));
        *key = rand() % 50;
        *value = rand() % 50;
        if (HashMap_Insert(hm, key, value) != MAP_SUCCESS)
		{
			free(key);
			free(value);
			++failed;
		}
		++success;
	}

return NULL;
}

void*  ExtractionThread(void* _context)
{
	int i;
	STHashMap_t* hm =(STHashMap_t*)_context;
    int* key;
	int* value;
    int* num = malloc(sizeof(int));;

	for(i = 0; i < 100; ++i)
	{
    	key = malloc(sizeof(int));
		value = malloc(sizeof(int));
        *num = rand() % 50;
        if(MAP_SUCCESS !=HashMap_Remove(hm,(void*) num, (void**)&key,(void**)&value))
		{
			free(key);
			free(value);
			--failed;
		}
	/*	--success;*/
	}
return NULL;
}


UNIT(creation)
	STHashMap_t* hm;

	hm = HashMap_Create(SIZE, (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	ASSERT_THAT(NULL != hm);
	HashMap_Destroy(&hm, NULL, NULL);

	hm = HashMap_Create(SIZE, NULL, (EqualityFunction) IsEqual);
	ASSERT_THAT(NULL == hm);
	HashMap_Destroy(&hm, NULL, NULL);

	hm = HashMap_Create(SIZE, (HashFunction) hashfunc, NULL);
	ASSERT_THAT(NULL == hm);
	HashMap_Destroy(&hm, NULL, NULL);

END_UNIT

UNIT(destruction)
	STHashMap_t* hm;
	hm = HashMap_Create(SIZE, (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);

END_UNIT

UNIT(insert)
	STHashMap_t* hm;
	char* res;
	Map_Result result;
	hm = HashMap_Create(SIZE, (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, "pavel", "gever");
	HashMap_Insert(hm, "rita", "soup");
	HashMap_Insert(hm, "monkey", "bisnes");
	HashMap_Insert(hm, "nadav", "gever");
	HashMap_Insert(hm, "gilat", "biuteful");
	HashMap_Insert(hm, "cat", "shusha");
	result = HashMap_Find(hm, "pavel", NULL,(void**)&res,NULL);
	ASSERT_THAT(result == MAP_SUCCESS);
	ASSERT_THAT(strcmp(res, "gever") == 0);
	result = HashMap_Find(hm, "rita", NULL, (void**)&res,NULL);
	ASSERT_THAT(result == MAP_SUCCESS);
	ASSERT_THAT(strcmp(res, "soup") == 0);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);

END_UNIT

UNIT(insert_duplicate)
	STHashMap_t* hm;
	hm = HashMap_Create(SIZE, (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, "pavel", "gever");
	ASSERT_THAT(HashMap_Insert(hm, "pavel", "gever") == MAP_KEY_DUPLICATE_ERROR);
	HashMap_Insert(hm, "rita", "soup");
	ASSERT_THAT(HashMap_Insert(hm, "rita", "soup") == MAP_KEY_DUPLICATE_ERROR);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
END_UNIT


UNIT(find_non_existent)
	STHashMap_t* hm;
	char* res;
	hm = HashMap_Create(SIZE, (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, "pavel", "gever");
	ASSERT_THAT(HashMap_Find(hm, "moshe",NULL, (void**)&res,NULL) == MAP_KEY_NOT_FOUND_ERROR);
	ASSERT_THAT(HashMap_Find(hm, "Pavel", NULL,(void**)&res,NULL) == MAP_KEY_NOT_FOUND_ERROR);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
END_UNIT

UNIT(remove_item)
	STHashMap_t* hm;
	char* reskey;
	char*resval;
	hm = HashMap_Create(SIZE,  (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, "pavel", "gever");
	ASSERT_THAT(HashMap_Remove(hm, "pavel", (void**)&reskey,(void**)&resval) == MAP_SUCCESS);
	ASSERT_THAT(strcmp(resval, "gever") == 0);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
END_UNIT


UNIT(remove_item_twice)
	STHashMap_t* hm;
	char* reskey;
	char*resval;
	hm = HashMap_Create(SIZE,  (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, "pavel", "gever");
	ASSERT_THAT(HashMap_Remove(hm, "pavel", (void**)&reskey,(void**)&resval) == MAP_SUCCESS);
	ASSERT_THAT(strcmp(resval, "gever") == 0);
	ASSERT_THAT(HashMap_Remove(hm, "pavel", (void**)&reskey,(void**)&resval)  == MAP_KEY_NOT_FOUND_ERROR);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
END_UNIT

UNIT(rehash)
	STHashMap_t* hm;
	char* reskey;
	char*resval;
	hm = HashMap_Create(SIZE,  (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, "pavel", "gever");
	HashMap_Rehash(hm, SIZE*10);
	ASSERT_THAT(HashMap_Remove(hm, "pavel", (void**)&reskey,(void**)&resval) == MAP_SUCCESS);
	ASSERT_THAT(strcmp(resval, "gever") == 0);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
END_UNIT

UNIT(for_each)
	STHashMap_t* hm;
	char* reskey;
	char*resval;
	int sum = 1;
	char k[] = "pavel";
	char v[] = "value";
	hm = HashMap_Create(SIZE,  (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, k, v);
	HashMap_ForEach(hm, (KeyValueActionFunction) reversValeu, &sum);
	ASSERT_THAT(HashMap_Remove(hm, "pavel", (void**)&reskey,(void**)&resval) == MAP_SUCCESS);
	ASSERT_THAT(strcmp(resval, "eulav") == 0);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
END_UNIT


UNIT(massivcheck)
	STHashMap_t* hm;
	size_t i;
	int* key;
	int* value;
	int failer = 0;
	int success = 0;

	hm = HashMap_Create(SIZE,  (HashFunction) hashfunc, (EqualityFunction) NumEqFunc);

	for(i = 0 ; i < 100 ; ++i)
	{
		key = malloc(sizeof(int));
		value = malloc(sizeof(int));
		*key = rand() % 250+1;
		*value = rand() % 250+1;
		if (HashMap_Insert(hm, key, value) != MAP_SUCCESS)
		{
			free(key);
			free(value);
			++failer;
		}
		++success;
	}
	HashMap_Rehash(hm, SIZE*100);
	HashMap_Destroy(&hm, DestroyItem, DestroyItem);
	ASSERT_THAT(NULL == hm);

END_UNIT
/******************************************/
UNIT(massivRehashCheck)
	STHashMap_t* hm;
	size_t i;
	int* key;
	int* value;
	int failer = 0;
	int success = 0;

	hm = HashMap_Create(SIZE,  (HashFunction) hashfunc, (EqualityFunction) NumEqFunc);

	for(i = 0 ; i < 1000 ; ++i)
	{
		key = malloc(sizeof(int));
		value = malloc(sizeof(int));
		*key = rand() % 2500+1;
		*value = rand() % 2500+1;
		if (HashMap_Insert(hm, key, value) != MAP_SUCCESS)
		{
			free(key);
			free(value);
			++failer;
		}
		++success;
	}
	HashMap_Rehash(hm, SIZE*10);
	HashMap_Destroy(&hm, DestroyItem, DestroyItem);
	ASSERT_THAT(NULL == hm);

END_UNIT

UNIT(threadTest)
	STHashMap_t* hm;
	int i;
	void* junk;
	pthread_t threads[10];
	success = 0;
	failed = 0;
	hm = HashMap_Create(SIZE,  (HashFunction) hashfunc, (EqualityFunction) NumEqFunc);
    for(i = 0; i < 10; ++i)
	{
		if((i%2) == 0)
		{
			pthread_create(&threads[i], NULL,ExtractionThread, hm);
		}
		else
		{
			pthread_create(&threads[i], NULL,threadFunc, hm);
		}
	}
	for(i = 0; i < 10; ++i)
	{
		pthread_join(threads[i], &junk);
	}
	printf("sucees - %d | failed: %d\n",success,failed);
END_UNIT

/******************************************/
UNIT(update)
	STHashMap_t* hm;
	char* reskey;
	char*resval;
	char k[] = "pavel";
	char v[] = "value";
	hm = HashMap_Create(SIZE,  (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, k, v);
		ASSERT_THAT(HashMap_Find(hm, "pavel",(KeyValueActionFunction)reversValeu, (void**)&resval,NULL) == MAP_SUCCESS);
	ASSERT_THAT(HashMap_Remove(hm, "pavel", (void**)&reskey,(void**)&resval) == MAP_SUCCESS);
	ASSERT_THAT(strcmp("eulav",resval )== 0);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
END_UNIT


/******************************************/
TEST_SUITE(Generic HashMap Tests)
	/*TEST(creation)
	TEST(destruction)
	TEST(insert)
	TEST(insert_duplicate)
	TEST(find_non_existent)
	TEST(remove_item)
	TEST(remove_item_twice)
	TEST(rehash)*/
	TEST(for_each)
	/*TEST(massivcheck)
	TEST(massivRehashCheck)*/
/*    TEST(threadTest)
    TEST(update)*/
END_SUITE
