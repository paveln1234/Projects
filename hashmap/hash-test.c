#include <string.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/mu_test.h"
#include "../inc/hashmap.h"
#define SIZE 500

typedef void (*elementDestroy_t)(void*);


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



UNIT(creation)
	HashMap* hm;

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
	HashMap* hm;
	hm = HashMap_Create(SIZE, (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);

END_UNIT

UNIT(insert)
	HashMap* hm;
	char* res;
	Map_Result result;
	hm = HashMap_Create(SIZE, (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, "pavel", "gever");
	HashMap_Insert(hm, "rita", "soup");
	HashMap_Insert(hm, "monkey", "bisnes");
	HashMap_Insert(hm, "nadav", "gever");
	HashMap_Insert(hm, "gilat", "biuteful");
	HashMap_Insert(hm, "cat", "shusha");
	result = HashMap_Find(hm, "pavel", (void**)&res);
	ASSERT_THAT(result == MAP_SUCCESS);
	ASSERT_THAT(strcmp(res, "gever") == 0);
	result = HashMap_Find(hm, "rita", (void**)&res);
	ASSERT_THAT(result == MAP_SUCCESS);
	ASSERT_THAT(strcmp(res, "soup") == 0);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);

END_UNIT

UNIT(insert_duplicate)
	HashMap* hm;
	hm = HashMap_Create(SIZE, (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, "pavel", "gever");
	ASSERT_THAT(HashMap_Insert(hm, "pavel", "gever") == MAP_KEY_DUPLICATE_ERROR);
	HashMap_Insert(hm, "rita", "soup");
	ASSERT_THAT(HashMap_Insert(hm, "rita", "soup") == MAP_KEY_DUPLICATE_ERROR);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
END_UNIT


UNIT(find_non_existent)
	HashMap* hm;
	char* res;
	hm = HashMap_Create(SIZE, (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, "pavel", "gever");
	ASSERT_THAT(HashMap_Find(hm, "moshe", (void**)&res) == MAP_KEY_NOT_FOUND_ERROR);
	ASSERT_THAT(HashMap_Find(hm, "Pavel", (void**)&res) == MAP_KEY_NOT_FOUND_ERROR);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
END_UNIT

UNIT(remove_item)
	HashMap* hm;
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
	HashMap* hm;
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
	HashMap* hm;
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
	HashMap* hm;
	char* reskey;
	char*resval;
	char k[] = "pavel";
	char v[] = "value";
	hm = HashMap_Create(SIZE,  (HashFunction) hashfunc, (EqualityFunction) IsEqual);
	HashMap_Insert(hm, k, v);
	HashMap_ForEach(hm, (KeyValueActionFunction) reversValeu, NULL);
	ASSERT_THAT(HashMap_Remove(hm, "pavel", (void**)&reskey,(void**)&resval) == MAP_SUCCESS);
	ASSERT_THAT(strcmp(resval, "eulav") == 0);
	HashMap_Destroy(&hm, NULL, NULL);
	ASSERT_THAT(NULL == hm);
END_UNIT


UNIT(massivcheck)
	HashMap* hm;
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

UNIT(massivRehashCheck)
	HashMap* hm;
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
/*
#ifndef NDEBUG
UNIT(statisticCheck)
	HashMap* hm;
	Map_Stats* statMap;
	size_t i;
	int* key;
	int* value;
	int failer = 0;
	int success = 0;

	hm = HashMap_Create(SIZE,  (HashFunction) hashfunc, (EqualityFunction) NumEqFunc);

	for(i = 0 ; i < 10000 ; ++i)
	{
		key = malloc(sizeof(int));
		value = malloc(sizeof(int));
		*key = rand() % 25000+1;
		*value = rand() % 25000+1;
		if (HashMap_Insert(hm, key, value) != MAP_SUCCESS)
		{
			free(key);
			free(value);
			++failer;
		}
		++success;
	}
	HashMap_Rehash(hm, SIZE*100);

	statMap = HashMap_GetStatistics(hm);
	ASSERT_THAT(statMap->numberOfNonEmptyBuckets == success);
	ASSERT_THAT(statMAp->numberOfBuckets == SIZE);

	HashMap_Destroy(&hm, DestroyItem, DestroyItem);
	ASSERT_THAT(NULL == hm);

END_UNIT
#endif
*/
TEST_SUITE(Generic HashMap Tests)
	TEST(creation)
	TEST(destruction)
	TEST(insert)
	TEST(insert_duplicate)
	TEST(find_non_existent)
	TEST(remove_item)
	TEST(remove_item_twice)
	TEST(rehash)
	TEST(for_each)
	/*TEST(massivcheck)
	TEST(massivRehashCheck)*/
/*
#ifndef NDEBUG
	TEST(statisticCheck)

#endif
*/
END_SUITE
