#include <stdio.h>/*file*/
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "queue.h"
#include "zlogManager.h"
#include "macros.h"

#define BUFFER 128
#define TRUE 1
#define FALSE 0
#define MAGICNUMBER 0xDEADBAAD


typedef struct DataStruct
{
    char* m_name;
	char* m_fileName;
    char* m_pathe;
    LogLevel m_level;

}DataStruct;



/* internal functions  */
static LogLevel LogLevelDetectev(char* _logLevel);
static void Log_GetData(const char* _line,char* _data);
static void Log_GetName(const char* _line,char* _name);
static void* createStruct(FILE* _file,int* _flag);
static void destroyConfig (void* _item);

/* global for the scope only*/
static ConfigData* newConfig;


void* Config_Read(const char* _configFileName)
{
    FILE* file;
    void* queue;
    char* temp;
    int flag = TRUE;
    char c;

    CHECK_EQUAL_RETURN(NULL,_configFileName,NULL);

    queue = Queue_Create(TRUE);
    file = fopen(_configFileName,"r");
    newConfig = calloc(1,sizeof(ConfigData));

    /* create the default LOG */
    while(!feof(file) && !ferror(file))
    {
        Queue_Enqueue(queue,createStruct(file,&flag));
        c = fgetc(file);
    }

    file = fopen(_configFileName,"r");
    temp = Config_GetPath(queue);

    /* change the directory to log directory  */
    chdir(temp);
    newConfig->m_configFile = file;
    newConfig->m_data = queue;

return newConfig ;
}

void Config_Close(ConfigData** _data)
{
    fclose((*_data)->m_configFile);
    Queue_Destory((Queue**)&(*_data)->m_data,destroyConfig);
    free(*_data);
    *_data = NULL;
return;
}
/*the function create new struct from file it reads from [name] and until get log name*/
static void* createStruct(FILE* _file,int* _flag)
{
    DataStruct* Logstruct;
    int i = 0;
    char tempstr[BUFFER] ={'\0'} ;
    char line[BUFFER]= {'\0'} ;
/* clean the file  buffer */
    fflush(_file);
    Logstruct = calloc(1,sizeof(DataStruct));
    /* get the Log name */
    fgets(line,BUFFER,_file);
    Log_GetName(line,tempstr);
    Logstruct->m_name = calloc(strlen(tempstr)+2,sizeof(char));
    strcpy(Logstruct->m_name,tempstr);
    /* get the Log Level */
    fgets(line,BUFFER,_file);
    Log_GetData(line,tempstr);
    Logstruct->m_level = LogLevelDetectev(tempstr);
    /* get the Log path needs only to default Log  */
    if(*_flag)
    {

        fgets(line,BUFFER,_file);
        Log_GetData(line,tempstr);
        Logstruct->m_pathe = calloc(strlen(tempstr)+2,sizeof(char));
        strcpy(Logstruct->m_pathe,tempstr);
        /* cleaning file buffer and line and tempst some whe it wright junk to file */
        fflush(_file);
        for(; i<BUFFER;++i)
        {
            line[i] = '\0';
            tempstr[i] = '\0';
        }
        *_flag = FALSE;
    }

    /* get the Log file */
    fgets(line,BUFFER,_file);
    Log_GetData(line,tempstr);
    Logstruct->m_fileName = calloc(strlen(tempstr)+2,sizeof(char));
    strcpy(Logstruct->m_fileName,tempstr);

return Logstruct;
}
/* read the file from [ and until ]*/
static void Log_GetName(const char* _line,char* _name)
{
    while( '[' != *_line)
    {
        ++_line;
    }

    ++_line;

    while( ']' != *_line)
    {
        *_name = *_line;
        ++_line;
        ++_name;
    }
return;
}

/* the function read data from given data it look the char = at first and after look for first char that is not spase and copy it*/
static void Log_GetData(const char* _line,char* _data)
{
    while( '=' != *_line)
    {
        ++_line;
    }

    ++_line;
    while(' ' == *_line )
    {
        ++_line;
    }

    while('\0' != *_line && ' ' != *_line && '\n' != *_line)
    {
        *_data = *_line;
        ++_line;
        ++_data;
    }
return;
}

/* the function return LogLevel level from a given string */
static LogLevel LogLevelDetectev(char* _logLevel)
{
    int i =0;
    char* ch[] = {"LOG_TRACE","LOG_DEBUG","LOG_INFO","LOG_WARNING","LOG_ERROR","LOG_CRITICAL","LOG_SEVERE","LOG_FATAL","LOG_NONE"};
    while (strcmp(_logLevel,ch[i])!= 0)
    {
        ++i;
    }
    return i;
}
/* return path from data  the data null if empty */
char* Config_GetPath(void* _data)
{
    DataStruct*  tempDataStruct = NULL;

    CHECK_EQUAL_RETURN(NULL,_data,NULL);
    Queue_Top((Queue*)_data,(void**)&tempDataStruct);

return tempDataStruct->m_pathe;
}

/* return moudele name  from data  the data */
char* Config_GetMoudeleName(void* _data)
{
    DataStruct*  tempDataStruct;

    CHECK_EQUAL_RETURN(NULL,_data,NULL);
    Queue_Top((Queue*)_data,(void**)&tempDataStruct);

return tempDataStruct->m_name;
}
/* return file name  from data  the data */
char* Config_GetFileName(void* _data)
{
    DataStruct*  tempDataStruct;
    char tempstr[BUFFER] ={'\0'} ;

    CHECK_EQUAL_RETURN(NULL,_data,NULL);
    Queue_Top((Queue*)_data,(void**)&tempDataStruct);
    strcpy(tempstr,tempDataStruct->m_fileName);
return tempDataStruct->m_fileName;
}
/* return LogLevele name  from data  the data */
LogLevel Config_GetLogLevel(void* _data)
{
    DataStruct*  tempDataStruct;

    CHECK_EQUAL_RETURN(NULL,_data,LOG_ERROR);
    Queue_Top((Queue*)_data,(void**)&tempDataStruct);

return tempDataStruct->m_level;
}

/* the function check if the queue is empty*/
int Config_IsEmptey(void*_data)
{
    return Queue_isEmptey((Queue*)_data);
}

/* the function return the next item from queue if the item NULL queue is emptey return FALSE*/
int Config_GetNextItem(void* _data)
{
    Queue_Result res;
    DataStruct* _item;
    CHECK_EQUAL_RETURN(NULL,_data,FALSE);
    res = Queue_Dequeue((Queue*)_data,(void**)&_item);
 /*   free(_item);*/
return (res == QUEUE_SUCCESS)?TRUE:FALSE;
}

/* destroy function*/
static void destroyConfig(void* _item)
{

    free(((DataStruct* )(_item))->m_fileName);
    free(((DataStruct* )(_item))->m_name);
    free(_item);

return;
}
