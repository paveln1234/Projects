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
#define SLAPTIME 360
#define LOGPATHE "../../logconfig.txt"

void saveSubReportToFile(char* _str)
{
    char  reportfilePath[] = REPORTFOLDER;
    char reportFile[] =SUBREPORTFILE;
    FileHandler_Write(reportfilePath,reportFile,_str);

return;
}

void saveOpReportToFile(char* _str)
{
    char  reportfilePath[] = REPORTFOLDER;
    char reportFile[] =SUBREPORTFILE;
    FileHandler_Write(reportfilePath,reportFile,_str);

return;
}

void Make_reoprt(DataManager_t* manager)
{

    DataManager_CreatyReport(manager,ReportType_AllSubScribes,000,00000,(DataMaager_ReportFuncition)saveSubReportToFile);
    /*DataManager_CreatyReport(manager,ReportType_AllSubScribes,000,00000,(DataMaager_ReportFuncition)saveOpReportToFile);*/

    sleep(SLAPTIME);

return;
}

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
    sleep(SLAPTIME);

return NULL;
}


UNIT(CreatyANDdestroy)
    char  inputfilePath[] =  INPUTFOLDER;
    char  inprogressfilePath[] = INPROGRESSFOLDER;
    char  donefilePath[]     = DONEFOLDER;
    size_t subThreads = THREAD_SUBS;
    size_t opThreads = THREAD_OP;
    size_t mmcMnc = DEFULT_MMCMNC;
    DataManager_t* DataManager;
    CdrParserManager_t* CdrManager;
    STQueueu_t* sQueue;

    sQueue= SafeThreadQueue_Create(SQUEUE_SIZE);
    ASSERT_THAT( NULL!= sQueue);

    CdrManager = CdrParserManager_Creaty(sQueue,inputfilePath,inprogressfilePath,donefilePath,subThreads);
    ASSERT_THAT( NULL!= CdrManager);
    DataManager = DataManager_Creaty(sQueue,mmcMnc,opThreads,OPARATORS,SUBSRIBERS);
    ASSERT_THAT( NULL!= DataManager);

    ASSERT_THAT( CDR_MANAGER_SUCCESS ==CdrParserManager_Destroy(CdrManager));
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
    STQueueu_t* sQueue;
    pthread_t  DataThread;
    pthread_t  SubThread;

    sQueue= SafeThreadQueue_Create(SQUEUE_SIZE);
    ASSERT_THAT( NULL!= sQueue);

    CdrManager = CdrParserManager_Creaty(sQueue,inputfilePath,inprogressfilePath,donefilePath,subThreads);
    ASSERT_THAT( NULL!= CdrManager);
    DataManager = DataManager_Creaty(sQueue,mmcMnc,opThreads,OPARATORS,SUBSRIBERS);

    ASSERT_THAT( NULL!= DataManager);

    pthread_create(&SubThread,NULL,ThreadFuncDataManager,(void*)DataManager);
    pthread_create(&DataThread,NULL,ThreadFuncSubScribeManager,(void*)CdrManager);
    pthread_join(SubThread,NULL);
    pthread_join(DataThread,NULL);
    Make_reoprt(DataManager);

    ASSERT_THAT( CDR_MANAGER_SUCCESS ==CdrParserManager_Destroy(CdrManager));
    ASSERT_THAT( DATA_MANAGER_SUCCESS ==DataManager_Destroy(DataManager));

    SafeTreadQueue_Destroy(sQueue,NULL);
END_UNIT
/*********************************************************/

TEST_SUITE(Cdr_TO_Datamanager)
    TEST(CreatyANDdestroy)
    TEST(Run)

END_SUITE
