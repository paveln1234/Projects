#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "cdrMessager.h"
#include "subscribeDs.h"
#include"oparetorDs.h"
#include "safeThreadQueue.h"
#include "datamanager.h"
#define ALIVE 1
#define DEAD 0
#define RUN 1
#define PAUSE 0
#define OPNAME 64
#define CALLTYPE 10
#define MAGICNUMBER 0xDEADDEAD


struct DataManager_t
{
    size_t m_magicNumber;
    STQueueu_t* m__cdrToDataManagerQueue;
    OperatorDs_t* m_operatorDs;
    SubScribeDs_t* m_subScriberDs;
    pthread_t* m_threadArray;
    pthread_mutex_t m_pauseMutex;
    pthread_cond_t m_pauseCond;
    size_t m_NumberOfThread;
    size_t m_mmcMnc;
    short int m_isAlive;
    short int m_isPause;
};
/************internal function***************/
static void* ThreadFunc(void* _context);
static int CallTypeToInt(char* _callType);
static void datamanager_Updata(DataManager_t* _dataManager,void* _msg);
void MmcMncToBrandName(size_t _mmcmnc, char* _buffer);



/***********************************************/
DataManager_t* DataManager_Creaty(STQueueu_t* _cdrToDataManagerQueue,size_t _mmcMnc, size_t _numberOfthread,size_t _numOfOP,size_t _numOfSub)
{
    DataManager_t* newManager;
    if(NULL == _cdrToDataManagerQueue || 0 >= _numberOfthread)
    {
        return NULL;
    }

    newManager = calloc(1, sizeof(DataManager_t));
    if(NULL == newManager)
    {
        return NULL;
    }

    newManager->m_threadArray = calloc(_numberOfthread,sizeof(pthread_t));
    if(NULL == newManager->m_threadArray)
    {
        free(newManager);
        return NULL;
    }

    newManager->m_operatorDs = OperatorDs_Creaty(_numOfOP);
    if(NULL == newManager->m_operatorDs)
    {
        free(newManager->m_threadArray);
        free(newManager);
        return NULL;
    }

    newManager->m_subScriberDs = subScribeDs_Creaty(_numOfSub);
    if(NULL ==newManager->m_subScriberDs)
    {
        OperatorDs_Destroy(newManager->m_operatorDs);
        free(newManager->m_threadArray);
        free(newManager);
        return NULL;
    }

    if(pthread_mutex_init(&newManager->m_pauseMutex,NULL))
    {
        subScribeDs_Destroy(newManager->m_subScriberDs);
        OperatorDs_Destroy(newManager->m_operatorDs);
        free(newManager->m_threadArray);
        free(newManager);
        return NULL;
    }

    if(pthread_cond_init(&newManager->m_pauseCond,NULL))
    {
        pthread_mutex_destroy(&newManager->m_pauseMutex);
        subScribeDs_Destroy(newManager->m_subScriberDs);
        OperatorDs_Destroy(newManager->m_operatorDs);
        free(newManager->m_threadArray);
        free(newManager);
        return NULL;
    }

    newManager->m__cdrToDataManagerQueue = _cdrToDataManagerQueue;
    newManager->m_NumberOfThread = _numberOfthread;
    newManager->m_mmcMnc = _mmcMnc;
    newManager->m_isAlive = ALIVE;
    newManager->m_isPause = PAUSE;
    newManager->m_magicNumber = MAGICNUMBER;

return newManager;
}

/*********************************/
DataManager_Result DataManager_Destroy(DataManager_t* _dataManager)
{
    size_t i = 0;

    if(NULL == _dataManager || MAGICNUMBER != _dataManager->m_magicNumber)
    {
        return DATA_MANAGER_UNINITIALIZED_ERROR;
    }
    _dataManager->m_isPause = RUN;
    _dataManager->m_isAlive = DEAD;

    pthread_cond_broadcast(&_dataManager->m_pauseCond);
    for(; i<_dataManager->m_NumberOfThread; ++i)
    {
        pthread_cancel(_dataManager->m_threadArray[i]);
    }

    for(; i<_dataManager->m_NumberOfThread; ++i)
    {
        pthread_join(_dataManager->m_threadArray[i], NULL);
    }

    if(pthread_cond_destroy(&_dataManager->m_pauseCond))
    {
        pthread_cond_destroy(&_dataManager->m_pauseCond);
    }
    pthread_mutex_destroy(&_dataManager->m_pauseMutex);
    OperatorDs_Destroy(_dataManager->m_operatorDs);
    subScribeDs_Destroy(_dataManager->m_subScriberDs);
    _dataManager->m_magicNumber = 0;
    free(_dataManager->m_threadArray);
    free(_dataManager);
printf("Data Manager Destroy\n");
return DATA_MANAGER_SUCCESS;
}
/***************************************/
DataManager_Result DataManager_Run(DataManager_t* _dataManager)
{
    size_t i;

    if(NULL == _dataManager || MAGICNUMBER != _dataManager->m_magicNumber)
    {
        return DATA_MANAGER_UNINITIALIZED_ERROR;
    }
    printf("Data Manager Start\n");
    _dataManager->m_isPause = RUN;
    for(i=0 ; i <_dataManager->m_NumberOfThread; ++i)
    {
        pthread_create(&_dataManager->m_threadArray[i],NULL,ThreadFunc,_dataManager);
    }

return DATA_MANAGER_SUCCESS;
}


/***************************************/
DataManager_Result DataManager_Pause(DataManager_t* _dataManager)
{
    if(NULL == _dataManager || MAGICNUMBER != _dataManager->m_magicNumber)
    {
        return DATA_MANAGER_UNINITIALIZED_ERROR;
    }
        pthread_mutex_lock(&_dataManager->m_pauseMutex);
        _dataManager->m_isPause = PAUSE;
    pthread_mutex_unlock(&_dataManager->m_pauseMutex);

return DATA_MANAGER_SUCCESS;
}

/***************************************/
DataManager_Result DataManager_Resume(DataManager_t* _dataManager)
{
    if(NULL == _dataManager || MAGICNUMBER != _dataManager->m_magicNumber)
    {
        return DATA_MANAGER_UNINITIALIZED_ERROR;
    }

    pthread_mutex_lock(&_dataManager->m_pauseMutex);
        _dataManager->m_isPause = RUN;
    pthread_mutex_unlock(&_dataManager->m_pauseMutex);
    pthread_cond_broadcast(&_dataManager->m_pauseCond);

return DATA_MANAGER_SUCCESS;
}

/***************************************/
DataManager_Result DataManager_CreatyReport(DataManager_t* _dataManager, ReportType _reportType,size_t _subMsinsNumber, size_t _opMmcMnc, DataMaager_ReportFuncition _action)
{
    switch(_reportType)
    {
        case ReportType_OneSubScribe:
                subScribeDs_Report(_dataManager->m_subScriberDs,_subMsinsNumber,SubScribeDs_ReportType_OneSubScribe,(SubScribe_ReportFuncition)_action);
                break;
        case   ReportType_AllSubScribes:
                  subScribeDs_Report(_dataManager->m_subScriberDs,_subMsinsNumber,SubScribeDs_ReportType_AllSubScribes,(SubScribe_ReportFuncition)_action);
                  break;
        case ReportType_OneOperator:
                OperatorDs_Report(_dataManager->m_operatorDs,_opMmcMnc,OperatorDs_ReportType_OneOperator,(Operator_ReportFuncition)_action);
                break;
        case ReportType_AllOperators:
                OperatorDs_Report(_dataManager->m_operatorDs,_opMmcMnc,OperatorDs_ReportType_AllOperators, (Operator_ReportFuncition)_action);
                break;
    }
return DATA_MANAGER_SUCCESS;
}

/***************************************/
static void* ThreadFunc(void* _context)
{
    int oldtype;
    void* item;
    DataManager_t* dataManager = (DataManager_t*)_context;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);

    while (ALIVE == dataManager->m_isAlive)
    {
        pthread_mutex_lock(&dataManager->m_pauseMutex);
            while(PAUSE == dataManager->m_isPause)
            {
                pthread_cond_wait(&dataManager->m_pauseCond,&dataManager->m_pauseMutex);
            }
            SafeTreadQueue_Dequeue(dataManager->m__cdrToDataManagerQueue,(void**)&item);
            datamanager_Updata(dataManager,item);
         pthread_mutex_unlock(&dataManager->m_pauseMutex);
     }

return NULL;
}

/************************************************************************/
static void datamanager_Updata(DataManager_t* _dataManager,void* _msg)
{
    int res = 0;
    size_t msisdn = 0;
    size_t msgMmcMnc = 0;
    char callType[CALLTYPE];
    char OpName[OPNAME];
    DataType_u* data;

    CdrMessage_t* msg = (CdrMessage_t*)_msg;
    data =malloc(sizeof(DataType_u));

    CdrMessage_GetMsisdn(msg,&msisdn);
    CdrMessage_GetCallType(msg,callType);
    CdrMessage_GetComPartyMccmnc(msg,&msgMmcMnc);
    res = CallTypeToInt(callType);
    switch(res)
    {
        case 0:
                CdrMessage_GetDuration(msg,&data->sec);
                if(_dataManager->m_mmcMnc == msgMmcMnc)
                {
                    subScribeDs_Set(_dataManager->m_subScriberDs, msisdn ,OUT_CALL_WITHIN_OPERATOR,data);
                }
                else
                {
                    subScribeDs_Set(_dataManager->m_subScriberDs, msisdn ,OUT_CALL_OUTSIDE_OPERATOR,data);
                    MmcMncToBrandName(msgMmcMnc,OpName);
                    OperatorDs_Set(_dataManager->m_operatorDs,msgMmcMnc,OpName,OPERATOR_OUTGOING_CALL_TO_OPERATOR,data->sec);
                }
                break;

        case 1:
                CdrMessage_GetDuration(msg,&data->sec);
                if(_dataManager->m_mmcMnc == msgMmcMnc)
                {
                    subScribeDs_Set(_dataManager->m_subScriberDs, msisdn ,IN_CALL_WITHIN_OPERATOR,data);
                }
                else
                {
                    subScribeDs_Set(_dataManager->m_subScriberDs, msisdn ,IN_CALL_OUTSIDE_OPERATOR,data);
                    MmcMncToBrandName(msgMmcMnc,OpName);
                    OperatorDs_Set(_dataManager->m_operatorDs,msgMmcMnc,OpName,OPERATOR_INCOMING_CAll_FROM_OPERATOR,data->sec);
                }
                break;

        case 2:
                data->sec =1;
                if(_dataManager->m_mmcMnc == msgMmcMnc)
                {
                    subScribeDs_Set(_dataManager->m_subScriberDs, msisdn ,OUT_SMS_WITHIN_OPERATOR,data);
                }
                else
                {
                    subScribeDs_Set(_dataManager->m_subScriberDs, msisdn ,OUT_SMS_OUTSIDE_OPERATOR,data);
                    MmcMncToBrandName(msgMmcMnc,OpName);
                    OperatorDs_Set(_dataManager->m_operatorDs,msgMmcMnc,OpName,OPERATOR_OUTGOING_SMS_TO_OPERATOR,data->sec);
                }
                break;

        case 3:
                data->sec =1;
                if(_dataManager->m_mmcMnc == msgMmcMnc)
                {
                    subScribeDs_Set(_dataManager->m_subScriberDs, msisdn ,IN_SMS_WITHIN_OPERATOR,data);
                }
                else
                {
                    subScribeDs_Set(_dataManager->m_subScriberDs, msisdn ,IN_SMS_OUTSIDE_OPERATOR,data);
                    MmcMncToBrandName(msgMmcMnc,OpName);
                    OperatorDs_Set(_dataManager->m_operatorDs,msgMmcMnc,OpName,OPERATOR_INCOMING_SMS_FROM_OPERATOR,data->sec);
                }
                break;

        case 4:
                    CdrMessage_GetDownload(msg,&data->data);
                    subScribeDs_Set(_dataManager->m_subScriberDs, msisdn ,MB_DOWNLOADED,data);
                    CdrMessage_GetUpload(msg,&data->data);
                    subScribeDs_Set(_dataManager->m_subScriberDs, msisdn ,MB_UPLOADED,data);
                break;
    }
    free(data);
    CdrMessage_Desroy(msg);
return;
}


/***************************************************/
static int CallTypeToInt(char* _callType)
{
    if(0 == strcmp(_callType,"MOC"))
    {
        return 0;
    }
    else  if(0 == strcmp(_callType,"MTC"))
    {
        return 1;
    }
    else  if(0 == strcmp(_callType,"SMS-MO"))
    {
        return 2;
    }
    else  if(0 == strcmp(_callType,"SMS-MT"))
    {
        return 3;
    }
    else  if(0 == strcmp(_callType,"GPRS"))
    {
        return 4;
    }

return -1;
}

void MmcMncToBrandName(size_t _mmcmnc, char* _buffer)
{
    switch(_mmcmnc)
    {
            case 41205:
                    strcpy(_buffer,"Celcom");
                    break;
            case 41206:
                    strcpy(_buffer,"Partnet");
                    break;
            case 41207:
                    strcpy(_buffer,"Pelephone");
                    break;
            case 41208:
                    strcpy(_buffer,"Golan Telcome");
                    break;
    }
}


