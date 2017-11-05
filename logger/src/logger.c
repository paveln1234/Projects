#include <stdio.h>/*file ptr*/
#include <stdlib.h> /*calloc */
#include <sys/types.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


#include "macros.h"
#include "logger.h"
#include "config.h"
#define MAGICNUMBER 0xbeefbeef
#define REMOVMAGICNUMBER   0



static char levleToCahr(LogLevel _log);

struct Logger
{

	char* m_moduleName;
	char* m_fileName;
	LogLevel m_level;
	FILE* m_filePtr;
	size_t m_magicNumber;

};


Logger* Logger_Create(const char* _moduleName,const char* _FileName, LogLevel _level)
{
    Logger* newLogger;

    newLogger = calloc(1,sizeof(Logger));
    CHECK_EQUAL_RETURN(NULL,newLogger,NULL);

    newLogger->m_magicNumber =MAGICNUMBER;

    newLogger->m_moduleName =calloc(strlen(_moduleName)+1,sizeof(char));
    CHECK_EQUAL_RETURN(NULL,newLogger->m_moduleName,NULL);
    strcpy(newLogger->m_moduleName,_moduleName);

    newLogger->m_fileName =calloc(strlen(_FileName)+1,sizeof(char));
    CHECK_EQUAL_RETURN(NULL,newLogger->m_fileName,NULL);
    strcpy(newLogger->m_fileName,_FileName);
    newLogger->m_level = _level;

return newLogger;
}
/* return the file name of the logger*/
char* Loggger_GetFileName(Logger* _log)
{
    return _log->m_fileName;
}
/* open file to wright the logs in to him*/
void Loggger_setFile(Logger* _log)
{
    _log->m_filePtr = fopen(_log->m_fileName,"a");

return;
}
/*destroy function */
void Logger_Destroy(void* _log)
{
    if(NULL != _log)
    {
        if(NULL != ((Logger*)_log)->m_filePtr)
        {
            fclose(((Logger*)_log)->m_filePtr);
        }
        free(((Logger*)_log)->m_fileName);
        free(((Logger*)_log)->m_moduleName);
    }
    free((Logger*)_log);
return;
}

/*some why the function work but gives error whit -ansi  */
void LoggerWrite(Logger* _log, LogLevel _level,char* _function, char* _file, size_t _line,const char* _format, ...)
{
   /* char buf[256]= {0};
    char levelChar[2] ={0};*/
    char tempArg[128];
    va_list ZlogAP;
    if(NULL != _log && _log->m_level < _level && NULL != _function && NULL != _file  && NULL != _format)
    {

        va_start(ZlogAP, _format);
            vsprintf(tempArg, _format, ZlogAP);
        va_end(ZlogAP);
fprintf(_log->m_filePtr,"%s %s %d %lu %c %s %s %s %lu %s \n",__DATE__,__TIME__, getpid(), pthread_self(),levleToCahr(_log->m_level),_log->m_moduleName,_function,_file,_line,tempArg);

return;
}
/*return the letter from given LogLevel in char as requer for the wright function */
static char levleToCahr(LogLevel _log)
{
    switch(_log)
    {
    case(LOG_TRACE):
        return 'T';

    case(LOG_DEBUG):
        return 'D';

    case(LOG_INFO):
        return 'I';

    case(LOG_WARNING):
        return 'W';

    case(LOG_ERROR):
        return 'E';

    case(LOG_CRITICAL):
        return 'C';

    case(LOG_SEVERE):
        return 'S';

    case(LOG_FATAL):
        return 'F';

    case(LOG_NONE):
        return 'N';

    }
return 'N';
}

