#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "safeThreadHashMap.h"
#include "oparetorDs.h"
#include "operator.h"
#define MAGICNUMBER 0xDEADDAAD
#define NEW 1
#define EXISTS 0
#define MESSAGESIZE 256


/*Define struct SubSribeDS_t*/
struct OperatorDs_t
{
    size_t m_magicNumber;
    STHashMap_t* m_hashMap;
    pthread_mutex_t m_mutext;
};

typedef struct OperatorUpdate_t
{
    OperatorDs_FiledToUpdate m_filed;
    size_t m_data;
}OperatorUpdate_t;

/**********internal function********/
static size_t OperatorUpdateFunction(const void* _key, void* _value, void* _context);
static void InternalOperatorUpdate(size_t _mmsMnc, OperatorData_t* _subSriber, OperatorUpdate_t* _data);
static size_t PrintOperator(const void* _mmsMnc, void* _operator,void* _context);
static void OperatorDestroy(void* _item);
static size_t PrintAllOperators(const void* _mmsMnc, void* _operator,void* _context);


/**********internal hash function*************/
static int isEqualFunc(size_t* _num1, size_t* _num2);
static size_t hashfunc(char* _str);


/***************************************************/
OperatorDs_t* OperatorDs_Creaty(size_t _numberOfOperators)
{
    OperatorDs_t* newOp = NULL;
    if(0 ==_numberOfOperators )
    {
        return NULL;
    }
    newOp = calloc(1,sizeof(OperatorDs_t));
    if(NULL == newOp)
    {
        return NULL;
    }

    if(pthread_mutex_init(&newOp->m_mutext,NULL))
    {
        free(newOp);
        return NULL;
    }
    newOp->m_hashMap = HashMap_Create(_numberOfOperators, (HashFunction) hashfunc, (EqualityFunction) isEqualFunc);
    if(NULL == newOp->m_hashMap)
    {
        pthread_mutex_destroy(&newOp->m_mutext);
        free(newOp);
        return NULL;
    }
    newOp->m_magicNumber = MAGICNUMBER;

return newOp;
}
/***************************************************/
operatorDs_Result OperatorDs_Destroy(OperatorDs_t* _operatorDs)
{
    if(NULL == _operatorDs || MAGICNUMBER != _operatorDs->m_magicNumber)
    {
        return OPERATOR_DS_UNINITIALIZED_ERROR;
    }
    HashMap_Destroy(&_operatorDs->m_hashMap,NULL,OperatorDestroy);
    _operatorDs->m_magicNumber = 0;
    pthread_mutex_destroy(&_operatorDs->m_mutext);
    free(_operatorDs);

return OPERATOR_DS_SUCCESS;
}
/***************************************************/
operatorDs_Result OperatorDs_Set(OperatorDs_t* _operatorDs,size_t _mmcMnc,char* _OpBrandName,OperatorDs_FiledToUpdate _filed, size_t _data)
{
    void* junk;
    OperatorData_t* newOperator;
    OperatorUpdate_t*  newUpdate;
    if(NULL == _operatorDs || MAGICNUMBER != _operatorDs->m_magicNumber)
    {
        return OPERATOR_DS_UNINITIALIZED_ERROR;
    }
    newUpdate = (OperatorUpdate_t*) malloc(sizeof(OperatorUpdate_t));
    if(NULL == newUpdate)
    {
        return OPERATOR_DS_ERRROR;
    }
    newUpdate->m_filed = _filed;
    newUpdate->m_data = _data;

    if (MAP_KEY_NOT_FOUND_ERROR == HashMap_Find(_operatorDs->m_hashMap,(void*)&_mmcMnc, OperatorUpdateFunction, (void**)&junk,newUpdate))
    {
       /* printf("not fund newUPdatr first time - mmc %ld\n" ,newUpdate->m_filed );*/
        pthread_mutex_lock(&_operatorDs->m_mutext);
            newOperator = OperatorData_Creaty(_mmcMnc, _OpBrandName);
            if(NULL == newOperator)
            {
                pthread_mutex_unlock(&_operatorDs->m_mutext);
                return OPERATOR_DS_ERRROR;
            }
            InternalOperatorUpdate(_mmcMnc,newOperator,newUpdate);
            if(MAP_KEY_DUPLICATE_ERROR== HashMap_Insert(_operatorDs->m_hashMap,(void*)&_mmcMnc,(void*)newOperator))
            {
                pthread_mutex_unlock(&_operatorDs->m_mutext);
                if(MAP_KEY_NOT_FOUND_ERROR == HashMap_Find(_operatorDs->m_hashMap,(void*)&_mmcMnc,OperatorUpdateFunction,(void**)&junk,newUpdate))
                   {
                       printf("somethink fuck up whit the hash map");
                   }
                free(newUpdate);
                return OPERATOR_DS_SUCCESS;
            }
        pthread_mutex_unlock(&_operatorDs->m_mutext);
    }
    free(newUpdate);

return OPERATOR_DS_SUCCESS;
}

/***************************************************/
operatorDs_Result OperatorDs_Report(OperatorDs_t* _operatorDs,size_t m_mmcMnc, OperatorDs_ReportType _type, Operator_ReportFuncition _action)
{
    void* junk;
    if(NULL == _operatorDs || MAGICNUMBER != _operatorDs->m_magicNumber || NULL == _action)
    {
        return OPERATOR_DS_UNINITIALIZED_ERROR;
    }

    if(OperatorDs_ReportType_OneOperator == _type)
    {
        if(MAP_KEY_NOT_FOUND_ERROR == HashMap_Find(_operatorDs->m_hashMap,(void*)&m_mmcMnc,(KeyValueActionFunction)PrintOperator,(void**)&junk,(void*)_action))
        {
            return OPERATOR_DS_ERRROR;
        }
    }
    else
    {
        HashMap_ForEach(_operatorDs->m_hashMap,(KeyValueActionFunction)PrintAllOperators,(void*)_action);
    }

return OPERATOR_DS_SUCCESS;
}


/***************************************************/
static size_t PrintOperator(const void* _mmsMnc, void* _subScriber,void* _context)
{
    OperatorData_t* tempOperator = (OperatorData_t*) _subScriber;
    char buffer[MESSAGESIZE];

    Operator_ReportFuncition action =  (Operator_ReportFuncition)_context;
    OperatorData_OperatorToStr(tempOperator,buffer);
    action(buffer);

return 1;
}
/***************************************************/
static size_t PrintAllOperators(const void* _mmsMnc, void* _Operator,void* _context)
{
    OperatorData_t* tempOperator = (OperatorData_t*) _Operator;
    char buffer[MESSAGESIZE];
    Operator_ReportFuncition action =  (Operator_ReportFuncition)_context;

    OperatorData_OperatorToStr(tempOperator,buffer);
    action(buffer);
    OperatorData_OperatorReset(tempOperator);

return 1;
}

/***************************************************/
static void OperatorDestroy(void* _item)
{
    OperatorData_Destroy((OperatorData_t*)_item);

return;
}

/***************************************************/
static size_t OperatorUpdateFunction(const void* _key, void* _value, void* _context)
{
    size_t mmcMnc = (size_t)_key;
    OperatorData_t* Operator = (OperatorData_t*)_value;
    OperatorUpdate_t* data = (OperatorUpdate_t*)_context;
    InternalOperatorUpdate(mmcMnc,Operator,data);
return 1;
}

/***************************************************/
static void InternalOperatorUpdate(size_t _mmsMnc, OperatorData_t* _operator, OperatorUpdate_t* _data)
{

    switch(_data->m_filed)
    {
        case OPERATOR_INCOMING_CAll_FROM_OPERATOR:
                OperatorData_AddInCallFromOperator(_operator,_data->m_data);
                break;

        case OPERATOR_OUTGOING_CALL_TO_OPERATOR:
                OperatorData_AddOutCallToOperator(_operator,_data->m_data);
                break;

        case OPERATOR_INCOMING_SMS_FROM_OPERATOR:
                OperatorData_AddInSmsFromOperator(_operator);

                break;

        case OPERATOR_OUTGOING_SMS_TO_OPERATOR:
                OperatorData_AddOutSmsToOperator(_operator);
                break;
    }

return;
}

/***************************************************/
static int isEqualFunc(size_t* _num1, size_t* _num2)
{
	return (*_num1 == *_num2);
}
/***************************************************/
static size_t hashfunc(char* _str)
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
