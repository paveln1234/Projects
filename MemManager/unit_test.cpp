#include "mu_test.h"
#include "MemPage_t.h"
#include "MemPool_t.h"
#include "MemManager_t.h"
#include <iostream>
#include <cstring>

using namespace std;

UNIT(page_simple)
	MemPage_t page;
	ASSERT_THAT(!page.IsFull());
	ASSERT_THAT(page.IsEmpty());
	ASSERT_THAT(page.GetActualSize() == 0);
	ASSERT_THAT(page.GetCapacity() == 6);
	ASSERT_THAT(page.GetPos() == 0);
END_UNIT

UNIT(insert_int)
	MemPage_t page;
	int num = 7;
	ASSERT_THAT(page.MemWrite(&num, sizeof(int)) == sizeof(int));
	ASSERT_THAT(page.GetPos() == 4);
	ASSERT_THAT(page.GetActualSize() == sizeof(int));
	ASSERT_THAT(!page.IsFull());
	ASSERT_THAT(!page.IsEmpty());	
END_UNIT

UNIT(insert_two_ints)
	MemPage_t page;
	int num1 = 7, num2 = 8;
	ASSERT_THAT(page.MemWrite(&num1, sizeof(int)) == sizeof(int));
	ASSERT_THAT(page.MemWrite(&num2, sizeof(int)) == 2);
	ASSERT_THAT(page.GetActualSize() == page.GetCapacity());
	ASSERT_THAT(page.GetPos() == 6);
	ASSERT_THAT(page.IsFull());
	ASSERT_THAT(!page.IsEmpty());	
END_UNIT

UNIT(write_and_read_int)
	MemPage_t page;
	int num = 7, res;
	ASSERT_THAT(page.MemWrite(&num, sizeof(int)) == sizeof(int));
	page.MemRead(&res, sizeof(int));
	ASSERT_THAT(res != 7);
	page.SetPos(0);
	page.MemRead(&res, sizeof(int));
	ASSERT_THAT(res == 7);
END_UNIT

UNIT(write_and_read_int_on_set_pos)
	MemPage_t page;
	int num = 7, res = 1;
	ASSERT_THAT(page.MemWrite(&num, sizeof(int)) == sizeof(int));
	ASSERT_THAT(page.MemWrite(&num, sizeof(int)) == 2);
	ASSERT_THAT(page.MemWrite(&num, sizeof(int), 2) == sizeof(int));
	ASSERT_THAT(page.MemRead(&res, sizeof(int), 2) == sizeof(int));
	ASSERT_THAT(res == 7);
	num = 8;
	ASSERT_THAT(page.MemWrite(&num, sizeof(int), 0) == sizeof(int));
	page.SetPos(0);
	page.MemRead(&res, sizeof(int), 0);
	ASSERT_THAT(res == 8);
END_UNIT

UNIT(pool_simple)
	MemPool_t mp;
	ASSERT_THAT(mp.GetActualSize() == 0);
	ASSERT_THAT(mp.GetPos() == 0);
END_UNIT

UNIT(pool_write_and_read)
	MemPool_t mp;
	int num = 7, res = 0;
	mp.MemWrite(&num, sizeof(int));
	num = 8;
	mp.MemWrite(&num, sizeof(int));
	num = 9;	
	mp.MemWrite(&num, sizeof(int));	
	ASSERT_THAT(mp.GetPos() == 12);
	ASSERT_THAT(mp.MemRead(&res, sizeof(int)) == 0);
	mp.MemRead(&res, sizeof(int), 0);	
	ASSERT_THAT(res == 7);
	mp.MemRead(&res, sizeof(int), 4);	
	ASSERT_THAT(res == 8);
	mp.MemRead(&res, sizeof(int), 8);	
	ASSERT_THAT(res == 9);
	num = 100;
	mp.MemWrite(&num, sizeof(int), 1);	
	mp.MemWrite(&num, sizeof(int), 8);
	mp.MemRead(&res, sizeof(int), 1);	
	ASSERT_THAT(res == 100);
	mp.MemRead(&res, sizeof(int), 8);	
	ASSERT_THAT(res == 100);
END_UNIT

UNIT(pool_strings)
	MemPool_t mmp;	
	MemManager_t& mp = mmp;
	char s[] = "some text here blah blah blah whatever";
	char r[] = "random string";
	char* res = new char[sizeof(s)];
	mp.MemWrite(s, sizeof(s));
	mp.MemRead(res, sizeof(s), 0);
	ASSERT_THAT(strcmp(s, res) == 0);
	mp.MemWrite(r, sizeof(r), 5);
	mp.MemRead(res, sizeof(r), 5);
	ASSERT_THAT(strcmp(r, res) == 0);
	delete[] res;
	ASSERT_THAT(1 == 1);
END_UNIT

UNIT(pool_strings2)
	MemPool_t mmp;	
	MemManager_t& mp = mmp;
	char s[] = "some text here blah blah blah whatever";
	char r[] = "random string";
	char* res = new char[sizeof(s)];
	mp.MemWrite(s, sizeof(s));
	mp.SetPos(0);
	mp.MemRead(res, sizeof(s));
	ASSERT_THAT(strcmp(s, res) == 0);
	mp.SetPos(5);
	mp.MemWrite(r, sizeof(r));
	mp.SetPos(5);
	mp.MemRead(res, sizeof(r));
	ASSERT_THAT(strcmp(r, res) == 0);
	delete[] res;
	ASSERT_THAT(1 == 1);
END_UNIT

TEST_SUITE(Memory manager tests)
	TEST(page_simple)
	TEST(insert_int)
	TEST(insert_two_ints)
	TEST(write_and_read_int)
	TEST(write_and_read_int_on_set_pos)
	TEST(pool_simple)
	TEST(pool_write_and_read)
	TEST(pool_strings)
	TEST(pool_strings2)
END_SUITE




























