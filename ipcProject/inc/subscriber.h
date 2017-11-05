#ifndef _SUBSCRIBER_H_
#define _SUBSCRIBER_H_


/**
 *  @file subScriber.h
 *  @brief set get function  for  subscriber data.
 *
 *  @details  set get function  for   subscriber data.
 *
 *  @author Pavel Korolin (paveln1234@gmail.com)
 *
 *  @bug No known bugs.
 */

 /*Define struct Subsrcibe Data */
typedef struct SubScribeData_t SubScribeData_t;


/*Define Enum SubScribeData Result */
typedef enum SubScribeData_Result
{
    SUBSCRIBE_DATA_SUCCESS,
    SUBSCRIBE_DATA_UNINITIALIZED_ERROR
}SubScribeData_Result;


/**
 * @brief The function create and init  Subsrciber data.
 * @param[in] size_t _msisdn -Msisdn number of the new SubScriber.
 * @return in success SubScribeData_t* in fail NULL.
 */
SubScribeData_t* SubScribe_Creaty(size_t _msisdn);

/**
 * @brief The function create and init  Subsrciber.
 * @param[in] SubScribeData_t _sub -SubScribeData to destroy;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_Destroy(SubScribeData_t* _sub);

/**
 * @brief The function Add sec  to Out Call Wight Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @param[in] size_t _sec -seconds to add to given SubScriber;
 * @return SubScribeData_Result.
 */
 SubScribeData_Result SubScribe_AddOutCallWightOperator(SubScribeData_t* _sub,size_t _sec);

 /**
 * @brief The function return  Out Call Wight Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return SubScribeData_Result.
 */
 SubScribeData_Result SubScribe_GetOutCallWightOperator(SubScribeData_t* _sub,size_t* _retVul);

/**
 * @brief The function Add sec  to in Call Wight Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @param[in] size_t _sec -seconds to add to given SubScriber;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_AddInCallWightOperator(SubScribeData_t* _sub,size_t _sec);

/**
 * @brief The function return  In Call Wight Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return SubScribeData_Result.
 */
 SubScribeData_Result SubScribe_GetInCallWightOperator(SubScribeData_t* _sub,size_t* _retVul);

/**
 * @brief The function Add sec  to Out Call Outside Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @param[in] size_t _sec -seconds to add to given SubScriber;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_AddOutCallOutsideOperator(SubScribeData_t* _sub,size_t _sec);

/**
 * @brief The function return  Out Call Outside Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return SubScribeData_Result.
 */
 SubScribeData_Result SubScribe_GetOutCallOutsideOperator(SubScribeData_t* _sub,size_t* _retVul);

/**
 * @brief The function Add sec  to in Call Outside Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @param[in] size_t _sec -seconds to add to given SubScriber;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_AddInCallOutsideOperator(SubScribeData_t* _sub,size_t _sec);

/**
 * @brief The function return  In Call Outside Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to return from;
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return SubScribeData_Result.
 */
 SubScribeData_Result SubScribe_GetInCallOutsideOperator(SubScribeData_t* _sub,size_t* _retVul);

/**
 * @brief The function Add one  to Out Sms Wight Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_AddOutSmsWightOperator(SubScribeData_t* _sub);

/**
 * @brief The function return Out Sms Wight Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to return from;
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_GetOutSmsWightOperator(SubScribeData_t* _sub,size_t* _retVul);

/**
 * @brief The function Add one  to In Sms Wight Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_AddInSmsWightOperator(SubScribeData_t* _sub);

/**
 * @brief The function return In Sms Wight Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to return from;
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_GetInSmsWightOperator(SubScribeData_t* _sub,size_t* _retVul);

/**
 * @brief The function Add one  to Out Sms Outside Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_AddOutSmsOutsideOperator(SubScribeData_t* _sub);

/**
 * @brief The function return Out Sms Outside Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to return from;
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_GetOutSmsOutsideOperator(SubScribeData_t* _sub,size_t* _retVul);

/**
 * @brief The function Add one  to In Sms Outside Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_AddInSmsOutsideOperator(SubScribeData_t* _sub);

/**
 * @brief The function return In Sms Outside Operator.
 * @param[in] SubScribeData_t* _sub -SubScribeData to return from;
 * @param[in] size_t* _retVul -pointer  to return value.
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_GetInSmsOutsideOperator(SubScribeData_t* _sub,size_t* _retVul);

/**
 * @brief The function Add Mb  Download.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @param[in] ,float _mb - number of Mb that add as afloat number
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_AddDownload(SubScribeData_t* _sub,float _mb);

/**
 * @brief The function return  download.
 * @param[in] SubScribeData_t* _sub -SubScribeData to return from;
 * @param[in] float* _retVul - pointer  to return value;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_GetDownload(SubScribeData_t* _sub,float* _retVul);

/**
 * @brief The function Add Mb  Upload.
 * @param[in] SubScribeData_t* _sub -SubScribeData to Add to;
 * @param[in] ,float _mb - number of Mb that add as afloat number
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_AddUpload(SubScribeData_t* _sub,float _mb);

/**
 * @brief The function return Upload.
 * @param[in] SubScribeData_t* _sub -SubScribeData to return from;
 * @param[in] float* _retVul - pointer  to return value;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_GetUpload(SubScribeData_t* _sub,float* _retVul);

/**
 * @brief The function convert subScriber to str.
 * @param[in] SubScribeData_t* _sub -SubScribeData to convert;
 * @param[in] char* _buffer -buffer to return str;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_SubSribeToSrc(SubScribeData_t* _sub,char* _buffer);

/**
 * @brief The function Reset All SubSriber fields to 0.
 * @param[in] SubScribeData_t* _sub -SubScribeData to reset;
 * @return SubScribeData_Result.
 */
SubScribeData_Result SubScribe_SubSribeReset(SubScribeData_t* _sub);

#endif /* _SUBSCRIBER_H_*/
