#include <stdio.h>
#include <stdlib.h>
#include "zlogManager.h"
#include "mu_test.h"

void checkPrintFunction(void* _ptr)
{
int port = 21, r = 334;
	ZLOG(_ptr, LOG_ERROR,"listen on port: %d failed: %d", port, r);

	ZLOG(_ptr, LOG_ERROR,"listen on port: %d failed: %d", port, r);
	ZLOG(_ptr, LOG_TRACE,"listen on port: %d failed: %d", port, r);
}

void checkPrintFunctionNet(void* _ptr)
{
	int port = 21, r = 334;
	ZLOG(_ptr, LOG_SEVERE,"listen on port: %d failed: %d", port, r);
	ZLOG(_ptr, LOG_ERROR,"listen on port: %d failed: %d", port, r);
	ZLOG(_ptr, LOG_SEVERE,"Is listen on port: %d failed: %d", port, r);
	ZLOG(_ptr, LOG_TRACE,"listen on port: %d failed: %d", port, r);
}


UNIT(checkLoger)
void* ptr;
void* ptr2;
ZlogInit("./log.log");
ptr = ZlogGet("query");
checkPrintFunction(ptr);
ptr2 = ZlogGet("net");
checkPrintFunctionNet(ptr2);

ZlogClose();

END_UNIT





TEST_SUITE(Generic Zlogger Tests)
	TEST(checkLoger)

END_SUITE
