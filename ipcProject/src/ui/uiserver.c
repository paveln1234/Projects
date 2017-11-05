#define _BSD_SOURCE
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include "safeThreadQueue.h"
#include "ui.h"
#include "reporter.h"
#define MAGICNUMBER 0xDEADBEAF
#define ALIVE 1
#define DEAD 0

struct UiMessage_t
{
    size_t m_message;
    size_t m_number;
};
struct UiServer_t
{
    size_t m_magicNumber;
    short int isAlive;
    STQueueu_t* m_uiToSystemManager;
    STQueueu_t* m_uiToReporterQueue;
    pthread_t m_thread;
    pthread_t m_subSignal;
    pthread_t m_opSignal;
};
/************internal function*****************************/
void* threadFunc(void* _ui);
void* SubsListener(void* _sQueue);
void* OpersListener(void* _sQueue);

UiServer_t* Ui_Creaty(void* _managerFromUiQueue,void* _uiToReporterQueue)
{
    UiServer_t* newUi;

    if(NULL == _uiToReporterQueue || NULL ==  _managerFromUiQueue)
    {
        return NULL;
    }
    newUi = (UiServer_t*)malloc(sizeof(UiServer_t));
    if(NULL == newUi)
    {
        return NULL;
    }

    newUi->m_uiToSystemManager = (STQueueu_t*)_managerFromUiQueue;
    newUi->m_uiToReporterQueue = (STQueueu_t*)_uiToReporterQueue;
    mkfifo(FIFO,0666);
    newUi->isAlive = ALIVE;
    newUi->m_magicNumber = MAGICNUMBER;

return newUi;
}

UiManager_Result Ui_Destroy(UiServer_t* _ui)
{
    if(NULL == _ui || MAGICNUMBER != _ui->m_magicNumber)
    {
        return UI_MANAGER_UNINITIALIZED_ERROR;
    }
    _ui->isAlive = DEAD;
    printf("exit 1\n ");
    pthread_cancel(_ui->m_thread);
    pthread_join(_ui->m_thread,NULL);

    unlink(FIFO);

    free(_ui);
return UI_MANAGER_SUCCESS;
}


UiManager_Result Ui_Run(UiServer_t* _ui)
{

    if(NULL == _ui)
    {
        return UI_MANAGER_UNINITIALIZED_ERROR;
    }
    printf("Program start \n ");
    printf("The program is initialized\n ");
    printf(" wait to user input\n");
    pthread_create(&_ui->m_thread,NULL,threadFunc,(void*)_ui);
    /*pthread_create(&_ui->m_subSignal,NULL,SubsListener,(void*)_ui);
    pthread_create(&_ui->m_opSignal,NULL,OpersListener,(void*)_ui);
*/
return UI_MANAGER_SUCCESS;
}

/*******************************************/
void* threadFunc(void* _ui)
{
    UiServer_t* ui;
    int oldtype;
    char line[10];
    size_t number = 0 ;
    int serverPipe;
    int errnum = 0;
    ReportMessage* newMessage;
    ui = (UiServer_t*)_ui;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
    serverPipe = open(FIFO,O_RDONLY);
    while(ALIVE == ui->isAlive && 0<read(serverPipe,line,sizeof(size_t)))
    {
        number  =atol(line);
        printf("%ld\n",number);
        switch(number)
        {
            case 1:
                    newMessage =malloc(sizeof(ReportMessage));
                    newMessage->m_reportType =Reporter_Report_Type_OneSubScribe;
                    if(0 > read(serverPipe,line,sizeof(size_t)))
                    {
                         errnum = errno;
                         fprintf(stderr, "Value of errno: %d\n", errno);
                         perror("Error printed by perror");
                         fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));           
                         break;
                    }
                    newMessage->m_data = atol(line);
                    SafeTreadQueue_Enqueue(ui->m_uiToReporterQueue,(void*)newMessage);
                    break;
            case 2:
                    newMessage =malloc(sizeof(ReportMessage));
                    newMessage->m_reportType =Reporter_Report_Type_OneOperator;
                    if(0>read(serverPipe,line,sizeof(size_t)))
                    {
                         errnum = errno;
                         fprintf(stderr, "Value of errno: %d\n", errno);
                         perror("Error printed by perror");
                         fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));           
                         break;
                    }
                  
                    newMessage->m_data = atol(line);
                    SafeTreadQueue_Enqueue(ui->m_uiToReporterQueue,(void*)newMessage);
                    break;
            case 3:
                    newMessage =malloc(sizeof(ReportMessage));
                    newMessage->m_reportType =Reporter_Report_Type_AllSubScribes;
                    SafeTreadQueue_Enqueue(ui->m_uiToReporterQueue,(void*)newMessage);
                    break;
            case 4:

                    newMessage =malloc(sizeof(ReportMessage));
                    newMessage->m_reportType =Reporter_Report_Type_AllOperators;
                    SafeTreadQueue_Enqueue(ui->m_uiToReporterQueue,(void*)newMessage);
                    break;
            case 5:
                    newMessage =malloc(sizeof(ReportMessage));
                    newMessage->m_data = 5;
                    SafeTreadQueue_Enqueue(ui->m_uiToSystemManager,(void*)newMessage);
                    break;

            case 6:
                    newMessage =malloc(sizeof(ReportMessage));
                    newMessage->m_data = 6;
                    SafeTreadQueue_Enqueue(ui->m_uiToSystemManager,(void*)newMessage);
                    break;

            case 7:
                    newMessage =malloc(sizeof(ReportMessage));
                    newMessage->m_data = 7;
                    SafeTreadQueue_Enqueue(ui->m_uiToSystemManager,(void*)newMessage);
                    break;

        }
        fflush(stdin);
    }

    close(serverPipe);
return NULL;
}
/*******************************************/
void* SubsListener(void* _ui)
{
    UiServer_t* ui;
	int a;
	sigset_t set;
    ReportMessage* newMessage;

    ui = (UiServer_t*)_ui;
	sigemptyset(&set);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
	sigaddset(&set, SIGUSR1);
    newMessage =malloc(sizeof(ReportMessage));
	while(ALIVE == ui->isAlive)
	{
		sigwait(&set, &a);
        newMessage->m_reportType =Reporter_Report_Type_AllSubScribes;
        SafeTreadQueue_Enqueue(ui->m_uiToReporterQueue,(void*)newMessage);
	}

return NULL;
}

/*******************************************/
void* OpersListener(void* _ui)
{
    UiServer_t* ui;
	int a;
	sigset_t set;
    ReportMessage* newMessage;

    ui = (UiServer_t*)_ui;
	sigemptyset(&set);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    newMessage =malloc(sizeof(ReportMessage));
	sigaddset(&set, SIGUSR1);
	while(ALIVE == ui->isAlive)
	{
		sigwait(&set, &a);
        newMessage->m_reportType =Reporter_Report_Type_AllOperators;
        SafeTreadQueue_Enqueue(ui->m_uiToReporterQueue,(void*)newMessage);
	}

return NULL;
}
