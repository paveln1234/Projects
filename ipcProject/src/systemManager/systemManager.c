#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "systemManger.h"
#include "safeThreadQueue.h"
#include "ui.h"
#include "reporter.h"
#include "datamanager.h"
#include "cdrParserManager.h"

#define MAGICNUMBER 0xDEADDEAD
#define FILELENG 256
#define BUFFER 255
#define SUBREPORTFILE "subReport.txt"
#define OPREPORTFILE "opReport.txt"
#define DEFULTCONFIG "../../config.txt"
#define ALIVE 1
#define DEAD 0
#define RUN 1
#define PAUSE 0

struct SystemManger_t
{
	size_t m_magicNumber;
	CdrParserManager_t* m_cdrParser;
	DataManager_t* m_dsManager;
	UiServer_t* m_uiManager;
	Reporter_t* m_reporter;
    STQueueu_t*  m_cdrToDataManager;
    STQueueu_t*  m_uiToReporter;
    STQueueu_t*  m_uiToSystemManager;
    char* m_inputFolder;
    char* m_inprogressFolder;
    char* m_outputFolder;
    char* m_reporterFolder;
    size_t m_NumOfThreds;
    short int m_isAlive;
    short int m_isPause;
};

/*****************intrenal function***************************/
static void* DestroythreadFunc(void* _ui);
static void* PausethreadFunc(void* _ui);
static void* ResumethreadFunc(void* _ui);
static void getData(char* _linr,char* _buffer);
static void InitSystem(FILE* fp,SystemManger_t* _manager);

SystemManger_t* SystemManager_Load(void)
{
    SystemManger_t* newManager;
    FILE* fp;
   int errnum;

    newManager = malloc(sizeof(SystemManger_t));
    if(NULL == newManager)
    {
        return NULL;
    }
    fp = fopen(DEFULTCONFIG,"r");

    if (fp == NULL)
    {
      errnum = errno;
      fprintf(stderr, "Value of errno: %d\n", errno);
      perror("Error printed by perror");
      fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
   }
    newManager->m_inprogressFolder = calloc(FILELENG,sizeof(char));
    if (NULL ==newManager->m_inprogressFolder)
    {
        free (newManager);
        return NULL;
    }

    newManager->m_inputFolder =calloc(FILELENG,sizeof(char));
    if(NULL == newManager->m_inputFolder)
    {
        free(newManager->m_inprogressFolder);
        free (newManager);
        return NULL;
    }
    newManager->m_outputFolder = calloc(FILELENG,sizeof(char));
    if(NULL == newManager->m_outputFolder )
    {
        free(newManager->m_inputFolder);
        free(newManager->m_inprogressFolder);
        free (newManager);
        return NULL;
    }

    newManager->m_reporterFolder = calloc(FILELENG,sizeof(char));
    if(NULL == newManager->m_reporterFolder)
    {
        free(newManager->m_outputFolder);
        free(newManager->m_inputFolder);
        free(newManager->m_inprogressFolder);
        free (newManager);
        return NULL;
    }
    InitSystem(fp,newManager);
    fclose(fp);
    newManager->m_isPause = PAUSE;
    newManager->m_isAlive = ALIVE;
    newManager->m_magicNumber = MAGICNUMBER;

return newManager;
}

SystemManager_Result SystemManager_Run(SystemManger_t* _sysManager)
{
    pthread_t thread;
    ReportMessage* newMessage;
    if(NULL ==_sysManager || MAGICNUMBER != _sysManager->m_magicNumber)
    {
        return SYSTEM_MANAGER_GENERAL_ERROR;
    }
    printf("menager start");
    CdrParserManager_Run(_sysManager->m_cdrParser);
    DataManager_Run(_sysManager->m_dsManager);
    Ui_Run(_sysManager->m_uiManager);
    Reporter_Run(_sysManager->m_reporter);

    while(ALIVE == _sysManager->m_isAlive)
    {

        SafeTreadQueue_Dequeue(_sysManager->m_uiToSystemManager,(void**)&newMessage);
        if(newMessage->m_data == 5 )
        {
            pthread_create(&thread,NULL,PausethreadFunc,(void*)_sysManager);
            pthread_join(thread,NULL);
        }
        else if(newMessage->m_data == 6)
        {
            pthread_create(&thread,NULL,ResumethreadFunc,(void*)_sysManager);
            pthread_join(thread,NULL);
        }
        else if(newMessage->m_data == 7)
        {
            pthread_create(&thread,NULL,DestroythreadFunc,(void*)_sysManager);
            pthread_join(thread,NULL);
            return SYSTEM_MANAGER_SUCCESS;
        }

    }

return SYSTEM_MANAGER_SUCCESS;
}

/*******************************************/
static void* DestroythreadFunc(void* _sysManager)
{
    int oldtype;
   SystemManger_t* sysManager = (SystemManger_t*)_sysManager;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
    Reporter_Destroy(sysManager->m_reporter);
    Ui_Destroy(sysManager->m_uiManager);
    CdrParserManager_Destroy(sysManager->m_cdrParser);
    DataManager_Destroy(sysManager->m_dsManager);

return NULL;
}

/*******************************************/
static void* PausethreadFunc(void* _sysManager)
{
    int oldtype;
   SystemManger_t* sysManager = (SystemManger_t*)_sysManager;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);

    CdrParserManager_Pause(sysManager->m_cdrParser);
    DataManager_Pause(sysManager->m_dsManager);

return NULL;
}

/*******************************************/
static void* ResumethreadFunc(void* _sysManager)
{
    int oldtype;
    SystemManger_t* sysManager = (SystemManger_t*)_sysManager;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);

    CdrParserManager_Resume(sysManager->m_cdrParser);
    DataManager_Resume(sysManager->m_dsManager);

return NULL;
}


static void InitSystem(FILE* fp,SystemManger_t* _manager)
{

	char line[FILELENG];
    char data[FILELENG];
    size_t number_of_subsreibers;
    size_t number_of_operators;
    size_t opretor_defult_mmcmnc;
    size_t threads_parser;
    size_t thread_datamanger;
    size_t thread_subs = 0;
    size_t thread_op = 0;
    size_t Queue_size_cdrToDatamanager;
    size_t Queue_size_uiToReporter;
    size_t Queue_size_uiToSystemManager;
    int errnum = 0;
    
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
    getData(line, _manager->m_inputFolder);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    getData(line, _manager->m_inprogressFolder);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    getData(line, _manager->m_outputFolder);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    getData(line, _manager->m_reporterFolder);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    getData(line, data);
    number_of_subsreibers = atol(data);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    memset(data,'\n',FILELENG);
    getData(line, data);
    number_of_operators = atoi(data);
     if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    memset(data,'\n',FILELENG);
    getData(line, data);
    opretor_defult_mmcmnc = atoi(data);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    memset(data,'\n',FILELENG);
    getData(line, data);
    threads_parser = atoi(data);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    memset(data,'\n',FILELENG);
    getData(line, data);
    thread_datamanger = atoi(data);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    memset(data,'\n',FILELENG);
    getData(line, data);
    thread_subs = atoi(data);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    getData(line, data);
    thread_op = atoi(data);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    memset(data,'\n',FILELENG);
    getData(line, data);
    Queue_size_cdrToDatamanager = atoi(data);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    memset(data,'\n',FILELENG);
    getData(line, data);
    Queue_size_uiToReporter = atoi(data);
    if(NULL == fgets(line,BUFFER,fp))
    {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }
        
    memset(data,'\n',FILELENG);
    getData(line, data);
    Queue_size_uiToSystemManager = atoi(data);

    _manager->m_uiToSystemManager = SafeThreadQueue_Create(Queue_size_uiToSystemManager);
    _manager->m_cdrToDataManager = SafeThreadQueue_Create(Queue_size_cdrToDatamanager);
    _manager->m_uiToReporter = SafeThreadQueue_Create(Queue_size_uiToReporter);

    _manager->m_cdrParser = CdrParserManager_Creaty(_manager->m_cdrToDataManager,_manager->m_inputFolder,_manager->m_inprogressFolder,_manager->m_outputFolder,threads_parser);

    _manager->m_dsManager = DataManager_Creaty(_manager->m_cdrToDataManager,opretor_defult_mmcmnc,thread_datamanger,number_of_operators ,number_of_subsreibers);

    _manager->m_uiManager = Ui_Creaty(_manager->m_uiToSystemManager,_manager->m_uiToReporter);
    _manager->m_reporter = Reporter_Creaty(_manager->m_uiToReporter,_manager->m_dsManager);
    _manager->m_NumOfThreds = 0;
    _manager->m_NumOfThreds += threads_parser;
    _manager->m_NumOfThreds += thread_datamanger;
    thread_subs += thread_op;
return;
}

static void getData(char* line, char* input_folder)
{
	while('=' != *line)
	{
		++line;
	}

    ++line;
    while(' ' == *line )
    {
        ++line;
    }

    while('\0' != *line && ' ' != *line  &&  '\n' != *line)
    {
        *input_folder = *line;
        ++line;
        ++input_folder;
    }
return;
}
