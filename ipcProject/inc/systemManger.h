#ifndef _SYSTEMMANGER_H_
#define _SYSTEMMANGER_H_

/**
 *  @file systemManager.h
 *  @brief System manager is part of module is manager module for the "cdr to cfg" modules.
 *
 *  @details  System Manager is manager module for the all other modules in the "cdr to cfg" module
 *						the system manager allows to the user load, shutdown, pause and resume to the system at
 * 						any time.
 *						System Manager donfig file - the config file place in "./config/CdtToCfgConfig.ini"
 *						the System Manager have Error Handle abelate to prevent collaps of the system.
 *						the system manager provide log files for all modules (the log config defiended by
 *						"./logger/log.config").
 *
 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

 /*Define Data structure SystemManger_t */
typedef struct SystemManger_t SystemManger_t;



/* Defines the ENUM for SystemManager_Result */
typedef enum SystemManager_Result
{
            SYSTEM_MANAGER_SUCCESS = 0,
            SYSTEM_MANAGER_CDR_PARSE_ERROR = -1, /* problem white cdr file - the file will remove to ERROR folder*/
            SYSTEM_MANAGER_REPORT_CREATE_ERROR = -2, /* error whit report create*/
            SYSTEM_MANAGER_ALLOCATION_ERROR = -3, /* allocation error */
            SYSTEM_MANAGER_GENERAL_ERROR = -6 /*undefinded error*/
}SystemManager_Result;


/**
 * @brief The function load, init and run all the "Cdr To Cfg" modules.

 * @return in success SystemManger_t*  in fail return NULL.
 */
SystemManger_t* SystemManager_Load(void);

/**
 * @brief The function make safe Shutdown to the "Cdr To Cfg" modules,
 *        at the end of the proses of the shutdow the results that holds at the
 *				system will saved at the defult output folder.
 * @param[in] SystemManger_t* _sysManager - SystemManager_t struct that create whit SystemManager_load() func.
 * @return SystemManager_Result.
 */
SystemManager_Result SystemManager_ShutDown(SystemManger_t* _sysManager);

/**
 * @brief The function make safe Run to the "Cdr To Cfg" modules,
 *				proses that make convert of cdr To cfg will finish the convert before got pause.
 * @param[in] SystemManger_t* _sysManager - SystemManager_t struct that create whit SystemManager_load() func.
 * @return SystemManager_Result.
 */

SystemManager_Result SystemManager_Run(SystemManger_t* _sysManager);

/**
 * @brief The function make safe pause to the "Cdr To Cfg" modules,
 *				proses that make convert of cdr To cfg will finish the convert before got pause.
 * @param[in] SystemManger_t* _sysManager - SystemManager_t struct that create whit SystemManager_load() func.
 * @return SystemManager_Result.
 */
SystemManager_Result SystemManager_Pause(SystemManger_t* _sysManager);


/**
 * @brief The function make resume to the "Cdr To Cfg" modules,
 * @param[in] SystemManger_t* _sysManager - SystemManager_t struct that create whit SystemManager_load() func.
 * @return SystemManager_Result.
 */
SystemManager_Result SystemManager_Resume(SystemManger_t* _sysManager);



#endif /*_SYSTEMMANGER_H_*/
