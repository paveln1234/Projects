#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "mu_test.h"
#include "cdrMessager.h"
#include "cdrParserManager.h"
#include "safeThreadQueue.h"
#include "datamanager.h"
#include "fileHandler.h"
#include "reporter.h"
#define MAGICNUMBER 0xDEADDEAD
#define MAX 2000000
#define MIN 1000000
#define SUBSRIBERS 1000000
#define OPARATORS 6
#define DEFULT_MMCMNC 42422
#define THREAD_SUBS 2
#define THREAD_OP 2
#define INPUTFOLDER  "../../input/"
#define INPROGRESSFOLDER  "../../inprogress/"
#define DONEFOLDER "../../done/"
#define REPORTFOLDER "../../report/"
#define SUBREPORTFILE "subReport.txt"
#define OPREPORTFILE "opReport.txt"
#define SQUEUE_SIZE 400
#define UISQUWUE_SIZE 5
#define SLAPTIME 240

void* ThreadFuncDataManager(void* _context)
{

    DataManager_t* manager = (DataManager_t*)_context;
    DataManager_Run(manager);
    sleep(SLAPTIME);

return NULL;
}

void* ThreadFuncSubScribeManager(void* _context)
{
    CdrParserManager_t* manager = (CdrParserManager_t*)_context;
    CdrParserManager_Run(manager);

return NULL;
}

void* ThreadFuncReporter(void* _context)
{

    Reporter_t* reporter = (Reporter_t*)_context;
    Reporter_Run(reporter);
    sleep(SLAPTIME);
return NULL;
}


/***********************************************/
UNIT(CreatyANDdestroy)
    Reporter_t* reporter;
    STQueueu_t* sQueue;
    DataManager_t* DataManager;
    size_t opThreads = THREAD_OP;
    size_t mmcMnc = DEFULT_MMCMNC;

    sQueue= SafeThreadQueue_Create(UISQUWUE_SIZE);
    ASSERT_THAT( NULL!= sQueue);

    DataManager = DataManager_Creaty(sQueue,mmcMnc,opThreads,OPARATORS,SUBSRIBERS);
    ASSERT_THAT( NULL!= DataManager);

    reporter = Reporter_Creaty(sQueue,DataManager);
    ASSERT_THAT( NULL!= reporter);

    ASSERT_THAT( REPORTER_SUCCESS ==Reporter_Destroy(reporter));
    ASSERT_THAT( DATA_MANAGER_SUCCESS ==DataManager_Destroy(DataManager));

    SafeTreadQueue_Destroy(sQueue,NULL);
END_UNIT

/*****************************************/
UNIT(Run)
    char  inputfilePath[] =  INPUTFOLDER;
    char  inprogressfilePath[] = INPROGRESSFOLDER;
    char  donefilePath[] = DONEFOLDER;
    size_t subThreads = THREAD_SUBS;
    size_t opThreads = THREAD_OP;
    size_t mmcMnc = DEFULT_MMCMNC;
    DataManager_t* DataManager;
    CdrParserManager_t* CdrManager;
    Reporter_t* reporter;

    STQueueu_t* sQueue;
    STQueueu_t* sQueueToReporter;
    pthread_t  DataThread;
    pthread_t  SubThread;
    pthread_t  ReporterThread;
    ReportMessage* newReportMessage;

    sQueue= SafeThreadQueue_Create(SQUEUE_SIZE);
    ASSERT_THAT( NULL!= sQueue);

    sQueueToReporter= SafeThreadQueue_Create(UISQUWUE_SIZE);
    ASSERT_THAT( NULL!= sQueueToReporter);


    CdrManager = CdrParserManager_Creaty(sQueue,inputfilePath,inprogressfilePath,donefilePath,subThreads);
    ASSERT_THAT( NULL!= CdrManager);

    DataManager = DataManager_Creaty(sQueue,mmcMnc,opThreads,OPARATORS,SUBSRIBERS);
    ASSERT_THAT( NULL!= DataManager);

    reporter = Reporter_Creaty(sQueueToReporter,DataManager);
    ASSERT_THAT( NULL!= reporter);


    pthread_create(&SubThread,NULL,ThreadFuncDataManager,(void*)DataManager);
    pthread_create(&DataThread,NULL,ThreadFuncSubScribeManager,(void*)CdrManager);
    pthread_create(&ReporterThread,NULL,ThreadFuncReporter,(void*)reporter);

    pthread_join(SubThread,NULL);
    pthread_join(DataThread,NULL);
    pthread_join(ReporterThread,NULL);

    newReportMessage = calloc(1,sizeof(ReportMessage*));
    newReportMessage->m_reportType = Reporter_Report_Type_AllSubScribes;
    newReportMessage->m_data = 000000;

    SafeTreadQueue_Enqueue(sQueueToReporter,newReportMessage);
    newReportMessage = calloc(1,sizeof(ReportMessage*));
    newReportMessage->m_reportType = ReportType_AllOperators;
    newReportMessage->m_data = 000000;
    SafeTreadQueue_Enqueue(sQueueToReporter,newReportMessage);
    sleep(SLAPTIME);

    ASSERT_THAT( REPORTER_SUCCESS ==Reporter_Destroy(reporter));
    ASSERT_THAT( CDR_MANAGER_SUCCESS ==CdrParserManager_Destroy(CdrManager));
    ASSERT_THAT( DATA_MANAGER_SUCCESS ==DataManager_Destroy(DataManager));

    SafeTreadQueue_Destroy(sQueue,NULL);
END_UNIT
/***************************************************/
TEST_SUITE(Reporter_test)
    TEST(CreatyANDdestroy)
    TEST(Run)

END_SUITE
