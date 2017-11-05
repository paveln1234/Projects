#ifndef _CDRPARSER_H_
#define _CDRPARSER_H_
/**
 *  @file cdrParser.h
 *  @brief Cdr Parser  is part of "cdr parser Manager" module, this module is charge to parser cdr files and send the result to Data Manager.
 *
 *  @details  The Cdr Parser  module is charge to parse a given cdr file and send the answer to Data Manager.
 *            The parser cane parser in any time at must files as thread number defended by the user.
 *            The Cdr Parser get file name From "cdr parser Manager" and send the messages to data manager, after thparser finishes parser file the file moved  *              to output folder.
 *  @warning The parser create Ds message the responsibility  to free the message is on the getter module / user.
 *
 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

 /*Define structure CdrParser_t*/
typedef struct CdrParser_t CdrParser_t;

/*Define Enum CdrParser_Result */
typedef enum CdrParser_Result
{
    CDR_PARSER_SUCCESS,
    CDR_PARSER_UNINITIALIZED_ERROR,
    CDR_PARSER_BAD_FILE_ERROR
}CdrParser_Result;


/**
 * @brief The function create and init Cdr Parser.
 * @param[in] void* _cdrParserManager - pointer to cdr Parser.
 * @param[in] char* _inprogressFolder - path to inprogress folder to take cdr for parser.
 * @param[in] char* _outPutFolder - path to output folder to move in her files that the parser finishes parse.
 * @param[in] size_t _threadNumber - max number of thread that cane parse cdr file at once.
 * @return in success CdrParserManager_t* in fail NULL.
 */
CdrParser_t* CdrParser_Creaty(void* _cdrParserManager, char* _inprogressFolder, char* _outPutFolder ,size_t _threadNumber);

/**
 * @brief The function destroy CdrParser_t
 * @param[in] CdrParser_t* _cdrParser - Cdr Parser  to destroy.
 * @return CdrParser_Result.
 */
CdrParser_Result CdrParser_Destroy(CdrParser_t* _cdrParser);

/**
 * @brief The function run Cdr Parser
 * @param[in] CdrParser_t* _cdrParser - Cdr Parser  to run.
 * @return CdrParser_Result.
 */
CdrParser_Result CdrParser_Run(CdrParser_t* _cdrParser);

/**
 * @brief The function Pause Cdr Parser Manager  The module will finish current proses and then switch Cdr Parser to Pause mode.
 * @param[in] CdrParser_t* _cdrParser - Cdr Parser  to Pause.
 * @return CdrParser_Result.
 */
CdrParser_Result CdrParser_Pause(CdrParser_t* _cdrParser);

/**
 * @brief The function Resume Cdr Parser - The module  switch Cdr Parser to run mode.
 * @param[in] CdrParser_t* _cdrParser - Cdr Parser  to Resume.
 * @return CdrParser_Result.
 */
CdrParser_Result CdrParser_Resume(CdrParser_t* _cdrParser);

#endif /* _CDRPARSER_H_*/
