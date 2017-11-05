#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdrMessager.h"
#define MAGICNUMBER 0xDEADDEAD
#define OPEAROT_NAME_LENGHT 65
#define CALLTYPE_LENGHT 6
#define TIMEDATE_LENGHT 10
/*Define struct of  CdrMessage_t */
struct CdrMessage_t
{
    size_t m_magicNumber;
    size_t m_imsi;
    size_t m_msisdn;
    size_t m_imei;
    char* m_operatorName;
    size_t m_mccmnc;
    char* m_callType;
    char* m_callDate;
    char* m_callTime;
    size_t m_duration;
    float m_download;
    float m_upload;
    size_t m_comMsisdn;
    size_t m_comPartyMccmnc;
};

CdrMessage_t*  CdrMessage_Creaty(void)
{
    CdrMessage_t* newMessage;

    newMessage = calloc(1,sizeof(CdrMessage_t));
    if(NULL == newMessage)
    {
            return NULL;
    }

    newMessage->m_operatorName = calloc(OPEAROT_NAME_LENGHT,sizeof(char));
    if(NULL == newMessage->m_operatorName)
    {
        free(newMessage);
        return NULL;
    }

    newMessage->m_callType = calloc(CALLTYPE_LENGHT,sizeof(char));
    if(NULL == newMessage->m_callType)
    {
        free(newMessage->m_operatorName);
        free(newMessage);
        return NULL;
    }
    newMessage->m_callDate = calloc(TIMEDATE_LENGHT,sizeof(char));
    if(NULL == newMessage->m_callDate)
    {
        free(newMessage->m_callType);
        free(newMessage->m_operatorName);
        free(newMessage);
        return NULL;
    }
    newMessage->m_callTime = calloc(TIMEDATE_LENGHT,sizeof(char));
    if(NULL == newMessage->m_callTime)
    {
        free(newMessage->m_callDate);
        free(newMessage->m_callType);
        free(newMessage->m_operatorName);
        free(newMessage);
        return NULL;
    }
    newMessage->m_magicNumber = MAGICNUMBER;

return newMessage;
}

/*************************************************/
CdrMessager_Result CdrMessage_Desroy(CdrMessage_t* _msg)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber)
    {
            return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }
    _msg->m_magicNumber = 0;
    free(_msg->m_callDate);
    free(_msg->m_callTime);
    free(_msg->m_operatorName);
    free(_msg->m_callType);
    free(_msg);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_SetImsi(CdrMessage_t* _msg,const char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    _msg->m_imsi = atol(_str);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_GetImsi(CdrMessage_t* _msg,size_t* _returnVal)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _returnVal)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }
    *_returnVal = _msg->m_imsi;

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_SetOperatorName(CdrMessage_t* _msg,const char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }
    strcpy(_msg->m_operatorName,_str);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_GetOperatorName(CdrMessage_t* _msg,char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }
    strcpy(_str,_msg->m_operatorName);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_SetMccMnc(CdrMessage_t* _msg,const char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }
    _msg->m_mccmnc = atol(_str);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_GetMccMnc(CdrMessage_t* _msg,size_t* _returnVal)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _returnVal)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }
    *_returnVal = _msg->m_mccmnc;

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_SetCallType(CdrMessage_t* _msg,const char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    strcpy(_msg->m_callType,_str);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_GetCallType(CdrMessage_t* _msg,char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    strcpy(_str,_msg->m_callType);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_SetDuration(CdrMessage_t* _msg,const char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    _msg->m_duration = atoi(_str);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_GetDuration(CdrMessage_t* _msg,size_t* _returnVal)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _returnVal)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    *_returnVal = _msg->m_duration;

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_SetDownload(CdrMessage_t* _msg,const char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    _msg->m_download = atof(_str);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_GetDownload(CdrMessage_t* _msg,float* _returnVal)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _returnVal)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    *_returnVal = _msg->m_download;

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_SetUpload(CdrMessage_t* _msg,const char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    _msg->m_upload = atof(_str);

return CDR_MESSAGER_SUCCESS;

}

/*************************************************/
CdrMessager_Result CdrMessage_GetUpload(CdrMessage_t* _msg, float* _returnVal)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _returnVal)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    *_returnVal = _msg->m_upload;

return CDR_MESSAGER_SUCCESS;
}
/*************************************************/
CdrMessager_Result CdrMessage_SetMsisdn(CdrMessage_t* _msg,const char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    _msg->m_msisdn = atol(_str);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_GetMsisdn(CdrMessage_t* _msg,size_t* _returnVal )
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _returnVal)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    *_returnVal = _msg->m_msisdn;

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_SetImei(CdrMessage_t* _msg,const char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    _msg->m_imei = atol(_str);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_GetImei(CdrMessage_t* _msg,size_t* _returnVal )
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _returnVal)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    *_returnVal = _msg->m_imei;

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_SetCallDate(CdrMessage_t* _msg,const char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    strcpy(_msg->m_callDate,_str);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_GetCallDate(CdrMessage_t* _msg,char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    strcpy(_str,_msg->m_callDate);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_SetCallTime(CdrMessage_t* _msg,const char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    strcpy(_msg->m_callTime,_str);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_GetCallTime(CdrMessage_t* _msg,char* _str)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    strcpy(_str,_msg->m_callTime);

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_SetComMsisdn(CdrMessage_t* _msg,const char* _str)
{
     if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber )
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }
    if (NULL != _str)
    {
        _msg->m_comMsisdn = atol(_str);
    }
    else
    {
        _msg->m_comMsisdn = 0;
    }

return CDR_MESSAGER_SUCCESS;
}

/*************************************************/
CdrMessager_Result CdrMessage_GetComMsisdn(CdrMessage_t* _msg, size_t* _returnVal)
{
    if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _returnVal)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    *_returnVal = _msg->m_comMsisdn;

return CDR_MESSAGER_SUCCESS;
}
/*************************************************/
CdrMessager_Result CdrMessage_SetComPartyMccmnc(CdrMessage_t* _msg,const char* _str)
{
         if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _str)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    _msg->m_comPartyMccmnc = atol(_str);

return CDR_MESSAGER_SUCCESS;
}
/*************************************************/
CdrMessager_Result CdrMessage_GetComPartyMccmnc(CdrMessage_t* _msg, size_t* _returnVal)
{
        if(NULL == _msg || MAGICNUMBER != _msg->m_magicNumber || NULL == _returnVal)
    {
        return CDR_MESSAGER_UNINITIALIZED_ERROR;
    }

    *_returnVal = _msg->m_comPartyMccmnc;

return CDR_MESSAGER_SUCCESS;
}
