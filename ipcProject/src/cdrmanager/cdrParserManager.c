#include <stdio.h>/*calloc*/
#include <stdlib.h>/*size_t*/
#include<string.h>
#include <pthread.h> /*for thread and mutex function*/
#include "cdrMessager.h"
#include "cdrParser.h"
#include "cdrParserManager.h"
#include "safeThreadQueue.h"
#include "discoverer.h"
#define QUEUESIZE 10
#define MAGICNUMBER 0xDEADBEAF
#define ALIVE 1
#define DEAD 0
#define RUN 1
#define PAUSE 0

/*Define Data structure Cdr Parser Manager*/
struct CdrParserManager_t
{
    size_t m_magicNumber;
    STQueueu_t* m_discovererToCdrManagerQueue;
    STQueueu_t* m_cdrToDataManagerQueue;
    CdrParser_t* m_parser;
    Discoverer_t* m_discoverer;
    pthread_mutex_t m_mutex;
};
/****************************************************/
CdrParserManager_t* CdrParserManager_Creaty(STQueueu_t* _cdrToDataManagerQueue, char* _inputFolderPath, char* _inprogressFolderPath,
                                            char* _doneFolderPath, size_t _threadNumber)
    {
    CdrParserManager_t* newCdrManager;

    if(NULL == _cdrToDataManagerQueue || NULL == _inputFolderPath || NULL == _inprogressFolderPath
       || NULL == _doneFolderPath || 0 == _threadNumber)
    {
        return NULL;
    }
    newCdrManager = calloc(1,sizeof(CdrParserManager_t));
    if(NULL == newCdrManager )
    {
        return NULL;
    }
    newCdrManager->m_cdrToDataManagerQueue = _cdrToDataManagerQueue;

    newCdrManager->m_discovererToCdrManagerQueue = SafeThreadQueue_Create(QUEUESIZE);
    if(NULL == newCdrManager->m_discovererToCdrManagerQueue)
    {
        free(newCdrManager);
        return NULL;
    }

    newCdrManager->m_parser = CdrParser_Creaty((void*)newCdrManager, _inprogressFolderPath, _doneFolderPath, _threadNumber);
    if(NULL == newCdrManager->m_parser )
    {
        SafeTreadQueue_Destroy(newCdrManager->m_discovererToCdrManagerQueue,NULL);
        free(newCdrManager);
        return NULL;
    }
    newCdrManager->m_discoverer =Discoverer_Creaty((void*)newCdrManager,_inputFolderPath, _inprogressFolderPath,INTERVAL);
    if(NULL == newCdrManager->m_discoverer)
    {
        CdrParser_Destroy(newCdrManager->m_parser);
        SafeTreadQueue_Destroy(newCdrManager->m_discovererToCdrManagerQueue,NULL);
        free(newCdrManager);
        return NULL;
    }
    if(pthread_mutex_init(&newCdrManager->m_mutex,NULL))
    {
        Discoverer_Destroy(newCdrManager->m_discoverer);
        CdrParser_Destroy(newCdrManager->m_parser);
        SafeTreadQueue_Destroy(newCdrManager->m_discovererToCdrManagerQueue,NULL);
        free(newCdrManager);
        return NULL;
    }
    newCdrManager->m_magicNumber = MAGICNUMBER;
    printf("menager creaty\n");
return newCdrManager;
}

CdrParserManager_Result CdrParserManager_Destroy(CdrParserManager_t* _cdrParserManager)
{
    if(NULL == _cdrParserManager || MAGICNUMBER != _cdrParserManager->m_magicNumber)
    {
        return CDR_MANAGER_UNINITIALIZED_ERROR;
    }
    if(DISCOVERER_SUCCESS != Discoverer_Destroy(_cdrParserManager->m_discoverer))
    {
        perror("discoverer destroy failed");
    }
    if (CDR_PARSER_SUCCESS != CdrParser_Destroy(_cdrParserManager->m_parser))
    {
        perror("cdr parser destroy failed");
    }
    SafeTreadQueue_Destroy(_cdrParserManager->m_discovererToCdrManagerQueue,NULL);
    _cdrParserManager->m_magicNumber = 0;
    free(_cdrParserManager);

return CDR_MANAGER_SUCCESS;
}

CdrParserManager_Result CdrParserManager_Run(CdrParserManager_t* _cdrParserManager)
{
    if(NULL == _cdrParserManager || MAGICNUMBER != _cdrParserManager->m_magicNumber)
    {
        return CDR_MANAGER_UNINITIALIZED_ERROR;
    }

    if( DISCOVERER_SUCCESS != Discoverer_Run(_cdrParserManager->m_discoverer))
    {
           return CDR_MANAGER_RUN_ERRROR;
    }

    if(CDR_PARSER_SUCCESS !=CdrParser_Run(_cdrParserManager->m_parser))
    {
           return CDR_MANAGER_RUN_ERRROR;
    }

return CDR_MANAGER_SUCCESS;
}

CdrParserManager_Result CdrParserManager_Pause(CdrParserManager_t* _cdrParserManager)
{
    if(NULL == _cdrParserManager || MAGICNUMBER != _cdrParserManager->m_magicNumber)
    {
        return CDR_MANAGER_UNINITIALIZED_ERROR;
    }

    if( DISCOVERER_SUCCESS != Discoverer_Pause(_cdrParserManager->m_discoverer))
    {
           return CDR_MANAGER_PAUSE_ERROR;
    }

    if(CDR_PARSER_SUCCESS !=CdrParser_Pause(_cdrParserManager->m_parser))
    {
           return CDR_MANAGER_PAUSE_ERROR;
    }

return CDR_MANAGER_SUCCESS;
}


CdrParserManager_Result CdrParserManager_Resume(CdrParserManager_t* _cdrParserManager)
{
    if(NULL == _cdrParserManager || MAGICNUMBER != _cdrParserManager->m_magicNumber)
    {
        return CDR_MANAGER_UNINITIALIZED_ERROR;
    }

    if( DISCOVERER_SUCCESS != Discoverer_Resume(_cdrParserManager->m_discoverer))
    {
           return CDR_MANAGER_RUN_ERRROR;
    }

    if(CDR_PARSER_SUCCESS !=CdrParser_Resume(_cdrParserManager->m_parser))
    {
           return CDR_MANAGER_RUN_ERRROR;
    }

return CDR_MANAGER_SUCCESS;
}

CdrParserManager_Result CdrParserManager_PutCdrFileName(void* _cdrParserManager,char* _fileNameToInsert)
{
    CdrParserManager_t* cdrManager = (CdrParserManager_t*)_cdrParserManager;

     if(NULL == cdrManager || MAGICNUMBER != cdrManager->m_magicNumber)
    {
        return CDR_MANAGER_UNINITIALIZED_ERROR;
    }
    SafeTreadQueue_Enqueue(cdrManager->m_discovererToCdrManagerQueue,(void*)_fileNameToInsert);

return CDR_MANAGER_SUCCESS;
}

CdrParserManager_Result CdrParserManager_GetCdrFileName(void* _cdrParserManager,void** _buffer)
{
    CdrParserManager_t* cdrManager = (CdrParserManager_t*)_cdrParserManager;

    if(NULL == cdrManager || MAGICNUMBER != cdrManager->m_magicNumber || NULL == _buffer)
    {
        return CDR_MANAGER_UNINITIALIZED_ERROR;
    }
    SafeTreadQueue_Dequeue(cdrManager->m_discovererToCdrManagerQueue,_buffer);

return CDR_MANAGER_SUCCESS;
}

CdrParserManager_Result CdrParserManager_sendCdrMessage(void* _cdrParserManager,void* _message)
{
    CdrParserManager_t* cdrManager = (CdrParserManager_t*)_cdrParserManager;
     if(NULL == cdrManager || MAGICNUMBER != cdrManager->m_magicNumber)
    {
        return CDR_MANAGER_UNINITIALIZED_ERROR;
    }

    SafeTreadQueue_Enqueue(cdrManager->m_cdrToDataManagerQueue,(void*)_message);

return CDR_MANAGER_SUCCESS;

}

