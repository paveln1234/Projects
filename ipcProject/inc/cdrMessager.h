#ifndef _CDRMESSSAGER_H_
#define _CDRMESSSAGER_H_

/**
 *  @file cdrMessager.h
 *  @brief the module is part of CDR Manager modules, this module charge at Cdr_Message.
 *
 *  @details CDR Message is set get module for Cdr Message.

 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

/*Define struct of  CdrMessage_t */
 typedef struct CdrMessage_t CdrMessage_t;

/*Define Enum CdrMessage Result */
typedef enum CdrMessager_Result
{
    CDR_MESSAGER_SUCCESS,
    CDR_MESSAGER_UNINITIALIZED_ERROR, /* Uninitialized  error 	*/
    CDR_MESSAGER_ERROR
}CdrMessager_Result;

/**
 * @brief The function create new Cdr_Message_t.
 * @return in success CdrMessage_t* in fail NULL.
 */
CdrMessage_t*  CdrMessage_Creaty(void);

/**
 * @brief The function Destroy  CdrMessage_t
 * @param[in] CdrMessage_t* _msg- CdrMessage_t to destroy
 * @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_Desroy(CdrMessage_t* _msg);

/**
 * @brief The function Set IMSI
 * @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
 * @param[in] char* _str- str to set
 * @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetImsi(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function get IMSI
 * @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
 * @param[in] size_t* _returnVal- pointer to return value;
 * @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_GetImsi(CdrMessage_t* _msg,size_t* _returnVal);

/**
 * @brief The function Set Msisdn
 * @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
 * @param[in] char* _str- str to set
 * @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetMsisdn(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function get Msisdn
 * @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
 * @param[in] size_t* _returnVal -  pointer to return value.
 * @return CdrMessager_Result;
 */
 CdrMessager_Result CdrMessage_GetMsisdn(CdrMessage_t* _msg,size_t* _returnVal );

/**
 * @brief The function Set IMEI
 * @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
 * @param[in] char* _str- str to set
 * @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetImei(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function get IMEI
 * @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
 * @param[in] size_t* _returnVal -  pointer to return value.
 * @return CdrMessager_Result;
 */
 CdrMessager_Result CdrMessage_GetImei(CdrMessage_t* _msg,size_t* _returnVal );


/**
 * @brief The function Set OperatorName
* @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
* @param[in] char* _str- str to set
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetOperatorName(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function Get OperatorName
* @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
* @param[in] char* _str- str to set
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_GetOperatorName(CdrMessage_t* _msg,char* _str);

/**
 * @brief The function Set MCC/MNC
* @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
* @param[in] char* _str- str to set
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetMccMnc(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function Get MCC/MNC
* @param[in] CdrMessage_t* _msg- CdrMessage_t to Get from him
* @param[in] size_t* _returnVal -  pointer to return value.
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_GetMccMnc(CdrMessage_t* _msg,size_t* _returnVal);

/**
 * @brief The function Set CallType
* @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
* @param[in] char* _str- str to set
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetCallType(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function Get CallType
* @param[in] CdrMessage_t* _msg- CdrMessage_t to Get from him
* @param[in] char* _str- pointer to return value.
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_GetCallType(CdrMessage_t* _msg,char* _str);


/**
 * @brief The function Set CallDate
* @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
* @param[in] char* _str- str to set
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetCallDate(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function Get CallDate
* @param[in] CdrMessage_t* _msg- CdrMessage_t to Get from him
* @param[in] char* _str- pointer to return value.
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_GetCallDate(CdrMessage_t* _msg,char* _str);

/**
 * @brief The function Set CallTime
* @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
* @param[in] char* _str- str to set
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetCallTime(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function Get CallTime
* @param[in] CdrMessage_t* _msg- CdrMessage_t to Get from him
* @param[in] char* _str- pointer to return value.
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_GetCallTime(CdrMessage_t* _msg,char* _str);

/**
 * @brief The function Set Duration
* @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
* @param[in] char* _str- str to set
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetDuration(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function Get Duration
* @param[in] CdrMessage_t* _msg- CdrMessage_t to get from him
* @param[in] size_t* _returnVal -  pointer to return value.
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_GetDuration(CdrMessage_t* _msg,size_t* _returnVal);

/**
 * @brief The function Set Download
* @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
* @param[in] char* _str- str to set
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetDownload(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function Get Download
* @param[in] CdrMessage_t* _msg- CdrMessage_t to get from him
* @param[in] size_t* _returnVal -  pointer to return value.
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_GetDownload(CdrMessage_t* _msg,float* _returnVal);

/**
 * @brief The function Set Upload
* @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
* @param[in] char* _str- str to set
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetUpload(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function Get Upload
* @param[in] CdrMessage_t* _msg- CdrMessage_t to get from him
* @param[in] size_t* _returnVal -  pointer to return value.
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_GetUpload(CdrMessage_t* _msg, float* _returnVal);

/**
 * @brief The function Set Parry Msisdn
* @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
* @param[in] char* _str- str to set
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetComMsisdn(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function Get Parry Msisdn
* @param[in] CdrMessage_t* _msg- CdrMessage_t to get from him
* @param[in] size_t* _returnVal -  pointer to return value.
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_GetComMsisdn(CdrMessage_t* _msg, size_t* _returnVal);

/**
 * @brief The function Set Party Mccmnc
* @param[in] CdrMessage_t* _msg- CdrMessage_t to set on him
* @param[in] char* _str- str to set
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_SetComPartyMccmnc(CdrMessage_t* _msg,const char* _str);

/**
 * @brief The function Get Party Mccmnc
* @param[in] CdrMessage_t* _msg- CdrMessage_t to get from him
* @param[in] size_t* _returnVal -  pointer to return value.
* @return CdrMessager_Result;
 */
CdrMessager_Result CdrMessage_GetComPartyMccmnc(CdrMessage_t* _msg, size_t* _returnVal);

#endif /* _CDRMESSSAGER_H_*/
