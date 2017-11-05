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

typedef union
{
    size_t sec;
    float data;
}DataType_u;

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



DSMessage_t* DSMessage_Creaty();

DSMessage_Result DSMessage_Desroy(DSMessage_t* _msg);

DSMessage_Result DSMessage_Set(DSMessage_t* _msg);

DSMessage_Result DSMessage_Get(DSMessage_t* _msg);

#endif /* _DSMASSEGER_H_*/
