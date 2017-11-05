#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mu_test.h"
#include "cdrMessager.h"
#include "cdrParser.h"
#include "cdrParserManager.h"
#include "safeThreadQueue.h"
#include "discoverer.h"

UNIT(CdrMessage_creatyANDdestroy)
    CdrMessage_t* msg;

    msg = CdrMessage_Creaty();
	ASSERT_THAT(NULL != msg);
	ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_Desroy(msg));
    ASSERT_THAT(CDR_MESSAGER_UNINITIALIZED_ERROR == CdrMessage_Desroy(msg));

END_UNIT
/**************************************************/
UNIT(CdrMessage_SetANDGet)
    CdrMessage_t* msg;
    char imsi[] = "1234567891011";
    size_t imsiInt = 0;
    char opartor[] = "cellcom baaam";
    char* oparatorReturn;
    char mmc[] = "45002";
    size_t mmcMnc = 0;
    char callType[] = "MOC";
    char* callTypeRetVal;
    char download[]  = "1024";
    float downloadRetVal=0;
    char upload[] = "555";
    float uploadRetVal = 0;

    msg = CdrMessage_Creaty();
	ASSERT_THAT(NULL != msg);
    /*check set get imsi*/
	ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_SetImsi(msg,imsi));
	ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_GetImsi(msg,&imsiInt));
	ASSERT_THAT( 1234567891011== imsiInt);

    /*check set get oparetor name*/
    ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_SetCallType(msg,callType));
	callTypeRetVal = calloc(5,sizeof(char));
	ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_GetCallType(msg,callTypeRetVal));
	ASSERT_THAT( 0== strcmp(callType,callTypeRetVal));
    free(callTypeRetVal);

    /*check set get MccMnc */
    ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_SetMccMnc(msg,mmc));
    ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_GetMccMnc(msg,&mmcMnc));
	ASSERT_THAT( 45002== mmcMnc);
	/*check set get CallType*/
    ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_SetOperatorName(msg,opartor));
	oparatorReturn = calloc(64,sizeof(char));
	ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_GetOperatorName(msg,oparatorReturn));
	ASSERT_THAT( 0== strcmp(opartor,oparatorReturn));
    free(oparatorReturn);

    /*check set get download*/
	ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_SetDownload(msg,download));
	ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_GetDownload(msg,&downloadRetVal));
	ASSERT_THAT( 1024== downloadRetVal);


    /*check set get upload*/
	ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_SetUpload(msg,upload));
	ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_GetUpload(msg,&uploadRetVal));
	ASSERT_THAT( 555== uploadRetVal);

	ASSERT_THAT(CDR_MESSAGER_SUCCESS == CdrMessage_Desroy(msg));

END_UNIT
/**************************************************/

UNIT(CdrParser_creatyANDdestroy)
    CdrParser_t* newParser;
    size_t threadNumber = 2;
    char  inprogressfilePath[] = "../../inprogress/";
    char  inputfilePath[] = "../../output/";
    char* str= calloc(10,sizeof(char));

    newParser = CdrParser_Creaty(str,inprogressfilePath,inputfilePath,threadNumber);
    ASSERT_THAT( NULL!= newParser);
    ASSERT_THAT( CDR_PARSER_SUCCESS ==CdrParser_Destroy( newParser));
free(str);
END_UNIT

/**************************************************/
UNIT(CdrParser_runTest)
    CdrParser_t* newParser;
    size_t threadNumber = 2;
    char  inprogressfilePath[] = "../../inprogress/";
    char  inputfilePath[] = "../../output/";
    char* str= calloc(10,sizeof(char));

    newParser = CdrParser_Creaty(str,inprogressfilePath,inputfilePath,threadNumber);
    ASSERT_THAT( NULL!= newParser);
  ASSERT_THAT(CDR_PARSER_SUCCESS == CdrParser_Run(newParser));
    ASSERT_THAT( CDR_PARSER_SUCCESS ==CdrParser_Destroy( newParser));
    free(str);
END_UNIT

/**************************************************/
UNIT(Discoverer_CreatyTest)
    Discoverer_t* newDiscoverer;
    char  inputfilePath[] = "../../input/";
    char  inprogressfilePath[] = "../../inprogress/";
    size_t intervalNumber = 2;
    char* str;
    str = calloc(10,sizeof(char));
    newDiscoverer = Discoverer_Creaty(str,inputfilePath,inprogressfilePath,intervalNumber);
    ASSERT_THAT( NULL!= newDiscoverer);
    ASSERT_THAT( DISCOVERER_SUCCESS ==Discoverer_Destroy(newDiscoverer));
    free(str);
END_UNIT

/**************************************************/
UNIT(Discoverer_RunTest)
    Discoverer_t* newDiscoverer;
    char  inputfilePath[] = "../../input/";
    char  inprogressfilePath[] = "../../inprogress/";
    size_t intervalNumber = 2;
    char* str;
    str = calloc(10,sizeof(char));
    newDiscoverer = Discoverer_Creaty(str,inputfilePath,inprogressfilePath,intervalNumber);
    ASSERT_THAT( NULL!= newDiscoverer);
    ASSERT_THAT(DISCOVERER_SUCCESS == Discoverer_Run(newDiscoverer));
    sleep(1);
    ASSERT_THAT( DISCOVERER_SUCCESS ==Discoverer_Destroy(newDiscoverer));
    free(str);

END_UNIT

/**************************************************/
UNIT(CdrParserManager_CreatyTest)
    char  inputfilePath[] = "../../input/";
    char  inprogressfilePath[] = "../../inprogress/";
    char  donefilePath[] = "../../done/";
    CdrParserManager_t* messager;
    STQueueu_t* sQueue;
    sQueue= SafeThreadQueue_Create(40);
    messager = CdrParserManager_Creaty(sQueue,inputfilePath,inprogressfilePath,donefilePath,2);
    ASSERT_THAT( NULL!= messager);
    ASSERT_THAT( CDR_MANAGER_SUCCESS ==CdrParserManager_Destroy(messager));
    SafeTreadQueue_Destroy(sQueue,NULL);
END_UNIT

/**************************************************/
UNIT(CdrParserManager_ALLRunTestsWhitThreads)
    char  inputfilePath[] = "../../input/";
    char  inprogressfilePath[] = "../../inprogress/";
    char  donefilePath[] = "../../done/";

    CdrParserManager_t* messager;
    STQueueu_t* sQueue;

    size_t numberOfthread =2;
    sQueue= SafeThreadQueue_Create(20);
    ASSERT_THAT( NULL!= sQueue);

    messager = CdrParserManager_Creaty(sQueue,inputfilePath,inprogressfilePath,donefilePath,numberOfthread);
    ASSERT_THAT( NULL!= messager);
    ASSERT_THAT( CDR_MANAGER_SUCCESS ==CdrParserManager_Run(messager));
	sleep(40);
    SafeTreadQueue_Destroy(sQueue,NULL);
    ASSERT_THAT( CDR_MANAGER_SUCCESS ==CdrParserManager_Destroy(messager));
END_UNIT

/**************************************************/
TEST_SUITE(Cdr Manager)
/*	TEST(CdrMessage_creatyANDdestroy)
    TEST(CdrMessage_SetANDGet)
    TEST(CdrParser_creatyANDdestroy)
    TEST(CdrParser_runTest)
    TEST(Discoverer_CreatyTest)
    TEST(Discoverer_RunTest)
    TEST(CdrParserManager_CreatyTest)*/
    TEST(CdrParserManager_ALLRunTestsWhitThreads)

END_SUITE
