#include <stdio.h>/*calloc*/
#include <stdlib.h>/*size_t*/
#include <string.h> /*strlen*/
#include <dirent.h> /*read folders*/
#include <pthread.h> /*for thread and mutex function*/
#include <unistd.h> /*sleep*/
#include "cdrParserManager.h"
#include "discoverer.h"
#include "fileHandler.h"
#define MAGICNUMBER 0xDEADBEAF
#define FILENAME_LENGHT 64
#define ALIVE 1
#define DEAD 0
#define RUN 1
#define PAUSE 0

/********static function***********/
static void* ThreadFunc(void* _context);

/*Define structure Discoverer_t */
struct Discoverer_t
{
    size_t m_magicNumber;
    void* m_cdrManager;
    char* m_inputFolderPath;
    char* m_inprogressFolderPath;
    pthread_t m_discovererThread;
    pthread_mutex_t m_pauseMutex;
    pthread_cond_t m_pauseCond;
    size_t m_intervalTime;
    short int m_isAlive;
    short int m_isPause;
};

/****************************************************/
Discoverer_t* Discoverer_Creaty(void* _cdrManager, char* _inputFolderPath, char* _inprogressFolderPath, size_t _intervalTime)
{
    Discoverer_t* newDiscoverer;
    if(NULL == _cdrManager || NULL == _inputFolderPath  || NULL == _inprogressFolderPath)
    {
        return NULL;
    }
    newDiscoverer = calloc(1,sizeof(Discoverer_t));
    if(NULL == newDiscoverer)
    {
        return NULL;
    }
    newDiscoverer->m_cdrManager = _cdrManager;
    if(pthread_mutex_init(&newDiscoverer->m_pauseMutex,NULL))
    {
        free(newDiscoverer);
        return NULL;
    }
    if(pthread_cond_init(&newDiscoverer->m_pauseCond,NULL))
    {
            pthread_mutex_destroy(&newDiscoverer->m_pauseMutex);
            free(newDiscoverer);
            return NULL;
    }

    newDiscoverer->m_inputFolderPath = _inputFolderPath;
    newDiscoverer->m_isAlive = ALIVE;
    newDiscoverer->m_isPause = PAUSE;
    newDiscoverer->m_intervalTime = _intervalTime;
    newDiscoverer->m_inprogressFolderPath = _inprogressFolderPath;
    newDiscoverer->m_magicNumber = MAGICNUMBER;
return newDiscoverer;
}
/****************************************************/
Discoverer_Result Discoverer_Destroy(Discoverer_t* _disoverer)
{
    if(NULL == _disoverer || MAGICNUMBER != _disoverer->m_magicNumber)
    {
        return DISCOVERER_UNINITIALIZED_ERROR;
    }
    _disoverer->m_isPause = RUN;
    _disoverer->m_isAlive = DEAD;
    pthread_cond_broadcast(&_disoverer->m_pauseCond);
    pthread_cancel(_disoverer->m_discovererThread);
    pthread_join(_disoverer->m_discovererThread,NULL);
    pthread_cond_destroy(&_disoverer->m_pauseCond);
    pthread_mutex_destroy(&_disoverer->m_pauseMutex);

    _disoverer->m_magicNumber = 0;
    free(_disoverer);

return DISCOVERER_SUCCESS;
}
/****************************************************/
Discoverer_Result Discoverer_Run(Discoverer_t* _disoverer)
{
    if(NULL == _disoverer || MAGICNUMBER != _disoverer->m_magicNumber)
    {
        return DISCOVERER_UNINITIALIZED_ERROR;
    }
    _disoverer->m_isPause = RUN;
    pthread_create(&_disoverer->m_discovererThread,NULL,ThreadFunc,_disoverer);
return DISCOVERER_SUCCESS;
}

/****************************************************/
Discoverer_Result Discoverer_Pause(Discoverer_t* _disoverer)
{
    if(NULL == _disoverer || MAGICNUMBER != _disoverer->m_magicNumber)
    {
        return DISCOVERER_UNINITIALIZED_ERROR;
    }

    pthread_mutex_lock(&_disoverer->m_pauseMutex);
        _disoverer->m_isPause = PAUSE;
    pthread_mutex_unlock(&_disoverer->m_pauseMutex);

return DISCOVERER_SUCCESS;
}

Discoverer_Result Discoverer_Resume(Discoverer_t* _disoverer)
{
    if(NULL == _disoverer || MAGICNUMBER != _disoverer->m_magicNumber)
    {
        return DISCOVERER_UNINITIALIZED_ERROR;
    }

    pthread_mutex_lock(&_disoverer->m_pauseMutex);
        _disoverer->m_isPause = RUN;
        pthread_mutex_unlock(&_disoverer->m_pauseMutex);
    pthread_cond_broadcast(&_disoverer->m_pauseCond);

return DISCOVERER_SUCCESS;
}

/********static function***********/
static void* ThreadFunc(void* _context)
{
    int oldtype;
    Discoverer_t* discoverer = (Discoverer_t*)_context;
    DIR *dir;
    char* fileName;
    struct dirent *ent;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);

    while (ALIVE == discoverer->m_isAlive)
    {
        pthread_mutex_lock(&discoverer->m_pauseMutex);
        while(PAUSE == discoverer->m_isPause)
        {
            pthread_cond_wait(&discoverer->m_pauseCond,&discoverer->m_pauseMutex);
        }
        if ((dir = opendir (discoverer->m_inputFolderPath)) != NULL)
        {
            while ((ent = readdir (dir)) != NULL)
            {
                if(2<strlen( ent->d_name))
                {
                    FileHandler_MoveFile(ent->d_name,discoverer->m_inputFolderPath,discoverer->m_inprogressFolderPath);
                    fileName = calloc(FILENAME_LENGHT,sizeof(char));
                    strcpy(fileName,ent->d_name); /*insert auto to dequeue*/
                    CdrParserManager_PutCdrFileName((void*)discoverer->m_cdrManager,fileName);
                }
            }
            closedir (dir);
            sleep(10);
        }
        pthread_mutex_unlock(&discoverer->m_pauseMutex);
        sleep(discoverer->m_intervalTime);
    }

return NULL;
}

