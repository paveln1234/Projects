#ifndef  _POSIX_C_SOURCE
#define  _POSIX_C_SOURCE 199309L
#endif

#ifndef __ZLOGMANAGER_H__
#define __ZLOGMANAGER_H__
#include <stddef.h>  /* size_t */
#include "logger.h"
/**
 *  @file zlogMannager.h
 *  @brief Log manager events in application .
 *
 *  @details   the log mannager is write events to log file .
 *
 *  @author pavel Korolin (paveln1234@gmail.com);
 *	@date 28 mart 2017
 *
 *  @bug No known bugs.
 */


 /**
 * @brief Create a new log manager from configuration file.
 * @param[in] __configFileName = configuration file name.
 * @return void.
 * @warning if no file was given the out put will write to zlogger.log file in the application folder white LOG_ERROR level.
 * @warning allaction error at logger create will not announce.
*/

void ZlogInit(char* _configFileName);


 /**
 * @brief close the manager and all open files.
 * @param void
 * @return void.
*/
void ZlogClose();


/**
 * @brief resive Logger whit the require name if not found return default
 * @param[in] __moduleName = the application name as named in the configuration file.
 * @return logger if success.
 * @warning if given an wrong name will return a default logger .
 * @warning allaction error at logger create will not announce.
*/
Logger* ZlogGet(char* _moduleName);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"


#define ZLOG(LOG, LEVEL, FORMAT, ...) \
    LoggerWrite((LOG),(LEVEL),  __extension__ __FUNCTION__,__FILE__,__LINE__ ,(FORMAT),__VA_ARGS__)

#pragma GCC diagnostic pop


#endif /* __ZLOGMANAGER_H__ */
