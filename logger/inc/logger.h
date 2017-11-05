#ifndef __LOGGER_H__
#define __LOGGER_H__
#include <stddef.h>  /* size_t */
#include <sys/types.h>
#include <unistd.h>
#include "logLevel.h"

/**
 *  @file logger.h
 *  @brief create loggers for logger and write to file in function call.
 *
 *  @details   logger  is write events to log file .
 *
 *  @author pavel Korolin (paveln1234@gmail.com);
 *	@date 28 mart 2017
 *
 *  @bug No known bugs.
 */



typedef struct Logger Logger;


/**
**@brif - the function create new Logger .
*@param [-in] const char* __moduleName - the name of the module .
*@param [-in] const char* fileName -file name that log will wright to it.
*@param [-in] LogLevel _level - level at LogLevel format (logLevel .h) .
*@return pointer to new logger.
*/

Logger* Logger_Create(const char* _moduleName,const char* _FileName, LogLevel _level);


/**
**@brif - the function destroy given Logger.
*@param [-in] void* log - pointer to logger
*@return void.
*/
void Logger_Destroy(void* _log);

/**
*@brife the function return logger file name
*@param [-in] void* log - pointer to logger
*@return file name as char*
 */
char* Loggger_GetFileName(Logger* _log);


/**
*@brife the function open file to wright
*@param [-in] void* log - pointer to logger
*@return void.
* @warning  - if the name of the file is in the logger is wrong the function doesn't check it.
 */
void Loggger_setFile(Logger* _log);


/**
*@brife the function return the module from a logger
*@param [-in] void* log - pointer to logger
*@return char* - module name.
 */
char* GetModuleName(Logger* _log);


/**
*@brife the function return the LogLevel from a logger.
*@param [-in] void* log - pointer to logger.
*@return LogLevel - log level in logLevel.h format.
 */
LogLevel GetLogLevel(Logger* _log);


/**
*@brife the function wright to file new line in the format
    "year, month ,day, time, proses id ,thread id ,log level, tag - moudle name, function name ,@,sourse file , line number , message"
    the function check the level given to the level in the moudle and ignore from all requst that smaller the Loglevel that set in  Logger
*@param [-in] void* log - pointer to logger.
*@param LogLevel - log level in logLevel.h format.
*@param char* _function - function name that request to wright.
*@param char* _file - the file that  request to wright.
*@param size_t _line - the line in the file that request to wright.
*@param const char* _format - the massege to wright.
*@return LogLevel - log level in logLevel.h format.
 */

void Logger_Write(Logger* _Log, LogLevel _level,char* _function, char* _file, size_t _line,const char* _format, ...);



#endif /* __LOGGER_H__ */


/************ logger struct *****************/



