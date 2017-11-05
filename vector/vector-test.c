#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "../inc/mu_test.h"
#include "../inc/vector.h"


typedef struct Player
{
	size_t m_coordX;
	size_t m_coordY;
	size_t m_hp;
	int m_isFrozen;
} Player_t;

typedef void(*DestroyFunc_t)(void*);

/*Destroy function*/
void DestroyPlayer(Player_t* _player)
{
	free(_player);
}

/*Print playe's info*/
int PrintInfo(Player_t* _p, size_t _index, int* _factor)
{
	printf("\nPlayer %lu:\nCoordinates: (%lu, %lu)\nHealth Points: %lu\nm_isFrozen: %d", _index, _p->m_coordX, _p->m_coordY, _p->m_hp, _p->m_isFrozen);
	return 1;
}

/*Print function. Multiplies every player's m_hp by factor provided in parameter*/
int Multiplym_hp(Player_t* _p, size_t _index, int* _factor)
{
	_p->m_hp *= *_factor;
	return 1;
}


/*======================================= TESTS ==============================================*/

UNIT(create_empty)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	vec = Vector_Create(100, 100);
	ASSERT_THAT(vec != NULL);
	Vector_Destroy(&vec, destroyFunc);
END_UNIT

UNIT(create_zero_size)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	vec = Vector_Create(0, 100);
	ASSERT_THAT(vec != NULL);
	Vector_Destroy(&vec, destroyFunc);
END_UNIT

UNIT(create_non_resizable)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	vec = Vector_Create(100, 0);
	ASSERT_THAT(vec != NULL);
	Vector_Destroy(&vec, destroyFunc);
END_UNIT

UNIT(create_illigal)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	vec = Vector_Create(0, 0);
	ASSERT_THAT(vec == NULL);
	Vector_Destroy(&vec, destroyFunc);
END_UNIT

UNIT(create_and_destroy)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	vec = Vector_Create(100, 100);
	Vector_Destroy(&vec, destroyFunc);
	ASSERT_THAT(vec == NULL);
END_UNIT

UNIT(double_destruction)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	vec = Vector_Create(100, 100);
	Vector_Destroy(&vec, destroyFunc);
	Vector_Destroy(&vec, destroyFunc);
	ASSERT_THAT(vec == NULL);
END_UNIT

UNIT(append_one)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	Player_t* p = (Player_t*) malloc(sizeof(Player_t));
	vec = Vector_Create(100, 100);
	Vector_Append(vec, p);
	ASSERT_THAT(Vector_Size(vec) == 1);
	Vector_Destroy(&vec, destroyFunc);
END_UNIT

UNIT(append_few)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	int i;
	Player_t* p;
	vec = Vector_Create(100, 100);
	for(i = 0; i < 15; ++i)
	{
		p = (Player_t*) malloc(sizeof(Player_t));
		Vector_Append(vec, p);
	}
	ASSERT_THAT(Vector_Size(vec) == 15);
	Vector_Destroy(&vec, destroyFunc);
END_UNIT

UNIT(append_many)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	int i;
	Player_t* p;
	vec = Vector_Create(100, 100);
	for(i = 0; i < 300; ++i)
	{
		p = (Player_t*) malloc(sizeof(Player_t));
		Vector_Append(vec, p);

	}
	ASSERT_THAT(Vector_Size(vec) == 300);
	Vector_Destroy(&vec, destroyFunc);

END_UNIT

UNIT(append_many_to_unresizable)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	int i;
	Player_t* p;
	vec = Vector_Create(100, 0);
	for(i = 0; i < 300; ++i)
	{
		p = (Player_t*) malloc(sizeof(Player_t));
		if(Vector_Append(vec, p) != VECTOR_SUCCESS)
		{
			free(p);
			break;
		}
	}
	ASSERT_THAT(Vector_Size(vec) == 100);
	Vector_Destroy(&vec, destroyFunc);
END_UNIT

UNIT(append_and_remove)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	int i;
	Player_t* p;
	vec = Vector_Create(50, 50);
	for(i = 0; i < 100; ++i)
	{
		p = (Player_t*) malloc(sizeof(Player_t));
		Vector_Append(vec, p);
	}

	for(i = 0; i < 30; ++i)
	{
		Vector_Remove(vec, (void**)&p);
		free(p);
	}
	ASSERT_THAT(Vector_Size(vec) == 70);
	Vector_Destroy(&vec, destroyFunc);
END_UNIT

UNIT(append_and_remove_to_desize)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	int i;
	Player_t* p;

	vec = Vector_Create(100, 50);
	for(i = 0; i < 260; ++i)
	{
		p = (Player_t*) malloc(sizeof(Player_t));
		Vector_Append(vec, p);
	}

	ASSERT_THAT(Vector_Capacity(vec) == 300);

	for(i = 0; i < 240; ++i)
	{
		Vector_Remove(vec, (void**)&p);
		free(p);
	}

	ASSERT_THAT(Vector_Capacity(vec) == 100);
	Vector_Destroy(&vec, destroyFunc);
END_UNIT

UNIT(set_and_get)
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	int i;
	Player_t* p;
	Player_t* pCheck;

	vec = Vector_Create(100, 100);
	for(i = 0; i < 300; ++i)
	{
		p = (Player_t*) malloc(sizeof(Player_t));
		Vector_Append(vec, p);
	}
	p = (Player_t*) malloc(sizeof(Player_t));
	p->m_coordX = 100;
	Vector_Set(vec, 5, (void**)&p);
	Vector_Get(vec, 5, (void**)&pCheck);
	ASSERT_THAT(pCheck->m_coordX == 100);

	Vector_Destroy(&vec, destroyFunc);
END_UNIT

UNIT(create_and_print)
	/*VectorElementAction printAction = (VectorElementAction) PrintInfo;*/
	VectorElementAction multiplyAction = (VectorElementAction) Multiplym_hp;
	DestroyFunc_t destroyFunc = (DestroyFunc_t) DestroyPlayer;
	Vector_t* vec = NULL;
	int i;
	int factor = 2;
	Player_t* p;

	vec = Vector_Create(100, 100);
	for(i = 0; i < 5; ++i)
	{
		p = (Player_t*) malloc(sizeof(Player_t));
		p->m_coordX = rand() % 100;
		p->m_coordY = rand() % 100;
		p->m_hp = rand() % 100;
		p->m_isFrozen = rand() % 2;
		Vector_Append(vec, p);

	}


	ASSERT_THAT(Vector_ForEeach(vec, multiplyAction, &factor) == i);
	Vector_Destroy(&vec, destroyFunc);

END_UNIT


TEST_SUITE(Generic Vector Tests)
	TEST(create_empty)
	TEST(create_zero_size)
	TEST(create_non_resizable)
	TEST(create_illigal)
	TEST(create_and_destroy)
	TEST(double_destruction)
	TEST(append_one)
	TEST(append_few)
	TEST(append_many)
	TEST(append_many_to_unresizable)
	TEST(append_and_remove)
	TEST(append_and_remove_to_desize)
	TEST(set_and_get)
	TEST(create_and_print)
END_SUITE

/*===============================TEST IMPLEMENTATION============================================*/

























































