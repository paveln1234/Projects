#ifndef _INITIALIZER_H_
#define _INITIALIZER_H_

/**
 *  @file initializator.h
 *  @brief initializator is part of "System manager" module.
 *
 *  @details  initializator is apart of a manager module, the instalizator respons to create and init all
 *						modules.
 *
 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

/* Defines the ENUM for Initializer_Result */
typedef enum Initializer_Result
{
        INITIALIZER_SUCCESS ,
        INITIALIZER_ALLOCATION_ERROR ,
        INITIALIZER_PARSER_ERROR_CREATY, /* problem white cdr ParserManager */
        INITIALIZER_REPORT_ERROR_CREATY, /* error whit report create*/
        INITIALIZER_UI_ERROR_CREATY , /* /ui create  error */
        INITIALIZER_DATAMANAGER_ERROR_CREATY /*undefinded error*/
}Initializer_Result;

/**
 * @brief The function create and init All "Cdr To Cfg" modules.
 * @param[in] char* _folder - configuration init folder
 * @param[in] char* _fileName - configuration init file name
 * @param[in] SystemManger_t* _sysManager - SystemManager_t struct that create whit SystemManager_load() func.
 * @return Initializer_Result.
 */

 Initializer_Result initializator_Init(char* _folder, char* _fileName, SystemManger_t* _sysManager);

 /*static parser init file*/
#endif /* _INITIALIZER_H_*/
