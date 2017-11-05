#include <stdio.h>/*FILE*/
#include <stdlib.h>/* calloc*/
#include<string.h>/*hashmap strlen*/
#include "zlogManager.h"
#include "logger.h"
#include "config.h"
#include "hashmap.h"

#define MAGICNUMBER 0xDEADC0DE

#define DEFULTPATH "./"
#define DEFULTFILENAME "Zlog.log"
#define DEFULTLOG_LEVEL LOG_ERROR
#define DEFULTNAME "#"
#define DEFULTHASHSIZE 20

typedef struct LogManager
{
	char* m_defaultPath;
	void* m_loggers;
	Logger* m_defaultLogger;
	size_t m_magicNumber;
}LogManager;

/*-----------hashmap funcion----------------------*/
size_t hashfunc(char* _str);
int IsEqual(char* _firstKey,char* _secondKey);


/*-----------global for this scope----------------------*/
/*------------------------------------------------------*/
static LogManager* newLogManager;
void ZlogInit(char* _configFileName)
{

    void* templog;
    ConfigData* tempData;

    int flag = 0;

    newLogManager = calloc(1,sizeof(LogManager));
    if(NULL == newLogManager)
    {
        return;
    }
    /*if file name not give's create default stings */
    if(NULL == _configFileName)
    {
        flag = 1;
        if(NULL != (newLogManager->m_defaultLogger =  Logger_Create(DEFULTNAME,DEFULTFILENAME,DEFULTLOG_LEVEL)))
        {
            newLogManager->m_defaultPath = DEFULTPATH;
            newLogManager->m_magicNumber = MAGICNUMBER;
            Loggger_setFile(newLogManager->m_defaultLogger);
        }

    }
    if(!flag)
    {
        /*can tempData cane be VOID ? */
        tempData = calloc(1,sizeof(ConfigData));
        tempData = Config_Read(_configFileName);
        /*set default stings and open default log file*/
        newLogManager->m_defaultPath = Config_GetPath(tempData->m_data);

        newLogManager->m_defaultLogger = Logger_Create( Config_GetMoudeleName(tempData->m_data),Config_GetFileName(tempData->m_data),Config_GetLogLevel(tempData->m_data));
        newLogManager->m_magicNumber = MAGICNUMBER;
        Loggger_setFile(newLogManager->m_defaultLogger);

        newLogManager->m_loggers = HashMap_Create(DEFULTHASHSIZE,(HashFunction)hashfunc,(EqualityFunction)IsEqual);
        HashMap_Insert(newLogManager->m_loggers,Config_GetMoudeleName(tempData->m_data),newLogManager->m_defaultLogger);

        templog = malloc(sizeof(void*));
        while(Config_GetNextItem(tempData->m_data))
        {
            templog = Logger_Create( Config_GetMoudeleName(tempData->m_data),Config_GetFileName(tempData->m_data),Config_GetLogLevel(tempData->m_data));
            HashMap_Insert(newLogManager->m_loggers,Config_GetMoudeleName(tempData->m_data),templog);
        }

        Config_Close(&tempData);
        free(templog);
        /*free(templog);
        free(tempData->m_data);
        free(tempData);*/ /*why crash all the time*/
    }

return;
}

void ZlogClose()
{

    HashMap_Destroy((HashMap**)&newLogManager->m_loggers,NULL,Logger_Destroy);

return;
}

Logger* ZlogGet(char* _moduleName)
{
    Logger* getLogger;

    if(NULL != _moduleName)
    {
        if( MAP_SUCCESS == HashMap_Find((HashMap*)newLogManager->m_loggers,_moduleName,(void**)&getLogger))
        {
            Loggger_setFile(getLogger);
            return getLogger;
        }
    }
return newLogManager->m_defaultLogger;
}



/*--------------Hash map Function-----------------------*/

/* hash function for hash map */
size_t hashfunc(char* _str)
{
    size_t hash = 5381;
    size_t i = 0;
    size_t len = strlen(_str);
    for(i = 0; i < len; _str++, i++)
    {
        hash = ((hash << 5) + hash) + (*_str);
    }

    return hash;
}

/* compare function to hash map*/
int IsEqual(char* _firstKey,char* _secondKey)
{
	return (strcmp(_firstKey,_secondKey) == 0 ? 1 : 0);
}
/*--------------Hash map Function-----------------------*/


