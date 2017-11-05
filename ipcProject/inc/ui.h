#ifndef _UI_H_
#define _UI_H_
#define FIFO "../clientToServerFifo" /*fifo pipe between client server */
/**
 *  @file ui.h
 *  @brief UI is User Interface module for i/o request from the system.
 *
 *  @details  The UI module is an i/o interface between user and the "cdr To cfg" system.
 *            the UI module allowing to user to pause and return the system and require reports from the system.
 *
 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */


/*Define Data structure UiServer_t*/
typedef struct UiServer_t UiServer_t;


/*Define Enum UiManager_Result */
typedef enum UiManager_Result
{
    UI_MANAGER_SUCCESS,
    UI_MANAGER_ERRROR,
    UI_MANAGER_UNINITIALIZED_ERROR
}UiManager_Result;

/*Define Enum ReportType */
typedef enum UiMessage
{
    UiMessage_OneSubSribel =1, /*print on screen*/
    UiMessage_OneOperator=2, /*print on screen*/
    UiMessage_AllSubSribel=3,/*print to out put file*/
    UiMessage_AllOperators =4, /*print to out put file*/
    UiMessage_Pause =5, /* Pause the system*/
    UiMessage_Resume = 6, /* Pause the system*/
    UiMessage_Shutdown = 7 /* Shutdown the system*/
}UiMessage;

/*Define Data structure UiMessage_t*/
typedef struct UiMessage_t UiMessage_t;

/**
 * @brief The function create and init Ui.
 * @param[in] STQueueu_t* _managerFromUiQueue - safe thread queue for send messages to the System Manager.
 * @param[in] STQueueu_t* _uiToReporterQueue - safe thread queue to Send messages To the Reporter.
 * @return in success UiServer_t* in fail NULL.
 */
UiServer_t* Ui_Creaty(void* _managerFromUiQueue,void* _uiToReporterQueue);

/**
 * @brief The function destroy UiServer_t
 * @param[in] UiServer_t* _ui - UI Manager to destroy.
 * @return UiManager_Result.
 */
UiManager_Result Ui_Destroy(UiServer_t* _ui);

/**
 * @brief The function run UI Manager
 * @param[in] UiServer_t* _ui - UiServer_t* to run.
 * @return UiManager_Result.
 * @warning Without proper authorization, it is not possible to perform work on the system and error UI_MANAGER_UNAUTHRIZED_ACCESS return.
 */
UiManager_Result Ui_Run(UiServer_t* _ui);
#endif /* _UI_H_*/
