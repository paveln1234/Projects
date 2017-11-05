#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "safeThreadHashMap.h"
#include "subscribeDs.h"
#include "subscriber.h"
#define MAGICNUMBER 0xDEADDAAD
#define NEW 1
#define EXISTS 0
#define MESSAGESIZE 512

/*Define struct SubSribeDS_t*/
struct SubScribeDs_t
{
    size_t m_magicNumber;
    STHashMap_t* m_hashMap;
    pthread_mutex_t m_mutext;
};

typedef struct SubDataUpdate_t
{
    SubScribeDs_FiledToUpdate m_filed;
    DataType_u* m_data;
}SubDataUpdate_t;

/**********internal function********/
static size_t SubUpdateFunction(const void* _key, void* _value, void* _context);
static void InternalSubUpdate(size_t _msisd, SubScribeData_t* _subSriber, SubDataUpdate_t* _data);
static size_t PrintSubScriber(const void* _msisdn, void* _subScriber,void* _context);
static void subScribeDestroy(void* _item);
static size_t PrintAllSubScriber(const void* _msisdn, void* _subScriber,void* _context);

/**********internal hash function*************/
static int isEqualFunc(size_t* _num1, size_t* _num2);
size_t hashfunc(char* _str);


/***************************************************/
SubScribeDs_t* subScribeDs_Creaty(size_t _numberOfSubsribers)
{
    SubScribeDs_t* newSub = NULL;
    if(0 ==_numberOfSubsribers )
    {
        return NULL;
    }
    newSub = calloc(1,sizeof(SubScribeDs_t));
    if(NULL == newSub)
    {
        return NULL;
    }

    if(pthread_mutex_init(&newSub->m_mutext,NULL))
    {
        free(newSub);
        return NULL;
    }
    newSub->m_hashMap = HashMap_Create(_numberOfSubsribers, (HashFunction) hashfunc, (EqualityFunction) isEqualFunc);
    if(NULL == newSub->m_hashMap)
    {
        pthread_mutex_destroy(&newSub->m_mutext);
        free(newSub);
        return NULL;
    }
    newSub->m_magicNumber = MAGICNUMBER;

return newSub;
}

/***************************************************/
SubScribeDs_Result subScribeDs_Destroy(SubScribeDs_t* _subScribeDs)
{
    if(NULL == _subScribeDs || MAGICNUMBER != _subScribeDs->m_magicNumber)
    {
        return SUBSCRIBE_DS_UNINITIALIZED_ERROR;
    }
    HashMap_Destroy(&_subScribeDs->m_hashMap,NULL,subScribeDestroy);
    _subScribeDs->m_magicNumber = 0;
    pthread_mutex_destroy(&_subScribeDs->m_mutext);
    free(_subScribeDs);

return SUBSCRIBE_DS_SUCCESS;
}
/***************************************************/
SubScribeDs_Result subScribeDs_Set(SubScribeDs_t* _subScribeDs, size_t _msisdn ,SubScribeDs_FiledToUpdate _filed,DataType_u* _data)
{
    void* junk;
    SubScribeData_t* newSubsciber;
    SubDataUpdate_t*  newUpdate;
    if(NULL == _subScribeDs || MAGICNUMBER != _subScribeDs->m_magicNumber)
    {
        return SUBSCRIBE_DS_UNINITIALIZED_ERROR;
    }
    newUpdate = (SubDataUpdate_t*) malloc(sizeof(SubDataUpdate_t));
    if(NULL == newUpdate)
    {
        return SUBSCRIBE_DS_ERRROR;
    }
    newUpdate->m_filed = _filed;
    newUpdate->m_data = _data;

    if (MAP_KEY_NOT_FOUND_ERROR == HashMap_Find(_subScribeDs->m_hashMap,(void*)&_msisdn,SubUpdateFunction,(void**)&junk,newUpdate))
    {
        pthread_mutex_lock(&_subScribeDs->m_mutext);
        newSubsciber = SubScribe_Creaty(_msisdn);
        if(NULL == newSubsciber)
        {
            pthread_mutex_unlock(&_subScribeDs->m_mutext);
            return SUBSCRIBE_DS_ERRROR;
        }
        InternalSubUpdate(_msisdn,newSubsciber,newUpdate);
        if(MAP_KEY_DUPLICATE_ERROR== HashMap_Insert(_subScribeDs->m_hashMap,(void*)&_msisdn,(void*)newSubsciber))
        {
            pthread_mutex_unlock(&_subScribeDs->m_mutext);
            HashMap_Find(_subScribeDs->m_hashMap,(void*)&_msisdn,SubUpdateFunction,(void**)&junk,newUpdate);
            free(newUpdate);
            return SUBSCRIBE_DS_SUCCESS;
        }
        pthread_mutex_unlock(&_subScribeDs->m_mutext);
    }
    free(newUpdate);

return SUBSCRIBE_DS_SUCCESS;
}

SubScribeDs_Result subScribeDs_Report(SubScribeDs_t* _subScribeDs,size_t _msisdn, SubScribeDs_ReportType _type, SubScribe_ReportFuncition _action)
{
    void* junk;
    if(NULL == _subScribeDs || MAGICNUMBER != _subScribeDs->m_magicNumber || NULL == _action)
    {
        return SUBSCRIBE_DS_UNINITIALIZED_ERROR;
    }

    if(SubScribeDs_ReportType_OneSubScribe == _type)
    {
        if(MAP_KEY_NOT_FOUND_ERROR == HashMap_Find(_subScribeDs->m_hashMap,(void*)&_msisdn,(KeyValueActionFunction)PrintSubScriber,(void**)&junk,(void*)_action))
        {
            return SUBSCRIBE_DS_ERRROR;
        }
    }
    else
    {
        HashMap_ForEach(_subScribeDs->m_hashMap,(KeyValueActionFunction)PrintAllSubScriber,(void*)_action);
    }

return SUBSCRIBE_DS_SUCCESS;
}

/***************************************************/
static void subScribeDestroy(void* _item)
{
    SubScribe_Destroy((SubScribeData_t*)_item);
return;
}

/***************************************************/
static size_t PrintSubScriber(const void* _msisdn, void* _subScriber,void* _context)
{
    SubScribeData_t* tempSubScriber = (SubScribeData_t*) _subScriber;
    char buffer[MESSAGESIZE];
    SubScribe_ReportFuncition action =  (SubScribe_ReportFuncition)_context;
    SubScribe_SubSribeToSrc(tempSubScriber,buffer);
    action(buffer);
return 1;
}
/***************************************************/
static size_t PrintAllSubScriber(const void* _msisdn, void* _subScriber,void* _context)
{
    SubScribeData_t* tempSubScriber = (SubScribeData_t*) _subScriber;
    char buffer[MESSAGESIZE];
    SubScribe_ReportFuncition action =  (SubScribe_ReportFuncition)_context;
    SubScribe_SubSribeToSrc(tempSubScriber,buffer);
    action(buffer);
    SubScribe_SubSribeReset(tempSubScriber);
return 1;
}

/***************************************************/
static size_t SubUpdateFunction(const void* _key, void* _value, void* _context)
{
    size_t msisd = (size_t)_key;
    SubScribeData_t* subSriber = (SubScribeData_t*)_value;
    SubDataUpdate_t* data = (SubDataUpdate_t*)_context;
    InternalSubUpdate(msisd,subSriber,data);

return 1;
}
/*****************************************************/
static void InternalSubUpdate(size_t _msisd, SubScribeData_t* _subSriber, SubDataUpdate_t* _data)
{
    switch(_data->m_filed)
    {
    case OUT_CALL_WITHIN_OPERATOR:
            SubScribe_AddOutCallWightOperator(_subSriber,_data->m_data->sec);
            break;
	case IN_CALL_WITHIN_OPERATOR:
            SubScribe_AddInCallWightOperator(_subSriber,_data->m_data->sec);
            break;
	case OUT_CALL_OUTSIDE_OPERATOR:
            SubScribe_AddOutCallOutsideOperator(_subSriber,_data->m_data->sec);
        break;
	case IN_CALL_OUTSIDE_OPERATOR:
            SubScribe_AddInCallOutsideOperator(_subSriber,_data->m_data->sec);
        break;
	case OUT_SMS_WITHIN_OPERATOR:
            SubScribe_AddOutSmsWightOperator(_subSriber);
        break;
	case IN_SMS_WITHIN_OPERATOR:
            SubScribe_AddInSmsWightOperator(_subSriber);
        break;
	case OUT_SMS_OUTSIDE_OPERATOR:
            SubScribe_AddOutSmsOutsideOperator(_subSriber);
        break;
	case IN_SMS_OUTSIDE_OPERATOR:
            SubScribe_AddInSmsOutsideOperator(_subSriber);
        break;
	case MB_DOWNLOADED:
            SubScribe_AddDownload(_subSriber,_data->m_data->data);
        break;
	case MB_UPLOADED:
            SubScribe_AddUpload(_subSriber,_data->m_data->data);
        break;
    }
return;
}

/***************************************************/
int isEqualFunc(size_t* _num1, size_t* _num2)
{
	return (*_num1 == *_num2);
}
/***************************************************/
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
