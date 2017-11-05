#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>       /* time_t, time, ctime */
#include "safeThreadQueue.h"
#include "datamanager.h"
#include "fileHandler.h"
#include "reporter.h"
#define REPORTFOLDER "../../report/"
#define SUBREPORTFILE "subReport.txt"
#define OPREPORTFILE "opReport.txt"

#define MAGICNUMBER 0xDEADBEAB
#define SLAPTIME 60
#define ALIVE 1
#define DEAD 0
#define EMPTYSUB 0000
#define EMPTYOP 00000
#define TIMESTAMPEBUFF 32


struct Reporter_t
{
    size_t m_magicNumber;
    STQueueu_t* m_uiToReporterQueue;
    DataManager_t* m_dataManager;
    pthread_t  m_thread;
    short int m_isAlive;
};

/***************internal function*******************************/

static void PrintReportToScrean(char* _str);
static void saveSubReportToFile(char* _str);
static void saveOpReportToFile(char* _str);
static void AddTimeStampSub(void);
static void AddTimeStampOp(void);
static void* ThreadFunc(void* _context);


/*****************************************************************/
Reporter_t*  Reporter_Creaty(STQueueu_t* _uiToReporterQueue, void* _dataManager)
{
    Reporter_t* newReporter;
    if(NULL == _uiToReporterQueue || NULL == _dataManager)
    {
        return NULL;
    }
    newReporter = calloc(1,sizeof(Reporter_t));
    if(NULL == newReporter)
    {
        return NULL;
    }
    newReporter->m_uiToReporterQueue = _uiToReporterQueue;
    newReporter->m_dataManager = (DataManager_t*)_dataManager;
    newReporter->m_isAlive = ALIVE;
    newReporter->m_magicNumber = MAGICNUMBER;

return newReporter;
}

/*******************************************************/
Reporter_Result  Reporter_Destroy(Reporter_t* _reporter)
{
    if(NULL == _reporter || MAGICNUMBER != _reporter->m_magicNumber)
    {
        return REPORTER_ERROR;
    }
    _reporter->m_isAlive = DEAD;
    pthread_cancel(_reporter->m_thread);
    pthread_join(_reporter->m_thread,NULL);
    _reporter->m_magicNumber = 0;
    free(_reporter);

return REPORTER_SUCCESS;
}

/****************************************************/
Reporter_Result Reporter_Run(Reporter_t* _reporter)
{

    if(NULL == _reporter || MAGICNUMBER != _reporter->m_magicNumber)
    {
        return REPORTER_ERROR;
    }
     pthread_create(&_reporter->m_thread,NULL,ThreadFunc,_reporter);

return REPORTER_SUCCESS;
}

/**************************************************/
static void* ThreadFunc(void* _context)
{
    int oldtype;
    ReportMessage* message;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
    Reporter_t* reporter = (Reporter_t*)_context;
    while(ALIVE == reporter->m_isAlive)
    {
        message = calloc(1,sizeof(ReportMessage));
        SafeTreadQueue_Dequeue(reporter->m_uiToReporterQueue,(void**)&message);
        switch(message->m_reportType)
        {
            case Reporter_Report_Type_OneSubScribe:
                    DataManager_CreatyReport(reporter->m_dataManager,ReportType_OneSubScribe,message->m_data,EMPTYOP,(DataMaager_ReportFuncition)PrintReportToScrean);
                    break;

            case Reporter_Report_Type_OneOperator:
                    DataManager_CreatyReport(reporter->m_dataManager,ReportType_OneSubScribe,EMPTYSUB,message->m_data,(DataMaager_ReportFuncition)PrintReportToScrean);
                    break;

            case Reporter_Report_Type_AllSubScribes:
                    AddTimeStampSub();
                    DataManager_CreatyReport(reporter->m_dataManager,ReportType_AllSubScribes,EMPTYSUB,EMPTYOP,(DataMaager_ReportFuncition)saveSubReportToFile);
                    sleep(SLAPTIME);
                    break;

            case Reporter_Report_Type_AllOperators:
                    AddTimeStampOp();
                    DataManager_CreatyReport(reporter->m_dataManager,ReportType_AllOperators,EMPTYSUB,EMPTYOP,(DataMaager_ReportFuncition)saveOpReportToFile);
                    sleep(10);
                    break;
        }
        free(message);
    }

return NULL;
}

/***************internal function*******************************/
static void PrintReportToScrean(char* _str)
{
    printf("%s",_str);

return;
}

/**********************************************/
static void saveSubReportToFile(char* _str)
{
    char  reportfilePath[] = REPORTFOLDER;
    char reportFile[] =SUBREPORTFILE;
    FileHandler_Write(reportfilePath,reportFile,_str);

return;
}

/**********************************************/
static void saveOpReportToFile(char* _str)
{
    char  reportfilePath[] = REPORTFOLDER;
    char reportFile[] =OPREPORTFILE;
    FileHandler_Write(reportfilePath,reportFile,_str);

return;
}

/**********************************************/
static void AddTimeStampSub(void)
{
    time_t rawtime;
    char  reportfilePath[] = REPORTFOLDER;
    char reportFile[] =SUBREPORTFILE;
    char buffer[TIMESTAMPEBUFF];

    time (&rawtime);
    sprintf(buffer,"%s",ctime(&rawtime));
    FileHandler_Write(reportfilePath,reportFile,buffer);

return;
}

/**********************************************/
static void AddTimeStampOp(void)
{
    time_t rawtime;
    char  reportfilePath[] = REPORTFOLDER;
    char reportFile[] =OPREPORTFILE;
    char buffer[TIMESTAMPEBUFF];

    time (&rawtime);
    sprintf(buffer,"%s",ctime(&rawtime));
    FileHandler_Write(reportfilePath,reportFile,buffer);

return;
}
