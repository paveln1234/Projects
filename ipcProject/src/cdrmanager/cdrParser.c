#define _GNU_SOURCE          /* See feature_test_macros(7) */
#include <stdio.h>/*calloc*/
#include <stdlib.h>/*size_T*/
#include <string.h>/*strtok_r*/
#include <pthread.h> /*for thread and mutex function*/
#include <unistd.h>
#include <sys/syscall.h>
#include "cdrMessager.h"
#include "cdrParser.h"
#include "cdrParserManager.h"
#include "fileHandler.h"
#define ALIVE 1
#define DEAD 0
#define RUN 1
#define PAUSE 0
#define FILENAME_LENGHT 64
#define MAGICNUMBER 0xDEADDEAD

 /*Define typedef structure CdrParser_t*/
struct CdrParser_t
{
    size_t m_magicNumber;
    void* m_cdrManager;
    char* m_outPutFolder;
    char* m_inprogressFolder;
    pthread_t* m_threadArray;
    pthread_mutex_t m_pauseMutex;
    pthread_cond_t m_pauseCond;
    size_t m_NumberOfThread;
    short int m_isAlive;
    short int m_isPause;
};


/********static function***********/
/*thread function*/
static void* ThreadFunc(void* _test);
/*the function convert readed line from file in to cdr Message and send it to Cdr Parser Manager */
static void CdrPaser_LineToCdrMessage(char* _line,void* _context);

CdrParser_t* CdrParser_Creaty(void* _cdrParserManager, char* _inprogressFolder, char* _outPutFolder ,size_t _threadNumber)
{
    CdrParser_t* newCdr = NULL;

    if(NULL == _cdrParserManager ||  NULL == _inprogressFolder|| NULL == _outPutFolder|| 0 == _threadNumber)
    {
        return NULL;
    }

    newCdr = calloc(1,sizeof(CdrParser_t));
    if (NULL == newCdr)
    {
        return NULL;
    }

    newCdr->m_threadArray = calloc(_threadNumber,sizeof(pthread_t));
    if(NULL == newCdr->m_threadArray)
    {
        return NULL;
    }
    if(pthread_mutex_init(&newCdr->m_pauseMutex,NULL))
    {
            free(newCdr->m_threadArray);
            free(newCdr);
            return NULL;
    }

    if(pthread_cond_init(&newCdr->m_pauseCond,NULL))
    {
            pthread_mutex_destroy(&newCdr->m_pauseMutex);
            free(newCdr->m_threadArray);
            free(newCdr);
            return NULL;
    }

    newCdr->m_NumberOfThread = _threadNumber;
    newCdr->m_isAlive = ALIVE;
    newCdr->m_isPause = PAUSE;
    newCdr->m_magicNumber = MAGICNUMBER;
    newCdr->m_cdrManager = _cdrParserManager;
    newCdr->m_outPutFolder = _outPutFolder;
    newCdr->m_inprogressFolder = _inprogressFolder;

return newCdr;
}

/************************************/
CdrParser_Result CdrParser_Destroy(CdrParser_t* _cdrParser)
{
    int i=0;

    if(NULL == _cdrParser || MAGICNUMBER != _cdrParser->m_magicNumber)
    {
        return CDR_PARSER_UNINITIALIZED_ERROR;
    }

    _cdrParser->m_isPause = RUN;
    _cdrParser->m_isAlive = DEAD;
    pthread_cond_broadcast(&_cdrParser->m_pauseCond);
    for(; i<_cdrParser->m_NumberOfThread; ++i)
    {
        pthread_cancel(_cdrParser->m_threadArray[i]);
    }
    for(; i<_cdrParser->m_NumberOfThread; ++i)
    {
        pthread_join(_cdrParser->m_threadArray[i], NULL);
    }
    if(pthread_cond_destroy(&_cdrParser->m_pauseCond))
    {
        pthread_cond_destroy(&_cdrParser->m_pauseCond);
    }
    pthread_mutex_destroy(&_cdrParser->m_pauseMutex);
    _cdrParser->m_magicNumber = 0;
    free(_cdrParser->m_threadArray);
    free(_cdrParser);

return CDR_PARSER_SUCCESS;
}

/************************************/
CdrParser_Result CdrParser_Run(CdrParser_t* _cdrParser)
{
    size_t i;
    if(NULL == _cdrParser || MAGICNUMBER != _cdrParser->m_magicNumber)
    {
        return CDR_PARSER_UNINITIALIZED_ERROR;
    }
    _cdrParser->m_isPause = RUN;
    for(i=0 ; i <_cdrParser->m_NumberOfThread; ++i)
    {
        pthread_create(&_cdrParser->m_threadArray[i],NULL,ThreadFunc,_cdrParser);
    }

return CDR_PARSER_SUCCESS;
}

/************************************/
CdrParser_Result CdrParser_Pause(CdrParser_t* _cdrParser)
{
   if(NULL == _cdrParser || MAGICNUMBER != _cdrParser->m_magicNumber)
    {
        return CDR_PARSER_UNINITIALIZED_ERROR;
    }
    pthread_mutex_lock(&_cdrParser->m_pauseMutex);
        _cdrParser->m_isPause = PAUSE;
    pthread_mutex_unlock(&_cdrParser->m_pauseMutex);

return CDR_PARSER_SUCCESS;
}

/************************************/
CdrParser_Result CdrParser_Resume(CdrParser_t* _cdrParser)
{
    if(NULL == _cdrParser || MAGICNUMBER != _cdrParser->m_magicNumber)
    {
        return CDR_PARSER_UNINITIALIZED_ERROR;
    }
    pthread_mutex_lock(&_cdrParser->m_pauseMutex);
    _cdrParser->m_isPause = RUN;
    pthread_mutex_unlock(&_cdrParser->m_pauseMutex);
    pthread_cond_broadcast(&_cdrParser->m_pauseCond);

return CDR_PARSER_SUCCESS;
}


/********static function***********/
static void* ThreadFunc(void* _context)
{
    int oldtype;
    char* filename = calloc(FILENAME_LENGHT,sizeof(char));
    CdrParser_t* cdrParser= (CdrParser_t*)_context;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);

    printf("start parser\n");
    while (ALIVE == cdrParser->m_isAlive)
    {
        pthread_mutex_lock(&cdrParser->m_pauseMutex);
            while(PAUSE == cdrParser->m_isPause)
            {
                pthread_cond_wait(&cdrParser->m_pauseCond,&cdrParser->m_pauseMutex);
            }
            CdrParserManager_GetCdrFileName((void*)cdrParser->m_cdrManager,(void**)&filename);
            if(DEAD == cdrParser->m_isAlive)
            {
                    pthread_mutex_unlock(&cdrParser->m_pauseMutex);
                    return NULL;
            }

            pthread_mutex_unlock(&cdrParser->m_pauseMutex);
    printf("before calling pthread_create getpid: %d getpthread_self: %lu tid:%lu and file : %s\n",getpid(), pthread_self(), syscall(SYS_gettid),filename);
        FileHandler_Read(cdrParser->m_inprogressFolder,filename,(FileHandlerReadActionFunction)CdrPaser_LineToCdrMessage,(void*)cdrParser);
    printf("after calling pthread_create getpid: %d getpthread_self: %lu tid:%lu and file : %s\n",getpid(), pthread_self(), syscall(SYS_gettid),filename);
        FileHandler_MoveFile(filename,cdrParser->m_inprogressFolder,cdrParser->m_outPutFolder);
    printf("after moving pthread_create getpid: %d getpthread_self: %lu tid:%lu and file : %s\n",getpid(), pthread_self(), syscall(SYS_gettid),filename);
    }

return NULL;
}

static void CdrPaser_LineToCdrMessage(char* _line,void* _context)
{
    char* temp;
    CdrParser_t* cdrParser= (CdrParser_t*)_context;
	CdrMessage_t* newMessage;

	newMessage =  CdrMessage_Creaty();

    if(NULL == newMessage)
    {
        return;
    }

    /*  parse and set Cdr Message */
    CdrMessage_SetImsi(newMessage,strtok_r(_line,"|", &temp));
    CdrMessage_SetMsisdn(newMessage,strtok_r(NULL,"|", &temp));
    CdrMessage_SetImei(newMessage,strtok_r(NULL,"|", &temp));
    CdrMessage_SetOperatorName(newMessage,strtok_r(NULL,"|", &temp));
    CdrMessage_SetMccMnc(newMessage,strtok_r(NULL,"|", &temp));
    CdrMessage_SetCallType(newMessage,strtok_r(NULL,"|", &temp));
    CdrMessage_SetCallDate(newMessage,strtok_r(NULL,"|", &temp));
    CdrMessage_SetCallTime(newMessage,strtok_r(NULL,"|", &temp));
    CdrMessage_SetDuration(newMessage,strtok_r(NULL,"|", &temp));
    CdrMessage_SetDownload(newMessage,strtok_r(NULL,"|", &temp));
    CdrMessage_SetUpload(newMessage,strtok_r(NULL,"|", &temp));
    CdrMessage_SetComMsisdn(newMessage,strtok_r(NULL,"|", &temp));
	CdrMessage_SetComPartyMccmnc(newMessage,strtok_r(NULL,"|", &temp));

    CdrParserManager_sendCdrMessage(cdrParser->m_cdrManager,(void*)newMessage);

return;
}

