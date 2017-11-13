#ifndef _DSMESSEGER_H_
#define _DSMESSEGER_H_

/**
 *  @file dsMessger.h
 *  @brief the module is part of Data Manager modules, this module charge at Ds_message.
 *
 *  @details Ds Messager is set get module for Ds messages.

 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

/*Define structure DSMessage_t */
typedef struct DSMessage_t DSMessage_t;

/*Define Enum MesageType */
typedef enum MesageType
{
    operaor,
    subSriber
}MesageType;


/*define uniun for data or time use */
typedef union
{
    size_t sec;
    float data;
}DataType_u;
/*define structer of DS Mesaage type*/
typedef struct DSMessage_t
{
    MesageType m_dsType;
    size_t m_msisdn;
    size_t m_m_mmcMnc;
    char m_opBrandName[64];
    DataType_u  m_typeData;
}DSMessage_t;

/*Define Enum DSMessage Result */
typedef enum DSMessage_Result
{
    DS_MESSAGE_SUCCESS,
    DS_MESSAGE_ERRROR
}DSMessage_Result;


/**
Create an emptey message
return pointer to new message
*/
DSMessage_t* DSMessage_Creaty();
/**
Destroy message
param [in] DsMessage_t* - msg as define in this moudule
return - DSMessage_Result
*/
DSMessage_Result DSMessage_Desroy(DSMessage_t* _msg);

/*
the function set (desript) message to send 
param [out] DsMessage_t* -message that will set msg as define in this moudule
return - DSMessage_Result
*/
DSMessage_Result DSMessage_Set(DSMessage_t* _msg);

/*
the function get message (encript)
param [out] DsMessage_t* -message that will set msg as define in this moudule
return - DSMessage_Result
*/
DSMessage_Result DSMessage_Get(DSMessage_t* _msg);

#endif /* _DSMASSEGER_H_*/
