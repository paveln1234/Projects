#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "zlogManager.h"

/**
 *  @file config.h
 *  @brief the function pharse a given file and provide function to extract the data from it
 *
 *  @details Implemented pharser that extruct the data from agiven file and provied function to get the information for later use.
 *
 *  @author Pavel korolin 
 *
 *  @bug No known bugs.
 */


typedef struct ConfigData
{
    void* m_data;
    FILE* m_configFile;
}ConfigData;


/**
**@brif - the function open configuration file and read the date from it, the function make struct of data Long that return to the user;
*@param [-in] _configFileName - name of configuration file in the api format
*@return it will return an configData that point to array of data struct Log if SUCCESS
*       or NULL if _configFileName are null.
*/
void* Config_Read(const char* _configFileName);

/**
*@brif - the function close open configuration file and destoy all internel membares;
*@param [-in] _configFileName - name of configuration file in the api format
*@return void
*
*/
void Config_Close(ConfigData** _data);

/**
*@brif - the function return the path of DataStruct
*@param [-in] void* _data - pointer of DataStruct
*@return char* - path if success or NULL if empty or faild
*
*/
char* Config_GetPath(void* _data);

/**
*@brif - the function return the moudele name of DataStruct
*@param [-in] void* _data - pointer of DataStruct
*@return char* - mouduele name if success or NULL if empty or faild
*/
char* Config_GetMoudeleName(void* _data);


/**
*@brif - the function return the  file name of DataStruct
*@param [-in] void* _data - pointer of DataStruct
*@return char* -file name  name if success or NULL if empty or faild
*/
char* Config_GetFileName(void* _data);

/**
*@brif - the function return the  LogLevel  of DataStruct
*@param [-in] void* _data - pointer of DataStruct
*@return LogLevel
*@warning - in error no warning will gives in return
*/
LogLevel Config_GetLogLevel(void* _data);


/**
*@brif - the function check if there have elements in the datastruct
*@param [-in] void* _data - pointer of configData
*@return number of items
*/
int Config_IsEmptey(void*_data);
int Config_GetNextItem(void* _data);


#endif /* __CONFIG_H__ */

