#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "mu_test.h"
#include "subscribeDs.h"
#include "subscriber.h"
#include "operator.h"
#include"oparetorDs.h"
#include "datamanager.h"
#define MAX 2000000
#define MIN 1000000
#define MAKEIMSI(num)  num =(rand() % (MAX + 1 -MIN)) + MIN
#define SUBSRIBERS 2000000

void Subds_data(SubScribeDs_FiledToUpdate _filed,DataType_u* _type)
{
    switch(_filed)
    {
    case OUT_CALL_WITHIN_OPERATOR:
            _type->sec = 10;
            break;
	case IN_CALL_WITHIN_OPERATOR:
            _type->sec = 10;
            break;
	case OUT_CALL_OUTSIDE_OPERATOR:
            _type->sec = 10;
            break;
	case IN_CALL_OUTSIDE_OPERATOR:
            _type->sec = 10;
        break;
	case OUT_SMS_WITHIN_OPERATOR:
            _type->sec = 1;
        break;
	case IN_SMS_WITHIN_OPERATOR:
            _type->sec = 1;
        break;
	case OUT_SMS_OUTSIDE_OPERATOR:
            _type->sec = 1;
        break;
	case IN_SMS_OUTSIDE_OPERATOR:
            _type->sec = 1;
        break;
	case MB_DOWNLOADED:
            _type->data = 2.1;
        break;
	case MB_UPLOADED:
            _type->data = 1.3;
        break;
    }

return;
}
void printSub(char* _str)
{
    printf("%s",_str);
return;
}
UNIT(SubScribe_creatTest)
    SubScribeData_t* newSub;
    size_t mism = 43453;
    newSub = SubScribe_Creaty(mism);
	ASSERT_THAT(NULL != newSub);
    ASSERT_THAT(SUBSCRIBE_DATA_SUCCESS == SubScribe_Destroy(newSub));

END_UNIT

/******************************************/
UNIT(SubScribe_insertAndremove)
    SubScribeData_t* newSub;
    size_t mism = 43453;
    char buffer[512];
    size_t retintum= 0;
/*    float retfloatnum =0;*/
    newSub = SubScribe_Creaty(mism);
	ASSERT_THAT(NULL != newSub);
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_AddOutCallWightOperator(newSub,5));
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_GetOutCallWightOperator(newSub,&retintum));
    ASSERT_THAT( retintum ==  5);
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_AddInCallWightOperator(newSub,5));
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_AddOutCallOutsideOperator(newSub,5));
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_AddInCallOutsideOperator(newSub,5));
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_AddOutSmsWightOperator(newSub));
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_AddInSmsWightOperator(newSub));
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_AddOutSmsOutsideOperator(newSub));
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_AddInSmsOutsideOperator(newSub));
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_AddDownload(newSub,2.1));
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_AddUpload(newSub,3.1));
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_SubSribeToSrc(newSub,buffer));
    /*printf("subsribe = %s\n",buffer);*/
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_SubSribeReset(newSub));
    ASSERT_THAT( SUBSCRIBE_DATA_SUCCESS ==  SubScribe_SubSribeToSrc(newSub,buffer));
    /*printf("subsribe = %s\n",buffer);*/
    ASSERT_THAT(SUBSCRIBE_DATA_SUCCESS == SubScribe_Destroy(newSub));

END_UNIT
/******************************************/
UNIT(SubScribeDs_creatTest)
   	size_t _numberOfSubsribers = 300;

    SubScribeDs_t* subDs;
    subDs = subScribeDs_Creaty(  _numberOfSubsribers);
    ASSERT_THAT(NULL != subDs);
    ASSERT_THAT(SUBSCRIBE_DS_SUCCESS == subScribeDs_Destroy(subDs));

END_UNIT

UNIT(SubScribeDs_insertTest)
   	int i;
   	size_t _numberOfSubsribers = 300;
    int key;
    SubScribeDs_t* subDs;
    SubScribeDs_FiledToUpdate filed;
    DataType_u* data;
    subDs = subScribeDs_Creaty(  _numberOfSubsribers);
    ASSERT_THAT(NULL != subDs);
	for(i = 0; i < 5000; ++i)
	{
        MAKEIMSI(key);
        filed = rand()%9;
        data=calloc(1,sizeof(DataType_u));
        Subds_data(filed,data);
        ASSERT_THAT(SUBSCRIBE_DS_SUCCESS == subScribeDs_Set(subDs, key, filed,data));
	}

    ASSERT_THAT(SUBSCRIBE_DS_SUCCESS == subScribeDs_Destroy(subDs));
END_UNIT


/******************************************/
UNIT(SubScribeDs_ReoprtTest)
   	int i;
   	size_t _numberOfSubsribers = 300;
    size_t key;
    SubScribeDs_t* subDs;
    SubScribeDs_FiledToUpdate filed;
    DataType_u* data;
    subDs = subScribeDs_Creaty(  _numberOfSubsribers);
    ASSERT_THAT(NULL != subDs);
	for(i = 0; i < 100000; ++i)
	{
        MAKEIMSI(key);
        filed = rand()%9;
        data=calloc(1,sizeof(DataType_u));
        Subds_data(filed,data);
        subScribeDs_Set(subDs, key, filed,data);
	}
    ASSERT_THAT(SUBSCRIBE_DS_SUCCESS  == subScribeDs_Report(subDs,key, SubScribeDs_ReportType_AllSubScribes,printSub ));
    ASSERT_THAT(SUBSCRIBE_DS_SUCCESS  == subScribeDs_Report(subDs,key, SubScribeDs_ReportType_AllSubScribes,printSub ));
    ASSERT_THAT(SUBSCRIBE_DS_SUCCESS == subScribeDs_Destroy(subDs));
END_UNIT

/******************************************/
TEST_SUITE(DataManager_Tests)

  /*  TEST(SubScribe_creatTest)
    TEST(SubScribe_insertAndremove)
    TEST(SubScribeDs_creatTest)
    TEST(SubScribeDs_insertTest)*/
    TEST(SubScribeDs_ReoprtTest)

END_SUITE
