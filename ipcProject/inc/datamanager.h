#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_
#include "safeThreadQueue.h" /*for STqueue in creaty*/
/**
 *  @file datamanager.h
 *  @brief Data Manager module are charge to manage input data from Cdr Parser for subscribe and operators.
 *
 *  @details  Data Manager module are charge to manage input data from Cdr Parser for subscribe and operators.

 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

 /*Define report function*/
typedef void(*DataMaager_ReportFuncition)(char* _buffer);

/*Define structure DataManager_t */
typedef struct DataManager_t DataManager_t;

/*Define Enum DataManager_Result */
typedef enum DataManager_Result
{
    DATA_MANAGER_SUCCESS,
    DATA_MANAGER_UNINITIALIZED_ERROR,
    DATA_MANAGER_ERRROR
}DataManager_Result;

/*Define Enum ReportType */
typedef enum ReportType
{
    ReportType_OneSubScribe, /*print on screen*/
    ReportType_OneOperator, /*print on screen*/
    ReportType_AllSubScribes,/*print to out put file*/
    ReportType_AllOperators /*print to out put file*/
}ReportType;


/**
 * @brief The function create and init Data Manager.
 * @param[in] STQueueu_t* _cdrToDataManagerQueue - safe thread queue to receive messages from the cdr Parser.
 * @param[in] size_t _mmcMnc - operator MMCMNC.
 * @param[in] size_t _numberOfThread - number of thread that will run .
 * @param[in] size_t _numOfOP - number of  Operators
 * @param[in] size_t _numOfSub - number of Subsribers.
 * @return in success DataManager_t* in fail NULL.
 */
DataManager_t* DataManager_Creaty(STQueueu_t* _cdrToDataManagerQueue,size_t _mmcMnc, size_t _numberOfthread,size_t _numOfOP,size_t _numOfSub);

/**
 * @brief The function Destroy data Manager
 * @param[in] DataManager_t* _dataManager - Data Manager to Destroy.
 * @return DataManager_Result
 */
DataManager_Result DataManager_Destroy(DataManager_t* _dataManager);


/**
 * @brief The function run Data Manager
 * @param[in] DataManager_t* _dataManager - Data Manager to run.
 * @return DataManager_Result.
 */
DataManager_Result DataManager_Run(DataManager_t* _dataManager);

/**
 * @brief The function Pause Data Manager Manager  The module will finish current proses and then switch Data Manager to Pause mode.
 * @param[in] DataManager_t* _dataManager - Data Manager to Pause.
 * @return DataManager_Result.
 */
DataManager_Result DataManager_Pause(DataManager_t* _dataManager);

/**
 * @brief The function Resume Data Manager - The module  switch Data Manager to run mode.
 * @param[in] DataManager_t* _dataManager - Data Manager  to Resume.
 * @return DataManager_Result.
 */
DataManager_Result DataManager_Resume(DataManager_t* _dataManager);

/**
 * @brief The function create Report as request - user Must to provide SubNumber or opMmcMnc whit the Report.
 * @param[in] ReportType _reportType - require report type.
 * @param[in] size_t _subNumber - SubScriber to print on screan.
 * @param[in] size_t _opMmcMnc - Operator MMCMNC
 * @param[in] char* _filename - File name to save the Ds.
 * @param[in] DataMaager_ReportFuncition _action - action function
 * @return DataManager_Result.
 */
DataManager_Result DataManager_CreatyReport(DataManager_t* _dataManager, ReportType _reportType,size_t _subMsinsNumber, size_t _opMmcMnc, DataMaager_ReportFuncition _action);

#endif /* _DATAMANAGER_H_*/
