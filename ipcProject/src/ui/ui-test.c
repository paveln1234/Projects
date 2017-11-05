#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "mu_test.h"
#include "safeThreadQueue.h"
#include "ui.h"
#define NUMBEROFMESSAGE 4

/*****************************************/
UNIT(Creaty)
STQueueu_t* reporterToUiQueue;
STQueueu_t* uiToSystemManagerQueue;
UiServer_t* ui;

reporterToUiQueue = SafeThreadQueue_Create(NUMBEROFMESSAGE);
uiToSystemManagerQueue = SafeThreadQueue_Create(NUMBEROFMESSAGE);
ui= Ui_Creaty( reporterToUiQueue,uiToSystemManagerQueue);


ASSERT_THAT( NULL != ui);
ASSERT_THAT(UI_MANAGER_SUCCESS == Ui_Destroy(ui));
END_UNIT
/*********************************************************/

UNIT(Run)
STQueueu_t* reporterToUiQueue;
STQueueu_t* uiToSystemManagerQueue;
UiServer_t* ui;
int i;
uiToSystemManagerQueue = SafeThreadQueue_Create(NUMBEROFMESSAGE);
reporterToUiQueue = SafeThreadQueue_Create(NUMBEROFMESSAGE);

ui= Ui_Creaty( reporterToUiQueue,uiToSystemManagerQueue);
ASSERT_THAT( NULL != ui);
    Ui_Run(ui);
    printf("333\n");
    scanf("%d", &i);
ASSERT_THAT(UI_MANAGER_SUCCESS == Ui_Destroy(ui));
END_UNIT
/*********************************************************/

TEST_SUITE(ui_tests)
    TEST(Creaty)
    TEST(Run)
END_SUITE
