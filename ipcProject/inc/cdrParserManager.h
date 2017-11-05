#ifndef _CDRPARSERMANAGER_H_
#define _CDRPARSERMANAGER_H_

#include "safeThreadQueue.h"
#define INTERVAL 10 /*define the time in second for discoverer wait between search for new files*/
/**
 *  @file cdrParserManager.h
 *  @brief Cdr Parser Manager is part of "cdr To cfg" module, this module is charge to find cdr files in user directory and
 *          parser them.
 *
 *  @details  The Cdr Parser Manager module is charge to discover cdr files in user Input folder (as defended in config file) parser them and send them
 *            to the Data Manager module, after the parser finish to parser the file hi move the file to user Done directory (as defended in config file)
 *            The parser cane parser in any time at must files as thread number defended by the user  (at defended in config file).
 *            The Cdr Parser Manager get file name From discoverer and send the messages to data manager.
 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */


/*Define Data structure CdrParserManager_t*/
typedef struct CdrParserManager_t CdrParserManager_t;

/*Define Enum CdrParserManager_Result */
typedef enum CdrParserManager_Result
{
    CDR_MANAGER_SUCCESS,
    CDR_MANAGER_UNINITIALIZED_ERROR,
    CDR_MANAGER_PAUSE_ERROR,
    CDR_MANAGER_RUN_ERRROR
}CdrParserManager_Result;


/**
 * @brief The function create and init CdrParserManager.
 * @param[in] STQueueu_t* _cdrToDataManagerQueue - safe thread queue for send parsed messages to data manager.
 * @param[in] char* _inputFolderPath - path to input folder for search  cdr files.
 * @param[in] char* _inprogressFolderPath - path to inprogress folder will insert cdr that are parsing.
 * @param[in] char* _doneFolderPath - path to done folder  where will insert cdr that  finish parsing.
 * @param[in] size_t _threadNumber - number of thread that cane parse cdr file at once.
 * @return in success CdrParserManager_t* in fail NULL.
 */
CdrParserManager_t* CdrParserManager_Creaty(STQueueu_t* _cdrToDataManagerQueue,
                                            char* _inputFolderPath,char* _inprogressFolderPath,char* _doneFolderPath, size_t _threadNumber);

/**
 * @brief The function destroy CdrParserManager_t
 * @param[in] CdrParserManager_t* _cdrParserManager - Cdr Parser Manager to destroy.
 * @return CdrParserManager_Result.
 */
CdrParserManager_Result CdrParserManager_Destroy(CdrParserManager_t* _cdrParserManager);

/**
 * @brief The function run Cdr Parser Manager
 * @param[in] CdrParserManager_t* _cdrParserManager - CdrParserManager_t* to run.
 * @return CdrParserManager_Result.
 */
CdrParserManager_Result CdrParserManager_Run(CdrParserManager_t* _cdrParserManager);

/**
 * @brief The function Pause Cdr Parser Manager  The module will finish current proses and then switch Cdr Parser Manager to Pause mode.
 * @param[in] CdrParserManager_t* _cdrParserManager - CdrParserManager_t* to Pause.
 * @return CdrParserManager_Result.
 */
CdrParserManager_Result CdrParserManager_Pause(CdrParserManager_t* _cdrParserManager);


/**
 * @brief The function Pause Cdr Parser Manager The module will switch Cdr Parser Manager to run mode.
 * @param[in] CdrParserManager_t* _cdrParserManager - CdrParserManager_t* to Resume.
 * @return CdrParserManager_Result.
 */
CdrParserManager_Result CdrParserManager_Resume(CdrParserManager_t* _cdrParserManager);


/**
 * @brief The function put Cdr file name to parse in to queue for the cdr parser.
 * @param[in] void* _cdrParserManager - CdrParserManager_t*.
 * @param[in] char* _filename - file Name to insert.
 * @return CdrParserManager_Result.
 */
CdrParserManager_Result CdrParserManager_PutCdrFileName(void* _cdrParserManager,char* _fileNameToInsert);


/**
 * @brief The function put Cdr file name to parse in to queue for the cdr parser.
 * @param[in] void* _cdrParserManager - CdrParserManager_t* .
 * @param[in] void*** _buffer - buffer to return file Name.
 * @return CdrParserManager_Result.
 */
CdrParserManager_Result CdrParserManager_GetCdrFileName(void* _cdrParserManager,void** _buffer);

/**
 * @brief The function put Cdr file name to Queue for the data struct manager
 * @param[in] void* _cdrParserManager - CdrParserManager_t* .
 * @param[in] void* _message - message
 * @return CdrParserManager_Result.
 */

CdrParserManager_Result CdrParserManager_sendCdrMessage(void* _cdrParserManager,void* _message);

#endif /* _CDRPARSERMANAGER_H_ */
